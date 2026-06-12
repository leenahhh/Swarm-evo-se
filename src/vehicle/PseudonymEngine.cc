#include "PseudonymEngine.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

void PseudonymEngine::loadSessionSeed(const KeyBytes& sessionSeed, uint32_t epoch) {
    sessionSeed_   = sessionSeed;
    currentEpoch_  = epoch;
    nextIndex_     = 0;  // Reset index counter for new epoch
}

// P_i = SHA256(S_session || "PSEUDO" || i)
std::string PseudonymEngine::derivePseudonym(uint32_t index) const {
    if (sessionSeed_.empty()) throw std::runtime_error("PseudonymEngine: no session seed loaded.");

    std::string input(sessionSeed_.begin(), sessionSeed_.end());
    input += "PSEUDO";
    input += std::to_string(index);

    return toHex(sha256(input));
}

// k_i = SHA256(S_session || "SIGNKEY" || i)
KeyBytes PseudonymEngine::deriveSigningKey(uint32_t index) const {
    if (sessionSeed_.empty()) throw std::runtime_error("PseudonymEngine: no session seed loaded.");

    std::string input(sessionSeed_.begin(), sessionSeed_.end());
    input += "SIGNKEY";
    input += std::to_string(index);

    return sha256(input);
}

KeyBytes PseudonymEngine::sha256(const std::string& data) const {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
    return KeyBytes(hash, hash + SHA256_DIGEST_LENGTH);
}

std::string PseudonymEngine::toHex(const KeyBytes& bytes) const {
    std::ostringstream oss;
    for (uint8_t b : bytes) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}