#ifndef REVOCATIONPROTOCOL_H
#define REVOCATIONPROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

struct RevocationProposal {
    std::string proposerId;
    std::string suspectPseudonym;
    std::string evidence;
    uint32_t epoch = 0;
    double evidenceScore = 0.0;

    bool isValid() const;
};

struct RevocationUpdate {
    std::string revokedFingerprint;
    uint32_t newEpoch = 0;
    std::string clusterId;
    std::vector<uint8_t> thresholdSignature;
    bool authenticated = false;

    bool isValid() const;
};

class RevocationProtocol {
public:
    static RevocationProposal makeProposal(
        const std::string& proposerId,
        const std::string& suspectPseudonym,
        const std::string& evidence,
        uint32_t epoch,
        double evidenceScore);

    static RevocationUpdate makeUpdate(
        const std::string& revokedFingerprint,
        uint32_t newEpoch,
        const std::string& clusterId,
        const std::vector<uint8_t>& thresholdSignature);

    static bool acceptsProposal(const RevocationProposal& proposal,
                                double minimumEvidenceScore = 0.85);
};

#endif // REVOCATIONPROTOCOL_H
