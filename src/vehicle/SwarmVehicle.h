#ifndef SWARMVEHICLE_H
#define SWARMVEHICLE_H

// SwarmVehicle.h — The main OMNeT++ vehicle module
//
// Each simulated vehicle IS this class. It runs the complete Swarm Evo-SE protocol:
//   - Phase 1: Manufacture (TA interaction, HSM setup)
//   - Phase 2: First boot (all 8 initialisation steps)
//   - Phase 3: Pseudonym generation + swarm validation
//   - Phase 4: Safety message transmission
//   - Phase 5: Receiver processing + revocation gate
//
// Malicious vehicle behaviour is toggled via isMalicious_ flag.

#include <omnetpp.h>
#include <veins/modules/application/ieee80211p/DemoBaseApplLayer.h>
#include "../crypto/HSM.h"
#include "../crypto/ACF.h"
#include "../crypto/ZKProof.h"
#include "../crypto/BLSSignature.h"
#include "../protocol/Messages_m.h"
#include "PseudonymEngine.h"
#include "TrustCache.h"
#include "ProofPool.h"
#include <map>
#include <vector>
#include <memory>
#include <string>

using namespace omnetpp;
using namespace veins;

class SwarmVehicle : public DemoBaseApplLayer {
public:
    ~SwarmVehicle() override;
    // Malicious behaviour types for testing
    enum class MaliciousMode {
        NONE,              // Legitimate vehicle
        REPLAY_ATTACK,     // Replays old Proof of Swarm Acceptance
        SYBIL_ATTACK,      // Claims multiple identities
        FALSE_REVOCATION,  // Tries to falsely revoke legitimate vehicles
        INVALID_ZK,        // Broadcasts invalid ZK proofs
        GHOST_VEHICLE,     // Claims impossible positions/speeds
        COLLUDING          // Works with other malicious vehicles
    };

protected:
    // --- OMNeT++ lifecycle ---
    void initialize(int stage) override;
    void finish() override;
    void handleSelfMsg(cMessage* msg) override;
    void handleLowerMsg(cMessage* msg) override;
    void onWSM(BaseFrame1609_4* wsm) override;
    void onBSM(DemoSafetyMessage* bsm) override;
    int numInitStages() const override { return 3; }

private:
    // ============================================================
    // Phase 1 & 2: Manufacture and First Boot
    // ============================================================
    void performManufacture();     // TA interaction at t=0
    void performFirstBoot();       // All 8 init steps
    void initHSM();                // Step 1: K_master generation
    void deriveAnchors();          // Step 2: H_0 and C_0
    void initACF();                // Step 3: Empty filter
    void deriveSessionSeed();      // Step 4: S_session for current epoch
    void initPseudonymEngine();    // Step 5: Load P_i derivation
    void precomputeProofPool();    // Step 6: ZK proof pre-computation
    void initBLSKeys();            // Step 7: BLS key pair
    void initTrustCache();         // Step 8: Trust cache

    // ============================================================
    // Phase 3: Pseudonym Generation and Swarm Validation
    // ============================================================
    void requestNewPseudonym();            // Broadcast CANDIDATE_MSG
    void handleCandidateMsg(swarmevose::CandidateMsg* msg);   // Validate and sign
    void handlePartialSig(swarmevose::PartialSigMsg* msg);    // Collect signatures
    void tryAggregateSigs();               // Aggregate when threshold reached
    void activatePseudonym(const std::string& pseudo); // Switch pseudonym
    uint32_t computeThreshold() const;    // Adaptive k calculation

    // ============================================================
    // Phase 4: Message Transmission
    // ============================================================
    void sendSafetyMessage(const std::string& eventType);

    // ============================================================
    // Phase 5: Receiver Pipeline
    // ============================================================
    void handleSafetyMsg(swarmevose::SafetyMsg* msg);
    bool checkTrustCache(const std::string& pseudo);     // Step: 0.1ms path
    bool verifySignature(swarmevose::SafetyMsg* msg);    // Step 13
    bool verifyProofOfSwarmAcceptance(swarmevose::SafetyMsg* msg); // Step 15
    void applyGraduatedResponse(swarmevose::SafetyMsg* msg,
                                const std::string& result); // Step 16

