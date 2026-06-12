#ifndef ZKPROOF_H
#define ZKPROOF_H

// ZKProof.h — Non-Interactive Zero-Knowledge Proof (NIZK)
//
// Purpose: prove that pseudonym P_i was derived from a registered K_master
// whose H_0 is TA-certified, WITHOUT revealing K_master, C_0, or S_session.
//
// Real implementation: Groth16 or Bulletproofs over BLS12-381
// Simulation: HMAC-based commitment scheme with same interface and data sizes
//
// The proof convinces a verifier that:
//   "I know a secret K such that H_0 = K * G AND P_i = f(derive(K, epoch), i)"
// without revealing K.

#include <vector>
#include <string>
#include <cstdint>

using KeyBytes = std::vector<uint8_t>;

// A complete ZK proof for one pseudonym
struct ZKProof {
    std::string pseudonym;        // The pseudonym being proven (P_i)
    std::string h0;               // H_0 of the claiming vehicle (public)
    uint32_t    epoch;            // Epoch this proof was generated for
    uint32_t    pseudonymIndex;   // Index i of this pseudonym
    KeyBytes    commitment;       // Cryptographic commitment (32 bytes)
    KeyBytes    response;         // Proof response (32 bytes)
    bool        valid;            // Result of verification

    // Serialise to string for network transmission
    std::string serialise() const;
};

class ZKProofEngine {
public:
    ZKProofEngine() = default;

    // Generate a ZK proof for pseudonym P_i
    // Inputs available INSIDE the HSM only; this is called by the HSM
    //   sessionSeed: S_session for current epoch (from HSM)
    //   c0:          chain anchor (from HSM, stays internal)
    //   h0:          public key (safe to include in proof)
    //   pseudonym:   P_i (the value being proven)
    //   epoch:       current epoch number
    //   index:       i (which pseudonym in this epoch's pool)
    // Returns a complete ZKProof ready for transmission
    ZKProof generate(
        const KeyBytes& sessionSeed,
        const KeyBytes& c0,
        const std::string& h0,
        const std::string& pseudonym,
        uint32_t epoch,
        uint32_t index
    ) const;

    // Verify a ZK proof
    // Inputs available to ANY vehicle (public values only)
    //   proof: the proof received in CANDIDATE_MSG
    //   h0:    the claimed vehicle's certified public key (from TA cert)
    // Returns true if proof is valid — pseudonym was legitimately derived
    bool verify(const ZKProof& proof, const std::string& h0) const;

private:
    // Internal: HMAC-SHA256 helper
    KeyBytes hmac(const KeyBytes& key, const std::string& data) const;

    // Internal: SHA256 of a string
    KeyBytes sha256(const std::string& data) const;

    // Convert bytes to hex string
    std::string toHex(const KeyBytes& bytes) const;
};

#endif // ZKPROOF_H