#include "ACF.h"
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// --- Constructor ---
ACF::ACF(size_t capacity, uint32_t maxStaleness)
    : currentEpoch_(0), maxStaleness_(maxStaleness),
      capacity_(capacity), authenticated_(false) {}

// --- Insert a revoked pseudonym ---
bool ACF::insert(const RevocationEntry& entry) {
    if (entries_.size() >= capacity_) {
        return false;  // Filter full — in production: expand or use cascading filter
    }
    // Only insert if the entry carries a threshold signature
    // (prevents single malicious vehicle from injecting false revocations)
    if (!entry.authenticated) {
        return false;  // Reject unauthenticated entries
    }
    entries_[entry.pseudonymFingerprint] = entry;
    return true;
}

// --- Check membership ---
// Cuckoo filter guarantee: zero false positives for deletion
// If this returns false, the vehicle is DEFINITIVELY not revoked
bool ACF::contains(const std::string& fingerprint) const {
    return entries_.find(fingerprint) != entries_.end();
}

// --- Remove an entry ---
bool ACF::remove(const std::string& fingerprint) {
    return entries_.erase(fingerprint) > 0;
}

// --- Advance epoch after verified revocation update ---
void ACF::advanceEpoch(uint32_t newEpoch, const KeyBytes& newThresholdSig) {
    currentEpoch_ = newEpoch;
    currentThresholdSig_ = newThresholdSig;
    // Mark as authenticated only if signature is non-empty
    // (in production: verify BLS aggregate sig here)
    authenticated_ = !newThresholdSig.empty();
}

// --- Freshness check ---
// A filter is fresh if it is within maxStaleness_ epochs of the current time.
// A stale filter might be missing recent revocations — treat results with caution.
bool ACF::isFresh(uint32_t currentEpoch) const {
    if (currentEpoch < currentEpoch_) return false;  // Clock went backwards — suspicious
    return (currentEpoch - currentEpoch_) <= maxStaleness_;
}

// --- Authentication check ---
bool ACF::isAuthenticated() const {
    return authenticated_ && !currentThresholdSig_.empty();
}

// --- State hash: SHA256 over sorted fingerprints ---
// This is what the threshold signature is computed over.
// Sorting ensures determinism regardless of insertion order.
std::string ACF::getStateHash() const {
    return computeStateHash();
}

std::string ACF::computeStateHash() const {
    // Collect and sort all fingerprints
    std::vector<std::string> fps;
    fps.reserve(entries_.size());
    for (const auto& [fp, _] : entries_) fps.push_back(fp);
    std::sort(fps.begin(), fps.end());

    // Concatenate into one string
    std::string combined;
    for (const auto& fp : fps) combined += fp;
    combined += std::to_string(currentEpoch_);

    // SHA256 of combined
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(combined.c_str()),
           combined.size(), hash);

    // Return as hex string
    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return oss.str();
}

// --- Serialise for V2V gossip ---
// Format: epoch|stateHash|fp1,fp2,fp3,...
std::string ACF::serialise() const {
    std::ostringstream oss;
    oss << currentEpoch_ << "|" << computeStateHash() << "|";
    bool first = true;
    for (const auto& [fp, entry] : entries_) {
        if (!first) oss << ",";
        oss << fp << ":" << entry.epoch << ":" << entry.clusterId;
        first = false;
    }
    return oss.str();
}

// --- Export all entries ---
std::vector<RevocationEntry> ACF::getAllEntries() const {
    std::vector<RevocationEntry> result;
    for (const auto& [_, entry] : entries_) result.push_back(entry);
    return result;
}