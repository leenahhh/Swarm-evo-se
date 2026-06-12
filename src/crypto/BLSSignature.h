#ifndef BLSSIGNATURE_H
#define BLSSIGNATURE_H

// BLSSignature.h — BLS12-381 Threshold Signature Simulation
//
// Real BLS12-381: Boneh-Lynn-Shacham 2004, same curve as Ethereum 2.0
// Key property: ANY number of signatures aggregate into ONE 48-byte signature
// This is NOT lossy compression — the aggregate is mathematically equivalent
// to all individual signatures.
//
// Simulation: HMAC-SHA256 based aggregation with same interface
// Partial sig: 32 bytes. Aggregated sig: 32 bytes (regardless of k).

#include <vector>
#include <string>
#include <cstdint>

using KeyBytes = std::vector<uint8_t>;

// A partial BLS signature from one validator vehicle
struct PartialSignature {
    std::string vehicleId;    // Which vehicle produced this
    std::string pseudonym;    // Pseudonym being validated
    uint32_t    epoch;        // Epoch at time of signing
    KeyBytes    sigBytes;     // 32-byte partial signature
    std::string h0;           // Signer's H_0 (for verification)
};

// An aggregated threshold signature (Sigma_threshold)
struct AggregatedSignature {
    KeyBytes    sigBytes;     // 32-byte aggregated signature (same size as one partial)
    uint32_t    signerCount;  // How many partials were aggregated
    uint32_t    epoch;        // Epoch this covers
    std::string targetPseudonym; // What was being validated
    bool        valid;        // Was aggregation successful?

    std::string serialise() const;
};

class BLSEngine {
public:
    BLSEngine() = default;

    // Generate a partial signature on a pseudonym candidate
    // vehiclePrivKey: this vehicle's signing key (derived from S_session)
    // message: the pseudonym + epoch being validated
    PartialSignature sign(
        const std::string& vehicleId,
        const KeyBytes& vehiclePrivKey,
        const std::string& pseudonym,
        uint32_t epoch,
        const std::string& h0
    ) const;

    // Aggregate k partial signatures into one Sigma_threshold
    // Real BLS: sigma_agg = sigma_1 + sigma_2 + ... + sigma_k (elliptic curve addition)
    // Simulation: HMAC chain combining all partials
    AggregatedSignature aggregate(
        const std::vector<PartialSignature>& partials
    ) const;

    // Verify an aggregated signature
    // Only needs public information — the list of signer H_0s and the message
    bool verifyAggregate(
        const AggregatedSignature& sig,
        const std::vector<std::string>& signerH0s,
        const std::string& pseudonym,
        uint32_t epoch
    ) const;

    // Verify a single partial signature
    bool verifyPartial(
        const PartialSignature& sig,
        const std::string& signerH0
    ) const;

private:
    KeyBytes hmac(const KeyBytes& key, const std::string& data) const;
    KeyBytes sha256(const std::string& data) const;
};

#endif // BLSSIGNATURE_H