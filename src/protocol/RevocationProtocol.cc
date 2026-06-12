#include "RevocationProtocol.h"

#include <algorithm>

bool RevocationProposal::isValid() const {
    return !proposerId.empty() &&
           !suspectPseudonym.empty() &&
           !evidence.empty() &&
           evidenceScore >= 0.0 &&
           evidenceScore <= 1.0;
}

bool RevocationUpdate::isValid() const {
    return authenticated &&
           !revokedFingerprint.empty() &&
           !clusterId.empty() &&
           !thresholdSignature.empty();
}

RevocationProposal RevocationProtocol::makeProposal(
    const std::string& proposerId,
    const std::string& suspectPseudonym,
    const std::string& evidence,
    uint32_t epoch,
    double evidenceScore) {
    RevocationProposal proposal;
    proposal.proposerId = proposerId;
    proposal.suspectPseudonym = suspectPseudonym;
    proposal.evidence = evidence;
    proposal.epoch = epoch;
    proposal.evidenceScore = std::clamp(evidenceScore, 0.0, 1.0);
    return proposal;
}

RevocationUpdate RevocationProtocol::makeUpdate(
    const std::string& revokedFingerprint,
    uint32_t newEpoch,
    const std::string& clusterId,
    const std::vector<uint8_t>& thresholdSignature) {
    RevocationUpdate update;
    update.revokedFingerprint = revokedFingerprint;
    update.newEpoch = newEpoch;
    update.clusterId = clusterId;
    update.thresholdSignature = thresholdSignature;
    update.authenticated = !thresholdSignature.empty();
    return update;
}

bool RevocationProtocol::acceptsProposal(
    const RevocationProposal& proposal,
    double minimumEvidenceScore) {
    return proposal.isValid() &&
           proposal.evidenceScore >=
               std::clamp(minimumEvidenceScore, 0.0, 1.0);
}
