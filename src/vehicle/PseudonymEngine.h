#ifndef PSEUDONYMENGINE_H
#define PSEUDONYMENGINE_H

// PseudonymEngine.h — Hierarchical Deterministic Pseudonym Derivation
//
// Takes S_session (from HSM) and derives an unlimited pool of pseudonyms.
// P_i = SHA256(S_session || "PSEUDO" || i)
//
// Properties:
//   - Same S_session + i always produces same P_i (deterministic)
//   - P_1 and P_2 look like random bytes to anyone without S_session
//   - Pool is infinite — exhaustion impossible
//   - S_session changes every epoch — old pseudonyms cannot be linked to new ones

#include <string>
#include <vector>
#include <cstdint>

using KeyBytes = std::vector<uint8_t>;

class PseudonymEngine {
public:
    PseudonymEngine() = default;

    // Load a new session seed (called at start of each epoch)
    // S_session comes from HSM — the app processor receives this but NOT K_master
    void loadSessionSeed(const KeyBytes& sessionSeed, uint32_t epoch);

    // Derive pseudonym at index i
    // P_i = SHA256(S_session || "PSEUDO" || i)
    std::string derivePseudonym(uint32_t index) const;

    // Derive the signing private key for pseudonym i
    // k_i = SHA256(S_session || "SIGNKEY" || i)
    // This is an ephemeral key — different for each pseudonym
    KeyBytes deriveSigningKey(uint32_t index) const;

    // Get current epoch
    uint32_t getCurrentEpoch() const { return currentEpoch_; }

    // Get current session seed (for ZK proof generation — stays in OBU, not broadcast)
    const KeyBytes& getSessionSeed() const { return sessionSeed_; }

    // Get next unused index
    uint32_t getNextIndex() { return nextIndex_++; }

private:
    KeyBytes sessionSeed_;   // S_session from HSM (changes each epoch)
    uint32_t currentEpoch_;  // Current epoch number
    uint32_t nextIndex_;     // Next pseudonym index to use

    // Internal: SHA256 helper
    KeyBytes sha256(const std::string& data) const;
    // Convert bytes to hex string
    std::string toHex(const KeyBytes& bytes) const;
};

#endif // PSEUDONYMENGINE_H