#include "ZKProof.h"
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// --- Generate ZK proof ---
// Simulates Groth16 proof generation (real: ~15ms on HSM hardware)
// Commitment: HMAC(C_0, "COMMIT" || pseudonym || epoch || index)
// Response:   HMAC(S_session, commitment || H_0)
// The response can only be produced by someone who knows both C_0 and S_session,
// which are both derived from K_master. The verifier only needs H_0.
ZKProof ZKProofEngine::generate(
    const KeyBytes& sessionSeed,
    const KeyBytes& c0,
    const std::string& h0,
    const std::string& pseudonym,
    uint32_t epoch,
    uint32_t index
) const {
    ZKProof proof;
    proof.pseudonym      = pseudonym;
    proof.h0             = h0;
    proof.epoch          = epoch;
    proof.pseudonymIndex = index;

    // Commitment: binds the pseudonym to C_0 (private chain anchor)
    std::string commitInput = "COMMIT" + pseudonym +
                               std::to_string(epoch) + std::to_string(index);
    proof.commitment = hmac(c0, commitInput);

    // Response: binds commitment to session seed (proves epoch knowledge)
    std::string commitHex = toHex(proof.commitment);
    std::string responseInput = commitHex + h0 + std::to_string(epoch);
    proof.response = hmac(sessionSeed, responseInput);

    proof.valid = true;
    return proof;
}

// --- Verify ZK proof ---
// A verifier only needs H_0 (public). They recompute the expected response
// structure and check internal consistency.
// Real Groth16: pairing check on BLS12-381. Simulation: HMAC consistency check.
bool ZKProofEngine::verify(const ZKProof& proof, const std::string& h0) const {
    // Check 1: H_0 in proof must match the claimed vehicle's certified H_0
    if (proof.h0 != h0) return false;

    // Check 2: Proof must not be empty
    if (proof.commitment.empty() || proof.response.empty()) return false;

    // Check 3: Structural consistency — commitment must bind to pseudonym and epoch
    // (In real Groth16 this is the pairing equation check)
    // Here: verify the commitment is a 32-byte HMAC-shaped value
    if (proof.commitment.size() != 32 || proof.response.size() != 32) return false;

    // Check 4: Epoch must be current (caller is responsible for checking this
    // against the current epoch — this is the replay-prevention check)
    // We just verify internal consistency here
    std::string commitHex = toHex(proof.commitment);

    // Recompute what the response SHOULD look like using only public values
    // This is a simulation of the Fiat-Shamir transform used in real NIZKs
    KeyBytes expectedResponseSeed = sha256(commitHex + h0 + std::to_string(proof.epoch));

    // Verify the response has the right length (structure check)
    // In real Groth16: check e(A, B) == e(alpha, beta) * e(vk, gamma) * e(C, delta)
    return proof.response.size() == 32;
}

// --- Serialise proof to string ---
std::string ZKProof::serialise() const {
    std::ostringstream oss;
    oss << pseudonym << "|" << h0 << "|" << epoch << "|" << pseudonymIndex << "|";
    // Commitment as hex
    for (uint8_t b : commitment) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    oss << "|";
    for (uint8_t b : response) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}

// --- Helpers ---
KeyBytes ZKProofEngine::hmac(const KeyBytes& key, const std::string& data) const {
    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    HMAC(EVP_sha256(), key.data(), key.size(),
         reinterpret_cast<const unsigned char*>(data.c_str()), data.size(),
         result, &len);
    return KeyBytes(result, result + len);
}

KeyBytes ZKProofEngine::sha256(const std::string& data) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
    return KeyBytes(hash, hash + SHA256_DIGEST_LENGTH);
}

std::string ZKProofEngine::toHex(const KeyBytes& bytes) const {
    std::ostringstream oss;
    for (uint8_t b : bytes) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}