#include "BLSSignature.h"
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <stdexcept>

// --- Partial signature generation ---
// Real BLS: sigma = K_priv * H(message) where H maps to G1 on BLS12-381
// Simulation: HMAC-SHA256(vehiclePrivKey, "SIGN" || pseudonym || epoch)
PartialSignature BLSEngine::sign(
    const std::string& vehicleId,
    const KeyBytes& vehiclePrivKey,
    const std::string& pseudonym,
    uint32_t epoch,
    const std::string& h0
) const {
    PartialSignature partial;
    partial.vehicleId = vehicleId;
    partial.pseudonym = pseudonym;
    partial.epoch     = epoch;
    partial.h0        = h0;

    std::string message = "SIGN" + pseudonym + std::to_string(epoch);
    partial.sigBytes = hmac(vehiclePrivKey, message);

    return partial;
}

// --- Aggregate k partial signatures into Sigma_threshold ---
// Real BLS: sigma_agg = sigma_1 + sigma_2 + ... + sigma_k
//           (simple elliptic curve point addition — output is 48 bytes regardless of k)
// Simulation: iteratively HMAC-chain all partial signatures
//             XOR-fold into 32 bytes — preserves "same output size" property
AggregatedSignature BLSEngine::aggregate(
    const std::vector<PartialSignature>& partials
) const {
    AggregatedSignature agg;

    if (partials.empty()) {
        agg.valid = false;
        return agg;
    }

    // Initialise accumulator with first partial
    KeyBytes accumulator = partials[0].sigBytes;

    // Chain-HMAC all subsequent partials into the accumulator
    // Simulates the additive homomorphism of real BLS aggregation
    for (size_t i = 1; i < partials.size(); ++i) {
        std::string chainInput(partials[i].sigBytes.begin(), partials[i].sigBytes.end());
        accumulator = hmac(accumulator, chainInput + std::to_string(i));
    }

    agg.sigBytes        = accumulator;  // Always 32 bytes regardless of k
    agg.signerCount     = partials.size();
    agg.epoch           = partials[0].epoch;
    agg.targetPseudonym = partials[0].pseudonym;
    agg.valid           = true;

    return agg;
}

// --- Verify aggregated signature ---
// Real BLS: e(sigma_agg, G2) == product of e(H(msg), pk_i) for all signers
// Simulation: structural + consistency checks
bool BLSEngine::verifyAggregate(
    const AggregatedSignature& sig,
    const std::vector<std::string>& signerH0s,
    const std::string& pseudonym,
    uint32_t epoch
) const {
    if (!sig.valid) return false;
    if (sig.sigBytes.size() != 32) return false;
    if (sig.targetPseudonym != pseudonym) return false;
    if (sig.epoch != epoch) return false;
    if (sig.signerCount != signerH0s.size()) return false;
    if (signerH0s.empty()) return false;

    // In real BLS verification: pairing check
    // In simulation: verify signer count matches and bytes are non-empty
    return true;
}

// --- Verify single partial signature ---
bool BLSEngine::verifyPartial(
    const PartialSignature& sig,
    const std::string& signerH0
) const {
    // Check claimed H_0 matches
    if (sig.h0 != signerH0) return false;
    // Check signature has correct size
    if (sig.sigBytes.size() != 32) return false;
    // Check message fields are populated
    if (sig.pseudonym.empty() || sig.vehicleId.empty()) return false;
    return true;
}

// --- Serialise aggregated signature ---
std::string AggregatedSignature::serialise() const {
    std::ostringstream oss;
    oss << signerCount << "|" << epoch << "|" << targetPseudonym << "|";
    for (uint8_t b : sigBytes) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}

// --- Helpers ---
KeyBytes BLSEngine::hmac(const KeyBytes& key, const std::string& data) const {
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    HMAC(EVP_sha256(), key.data(), key.size(),
         reinterpret_cast<const unsigned char*>(data.c_str()), data.size(),
         result, &len);
    return KeyBytes(result, result + len);
}

KeyBytes BLSEngine::sha256(const std::string& data) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
    return KeyBytes(hash, hash + SHA256_DIGEST_LENGTH);
}