    // ============================================================
    // Revocation Protocol
    // ============================================================
    void handleRevokeProposal(swarmevose::RevokeProposalMsg* msg);
    void handleRevokeVote(swarmevose::RevokeVoteMsg* msg);
    void handleSignedACFUpdate(swarmevose::SignedAcfUpdateMsg* msg);
    void proposRevocation(const std::string& suspect,
                          const std::string& evidence, double confidence);
    void broadcastACFUpdate(const std::string& fingerprint);

    // ============================================================
    // Malicious Behaviour Injection
    // ============================================================
    void injectMaliciousBehaviour();       // Called if isMalicious_
    void replayOldProof();                 // Replay attack
    void claimFakeIdentity();              // Sybil
    void sendFalseRevocationProposal();    // False revocation
    void broadcastInvalidZK();             // Invalid proof flood
    void claimImpossiblePosition();        // Ghost vehicle

    // ============================================================
    // Timers
    // ============================================================
    cMessage* beaconTimer_;          // Periodic safety beacon
    cMessage* epochTimer_;           // Epoch rollover
    cMessage* preActivationTimer_;   // 60s before epoch end: request new pseudo
    cMessage* proofPoolTimer_;       // Background ZK pre-computation

    // In the private section of SwarmVehicle.h, add:
    std::string lastSigma_;                  // Last Sigma_threshold from swarm validation
    uint32_t    filterEpochAtSigning_ = 0;  // ACF epoch when last proof was issued
    std::vector<std::string> recentNeighbourPseudonyms_; // For false revocation targeting
    // Sign a message payload with current ephemeral key
    KeyBytes signPayload(const std::string& payload);
    // Get neighbour count from Veins connection manager
    uint32_t getNeighbourCount() const;

    // ============================================================
    // State
    // ============================================================
    std::unique_ptr<HSM>             hsm_;
    std::unique_ptr<ACF>             acf_;
    std::unique_ptr<PseudonymEngine> pseudoEngine_;
    std::unique_ptr<TrustCache>      trustCache_;
    std::unique_ptr<ProofPool>       proofPool_;
    ZKProofEngine                    zkEngine_;
    BLSEngine                        blsEngine_;

    std::string vehicleId_;           // True identity (VIN equivalent)
    std::string currentPseudonym_;    // Active anonymous identity
    std::string candidatePseudonym_;  // Pseudonym being validated
    std::string h0_;                  // This vehicle's certified public key
    KeyBytes    c0_;                  // Chain anchor (internal)
    KeyBytes    currentSigningKey_;   // Ephemeral key for current pseudonym
    std::string clusterId_;           // Current cluster membership

    // ============================================================
    // Phase 1 manufacture/registration artefacts
    // These represent the Starter Pack loaded into the OBU.
    // ============================================================
    bool physicalIdentityVerified_ = false;
    bool hsmManufacturerChainVerified_ = false;
    bool proofOfPossessionVerified_ = false;
    bool starterPackLoaded_ = false;

    std::string hsmManufacturerCertChain_;
    std::string enrolmentCertificateFingerprint_;
    std::string enrolmentCertificateSerial_;
    std::string phase1ExpiryInfo_;
    std::string starterPackId_;
    std::vector<std::string> bootstrapPIDs_;

    uint32_t    currentEpoch_;
    uint32_t    neighbourCount_;      // For adaptive threshold k
    bool        isMalicious_;
    bool        demoTrace_ = false;
    std::string demoRole_;
    MaliciousMode maliciousMode_;
    std::string maliciousModeName_;
    bool        isRevoked_;           // Has this vehicle been revoked?

    // Collected partial signatures for current candidate
    std::vector<PartialSignature> collectedPartials_;

    // Collected revocation votes per suspect
    std::map<std::string, std::vector<PartialSignature>> revokeVotes_;

    // Signature failure counter (per sender pseudonym, for auto-revocation)
    std::map<std::string, int> sigFailureCount_;

    // Recently observed neighbours based on received DSRC packets
    std::map<std::string, simtime_t> recentNeighbourSeen_;
    void updateObservedNeighbours();

    // Dashboard WebSocket client
    void emitDashboardEvent(const std::string& eventType,
                            const std::string& data);

    // Statistics
    long msgSent_, msgReceived_, msgDropped_, cacheHits_, revocationsIssued_;

    // Helper: convert bytes to hex
    std::string toHex(const KeyBytes& b) const;
    std::string computeFingerprint(const std::string& pseudo) const;
};

#endif // SWARMVEHICLE_H
