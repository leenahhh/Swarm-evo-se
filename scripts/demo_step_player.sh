#!/usr/bin/env bash

TA_TRACE="/tmp/phase1_ta_demo_trace.txt"
NODE_TRACE="/tmp/urban_full_demo_trace.txt"

pause() {
    echo
    read -rp "Press Enter to continue to the next step..."
}

section() {
    clear
    echo "============================================================"
    echo "$1"
    echo "============================================================"
    echo
}

show_lines() {
    local file="$1"
    local pattern="$2"

    if [ ! -f "$file" ]; then
        echo "Missing trace file: $file"
        echo "Run the simulation first."
        pause
        return
    fi

    grep -E "$pattern" "$file" || echo "No matching lines found for this step."
    pause
}

section "STEP 1: TA REGISTRATION AND HSM PROOF-OF-POSSESSION"
echo "Explain: The TA verifies vehicle identity, checks the HSM certificate chain, sends a nonce, and verifies proof-of-possession."
echo
show_lines "$TA_TRACE" "registration request|physical vehicle identity|HSM manufacturer|Hardware Security Module|Public key anchor|challenge nonce|proof-of-possession|Enrolment certificate|Public system parameters|Cluster assignment|Bootstrap PID|Starter Pack|TA secrecy|REGISTRATION SUCCESSFUL"

section "STEP 2: VEHICLE FIRST BOOT"
echo "Explain: Each vehicle prepares local security state: HSM, anchors, ACF, session seed, pseudonym, ZK proof pool, BLS keys and trust cache."
echo
show_lines "$NODE_TRACE" "PHASE_2_FIRST_BOOT|HSM ready|anchors derived|Authenticated Cuckoo Filter|session seed|first pseudonym|Zero-Knowledge proof pool|BLS signing keys|trust cache"

section "STEP 3: LEGITIMATE PSEUDONYM CANDIDATE BROADCAST"
echo "Explain: The legitimate sender broadcasts a real CANDIDATE_MSG over the simulated wireless channel."
echo
show_lines "$NODE_TRACE" "TX real CANDIDATE_MSG|RX_DISPATCH.*CANDIDATE_MSG"

section "STEP 4: VALIDATOR ZK PROOF VERIFICATION"
echo "Explain: Validators verify the ZK proof attached to the candidate pseudonym."
echo
show_lines "$NODE_TRACE" "PHASE_3_SWARM_VALIDATION.*proofValid=YES"

section "STEP 5: PARTIAL SIGNATURE COLLECTION AND SWARM ACCEPTANCE"
echo "Explain: Validators send partial signatures. The sender collects 3/3 and aggregates the threshold signature."
echo
show_lines "$NODE_TRACE" "TX real PARTIAL_SIG_MSG|RX PARTIAL_SIG_MSG|collected=1/3|collected=2/3|collected=3/3|threshold signature|New pseudonym activated"

section "STEP 6: AUTHENTICATED SAFETY MESSAGE ACCEPTED"
echo "Explain: The accepted pseudonym is used to send a SAFETY_MSG. Receivers verify it and accept it."
echo
show_lines "$NODE_TRACE" "LEGIT_SENDER.*SAFETY|SAFETY_MSG ACCEPTED|ACF not revoked|signature valid|Proof of Swarm Acceptance valid"

section "STEP 7: MALICIOUS INVALID ZK DETECTION"
echo "Explain: The malicious node sends invalid ZK proofs. Validators reject them and record failures."
echo
show_lines "$NODE_TRACE" "MALICIOUS.*invalid ZK|proofValid=NO|HARD_DROP invalid_zk|failures=1|failures=2"

section "STEP 8: REVOCATION PROPOSAL"
echo "Explain: After repeated invalid ZK failures, Validator 1 starts revocation and broadcasts REVOKE_PROPOSAL."
echo
show_lines "$NODE_TRACE" "Revocation threshold trigger|Stored proposer self-vote|TX real REVOKE_PROPOSAL|RX real REVOKE_PROPOSAL|Scheduled REVOKE_VOTE"

section "STEP 9: REVOCATION VOTING AND THRESHOLD DECISION"
echo "Explain: Validator 2 and Validator 3 vote. Validator 1 collects votes until 3/3 is reached."
echo
show_lines "$NODE_TRACE" "TX real REVOKE_VOTE|RX REVOKE_VOTE|votes=2/3|votes=3/3|Revocation threshold reached"

section "STEP 10: SIGNED ACF UPDATE PROPAGATION"
echo "Explain: After threshold revocation, a signed ACF update is broadcast and received by neighbouring vehicles."
echo
show_lines "$NODE_TRACE" "Local ACF updated|TX real SIGNED_ACF_UPDATE|RX SIGNED_ACF_UPDATE|updated local ACF|newACFEpoch"

section "STEP 11: POST-REVOCATION MALICIOUS SAFETY MESSAGE HARD-DROP"
echo "Explain: The malicious vehicle sends a safety message after revocation. Receivers get the packet but hard-drop it."
echo
show_lines "$NODE_TRACE" "post-revocation|TX real SAFETY_MSG|RX_DISPATCH.*SAFETY_MSG|HARD_DROP SAFETY_MSG"

section "STEP 12: FINAL TIMING REPORT"
echo "Explain: This summarises the full protocol execution and confirms that all expected evidence lines were found."
echo
python3 scripts/demo_timing_report.py || echo "Timing report script failed or is missing."
echo
echo "============================================================"
echo "END OF STEP-BY-STEP DEMO"
echo "============================================================"
