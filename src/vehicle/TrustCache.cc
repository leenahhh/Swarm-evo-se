#include "TrustCache.h"
#include <ctime>

TrustCache::TrustCache(uint32_t defaultTTL)
    : defaultTTL_(defaultTTL), hits_(0), misses_(0) {}

void TrustCache::insert(const std::string& pseudonym, uint32_t acfEpoch,
                        const std::string& cluster) {
    CacheEntry entry;
    entry.pseudonym       = pseudonym;
    entry.acfEpoch        = acfEpoch;
    entry.insertTime      = std::time(nullptr);
    entry.ttlSeconds      = defaultTTL_;
    entry.vehicleCluster  = cluster;
    entry.isMalicious     = false;
    cache_[pseudonym]     = entry;
}

bool TrustCache::check(const std::string& pseudonym, uint32_t currentAcfEpoch) const {
    auto it = cache_.find(pseudonym);
    if (it == cache_.end()) {
        ++misses_;
        return false;  // Not in cache
    }

    const CacheEntry& entry = it->second;

    // Invalidate if ACF epoch has advanced (revocation occurred)
    if (entry.acfEpoch != currentAcfEpoch) {
        ++misses_;
        return false;
    }

    // Invalidate if TTL expired
    time_t now = std::time(nullptr);
    if (now - entry.insertTime > entry.ttlSeconds) {
        ++misses_;
        return false;
    }

    // Invalidate if flagged as malicious
    if (entry.isMalicious) {
        ++misses_;
        return false;
    }

    ++hits_;
    return true;  // Valid cache hit — 0.1ms path
}

void TrustCache::invalidateAll() {
    cache_.clear();  // Wipe everything on ACF epoch advance
}

void TrustCache::markMalicious(const std::string& pseudonym) {
    auto it = cache_.find(pseudonym);
    if (it != cache_.end()) {
        it->second.isMalicious = true;
    }
}

double TrustCache::getHitRate() const {
    uint64_t total = hits_ + misses_;
    if (total == 0) return 0.0;
    return static_cast<double>(hits_) / total;
}