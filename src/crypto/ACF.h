#ifndef ACF_H
#define ACF_H

// ACF.h — Authenticated Cuckoo Filter
//
// This is the revocation list. Every vehicle maintains one locally.
// Key properties vs a Bloom Filter:
//   - Zero false positives for deletion (Bloom can't delete safely)
//   - If the ACF says a vehicle is NOT revoked, that is a hard guarantee
//   - The filter is threshold-signed: only valid if k vehicles agreed to update it
//
// Structure: fingerprint table with cuckoo hashing + epoch + BLS threshold signature

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <cstdint>
#include <functional>

using KeyBytes = std::vector<uint8_t>;

// One entry in the revocation table
struct RevocationEntry {
    std::string pseudonymFingerprint;  // SHA256 of the revoked pseudonym (hex)
    uint32_t    epoch;                 // Epoch at which this revocation was inserted
    std::string clusterId;             // Which vehicle cluster issued this revocation
    KeyBytes    thresholdSig;          // Aggregated BLS signature from k validators
    bool        authenticated;         // True only if threshold sig verifies
};

class ACF {
public:
    // Initialise empty filter
    // capacity: max number of fingerprints (default 10,000)
    // maxStaleness: how many epochs before filter is considered stale (default 3)
    ACF(size_t capacity = 10000, uint32_t maxStaleness = 3);

    // --- Core operations ---

    // Insert a revoked pseudonym fingerprint (called after epidemic update verified)
    // Returns false if capacity exceeded
    bool insert(const RevocationEntry& entry);

    // Check if a pseudonym fingerprint is in the revocation set
    // Returns true = REVOKED (hard guarantee: no false positives)
    // Returns false = NOT revoked (definitive)
    bool contains(const std::string& fingerprint) const;

    // Remove a fingerprint (needed for whitelist corrections — rare but possible)
    bool remove(const std::string& fingerprint);

    // --- Epoch and authentication ---

    // Advance the filter epoch (called when a new revocation update is applied)
    void advanceEpoch(uint32_t newEpoch, const KeyBytes& newThresholdSig);

    // Check if the filter is fresh (within maxStaleness epochs of current time)
    bool isFresh(uint32_t currentEpoch) const;

    // Check if the filter carries a valid threshold signature
    bool isAuthenticated() const;

    // Get current epoch
    uint32_t getEpoch() const { return currentEpoch_; }

    // Get fingerprint of current filter state (used for signature binding check)
    std::string getStateHash() const;

    // Get size (number of revoked entries)
    size_t size() const { return entries_.size(); }

    // --- Serialisation for V2V gossip transmission ---
    std::string serialise() const;
    static ACF deserialise(const std::string& data);

    // Export all entries (for dashboard display)
    std::vector<RevocationEntry> getAllEntries() const;

private:
    // The actual revocation table: fingerprint -> entry
    std::unordered_map<std::string, RevocationEntry> entries_;

    uint32_t    currentEpoch_;       // Current filter epoch
    uint32_t    maxStaleness_;       // Max epochs before considered stale
    size_t      capacity_;           // Max entries
    KeyBytes    currentThresholdSig_;// Threshold sig over current filter state
    bool        authenticated_;      // Is the current sig valid?

    // Internal: compute SHA256 of all fingerprints sorted (deterministic state hash)
    std::string computeStateHash() const;
};

#endif // ACF_H