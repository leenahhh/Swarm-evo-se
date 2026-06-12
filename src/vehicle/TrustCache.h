#ifndef TRUSTCACHE_H
#define TRUSTCACHE_H

// TrustCache.h — Short-term trust cache for recently verified vehicles
//
// After full verification (ZK proof + ACF check + signature), a vehicle's
// pseudonym fingerprint is cached for ttlSeconds (default 30s).
//
// Effect: >90% of incoming messages resolved in ~0.1ms (cache hit)
//         instead of full 18ms pipeline.
//
// Invalidation: ALL entries are wiped when ACF epoch advances
// (a revocation occurred — cached trusted vehicles must be re-verified)

#include <string>
#include <unordered_map>
#include <cstdint>
#include <ctime>

struct CacheEntry {
    std::string pseudonym;    // The cached pseudonym
    uint32_t    acfEpoch;     // ACF epoch when this entry was added
    time_t      insertTime;   // Wall-clock time of insertion
    uint32_t    ttlSeconds;   // Time-to-live in seconds
    std::string vehicleCluster; // Which cluster validated this vehicle
    bool        isMalicious;  // Set to true if flagged by revocation system
};

class TrustCache {
public:
    TrustCache(uint32_t defaultTTL = 30);

    // Add a verified vehicle to the cache
    void insert(const std::string& pseudonym, uint32_t acfEpoch,
                const std::string& cluster);

    // Check if pseudonym is in cache and still valid
    // Returns true = trusted (cache hit, 0.1ms path)
    // Returns false = not in cache or expired (full pipeline needed)
    bool check(const std::string& pseudonym, uint32_t currentAcfEpoch) const;

    // Invalidate ALL entries (called when ACF epoch advances)
    void invalidateAll();

    // Mark a pseudonym as malicious (called by revocation system)
    void markMalicious(const std::string& pseudonym);

    // Get cache size (for dashboard)
    size_t size() const { return cache_.size(); }

    // Get hit rate statistics
    double getHitRate() const;

private:
    std::unordered_map<std::string, CacheEntry> cache_;
    uint32_t defaultTTL_;

    // Statistics
    mutable uint64_t hits_;
    mutable uint64_t misses_;
};

#endif // TRUSTCACHE_H