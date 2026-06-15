#ifndef HSM_H
#define HSM_H

// HSM.h — Hardware Security Module simulation
// In a real vehicle this is the Infineon SLB 9670 / NXP SE050 / STMicro STA1085.
// Here we simulate it as a software object with the same interface and security boundaries.
// K_master NEVER leaves this class. All operations on K_master happen inside it.

#include <string>
#include <vector>
#include <cstdint>

// Represents a 256-bit (32-byte) key as a byte vector
using KeyBytes = std::vector<uint8_t>;

// Represents a BLS12-381 public key (48 bytes in real BLS; we use 32-byte SHA256 simulation)
using PublicKeyBytes = std::vector<uint8_t>;

class HSM {
public:
    // Constructor: generates K_master internally using hardware RNG (AIS-31 Class P2 equivalent)
    // In real hardware this uses the HSM's internal TRNG — never software rand()
    HSM();

    // Returns H_0: the BLS12-381 public key derived as K_master * G
    // In simulation: H_0 = SHA256("H0_PUBKEY" || K_master)
    // Public — safe to broadcast and share with the TA
    PublicKeyBytes getH0() const;

    // Returns C_0: the chain anchor for pseudonym derivation
    // C_0 = HMAC-SHA256(K_master, "CHAIN" || VIN)
    // NEVER leaves the HSM in normal operation
    KeyBytes getC0(const std::string& vin) const;

    // Derives the per-epoch session seed
    // S_session = HKDF-Extract(K_master, "Session_" || epoch)
    // This is the only value passed to the application processor
    KeyBytes deriveSessionSeed(uint32_t epoch) const;

    // Signs a registration nonce for TA proof-of-possession
    // In real BLS: sign(K_master, nonce). Here: HMAC-SHA256(K_master, nonce)
    KeyBytes signNonce(const KeyBytes& nonce) const;

    // Verifies that a given public key H matches this HSM's K_master
    // Used internally for self-consistency checks
    bool verifyOwnPublicKey(const PublicKeyBytes& h) const;

    // Returns the VIN this HSM is bound to (set at manufacture)
    std::string getVIN() const { return vin_; }

    // Binds VIN at manufacture time — called once by TrustedAuthority
    void bindVIN(const std::string& vin);

private:
    KeyBytes k_master_;      // THE root secret — never exposed outside this class
    std::string vin_;        // Vehicle Identification Number bound at manufacture
    bool vin_bound_;         // Safety flag: operations blocked until VIN is bound

    // Internal helper: HMAC-SHA256(key, data)
    KeyBytes hmacSHA256(const KeyBytes& key, const std::string& data) const;

    // Internal helper: generates cryptographically random bytes (AIS-31 equivalent)
    KeyBytes generateRandomBytes(size_t len) const;
};

#endif // HSM_H