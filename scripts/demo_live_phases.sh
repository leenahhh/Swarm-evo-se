#!/usr/bin/env bash

TRACE="/tmp/urban_full_demo_trace.txt"

touch "$TRACE"

echo "============================================================"
echo " SWARM EVO-SE LIVE PHASE TRACE"
echo " Watching: $TRACE"
echo "============================================================"
echo
echo "Legend:"
echo "  node[0] = Legitimate Sender"
echo "  node[1] = Legitimate Receiver"
echo "  node[2] = Validator 1 / Revocation Proposer"
echo "  node[3] = Validator 2"
echo "  node[4] = Validator 3"
echo "  node[5] = Malicious Vehicle"
echo "============================================================"
echo

tail -n +1 -f "$TRACE" | awk '
/PHASE_2_FIRST_BOOT/ {
    print "\n[PHASE 2: FIRST BOOT] " $0
    fflush()
}

/PHASE_3_PSEUDONYM_GENERATION|TX real CANDIDATE_MSG/ {
    print "\n[PHASE 3A: PSEUDONYM CANDIDATE BROADCAST] " $0
    fflush()
}

/proofValid=YES|proofValid=NO|HARD_DROP invalid_zk/ {
    print "\n[PHASE 3B: ZERO-KNOWLEDGE PROOF VALIDATION] " $0
    fflush()
}

/Scheduled PARTIAL_SIG_MSG|TX real PARTIAL_SIG_MSG|collected=1\/3|collected=2\/3|collected=3\/3|threshold signature aggregated|Boneh-Lynn-Shacham threshold signature aggregated/ {
    print "\n[PHASE 3C: SWARM ACCEPTANCE / THRESHOLD SIGNATURE] " $0
    fflush()
}

/PHASE_3_PSEUDONYM_ACTIVATION|New pseudonym activated/ {
    print "\n[PHASE 3D: PSEUDONYM ACTIVATION] " $0
    fflush()
}

/PHASE_4_SAFETY_TRANSMISSION|SAFETY_MSG ACCEPTED/ {
    print "\n[PHASE 4-5: SAFETY MESSAGE AUTHENTICATION] " $0
    fflush()
}

/MALICIOUS_BEHAVIOUR|failures=1|failures=2/ {
    print "\n[MALICIOUS DETECTION] " $0
    fflush()
}

/Revocation threshold trigger|REVOKE_PROPOSAL|Scheduled REVOKE_VOTE|TX real REVOKE_VOTE|RX REVOKE_VOTE|votes=1\/3|votes=2\/3|votes=3\/3|Revocation threshold reached/ {
    print "\n[REVOCATION CONSENSUS] " $0
    fflush()
}

/SIGNED_ACF_UPDATE|Local ACF updated|updated local ACF|trustCache=invalidated/ {
    print "\n[ACF UPDATE / REVOCATION PROPAGATION] " $0
    fflush()
}

/HARD_DROP SAFETY_MSG/ {
    print "\n[FINAL MALICIOUS MESSAGE DROP] " $0
    fflush()
}
'
