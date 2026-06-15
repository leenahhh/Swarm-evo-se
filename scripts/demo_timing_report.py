#!/usr/bin/env python3
import re
from pathlib import Path

TRACE = Path("/tmp/urban_full_demo_trace.txt")

if not TRACE.exists():
    raise SystemExit("ERROR: /tmp/urban_full_demo_trace.txt not found. Run UrbanEndToEndDemo first.")

lines = TRACE.read_text(errors="ignore").splitlines()

checks = [
    ("Phase 2 first boot begins",
     r"PHASE_2_FIRST_BOOT.*Step 1"),

    ("Legitimate pseudonym candidate sent",
     r"LEGIT_SENDER.*TX real CANDIDATE_MSG"),

    ("Validator 1 ZK proof accepted",
     r"VALIDATOR_1.*proofValid=YES"),

    ("Validator 2 ZK proof accepted",
     r"VALIDATOR_2.*proofValid=YES"),

    ("Validator 3 ZK proof accepted",
     r"VALIDATOR_3.*proofValid=YES"),

    ("Swarm partial signature 1 collected",
     r"collected=1/3"),

    ("Swarm partial signature 2 collected",
     r"collected=2/3"),

    ("Swarm partial signature 3 collected",
     r"collected=3/3"),

    ("Swarm threshold signature aggregated",
     r"threshold signature aggregated|Boneh-Lynn-Shacham threshold signature aggregated"),

    ("New pseudonym activated",
     r"New pseudonym activated"),

    ("Legitimate safety message accepted",
     r"LEGIT_RECEIVER.*SAFETY_MSG ACCEPTED"),

    ("Malicious invalid ZK failure 1 detected",
     r"HARD_DROP invalid_zk.*failures=1"),

    ("Malicious invalid ZK failure 2 detected",
     r"HARD_DROP invalid_zk.*failures=2"),

    ("Revocation proposer self-vote stored",
     r"Stored proposer self-vote.*votes=1/3"),

    ("Validator 2 revocation vote scheduled",
     r"VALIDATOR_2.*Scheduled REVOKE_VOTE"),

    ("Validator 3 revocation vote scheduled",
     r"VALIDATOR_3.*Scheduled REVOKE_VOTE"),

    ("Revocation vote 2 stored",
     r"RX REVOKE_VOTE.*votes=2/3"),

    ("Revocation vote 3 stored",
     r"RX REVOKE_VOTE.*votes=3/3"),

    ("Revocation threshold reached",
     r"Revocation threshold reached"),

    ("Local ACF updated after revocation",
     r"Local ACF updated after threshold revocation"),

    ("Signed ACF update broadcast",
     r"TX real SIGNED_ACF_UPDATE"),

    ("Signed ACF update received",
     r"RX SIGNED_ACF_UPDATE and updated local ACF"),

    ("Post-revocation malicious safety sent",
     r"MALICIOUS node attempting post-revocation safety message"),

    ("Post-revocation malicious safety transmitted",
     r"TX real SAFETY_MSG.*post-revocation malicious safety"),

    ("Post-revocation malicious safety dropped",
     r"HARD_DROP SAFETY_MSG.*post-revocation malicious safety message rejected"),
]

def extract_time(line):
    m = re.search(r"\[t=([0-9.]+)s\]", line)
    return float(m.group(1)) if m else None

def extract_node(line):
    m = re.search(r"\[(node\[[0-9]+\])\]", line)
    return m.group(1) if m else "-"

def extract_role(line):
    m = re.search(
        r"\]\[(LEGIT_SENDER|LEGIT_RECEIVER|VALIDATOR_1|VALIDATOR_2|VALIDATOR_3|MALICIOUS)\]\[",
        line
    )
    return m.group(1) if m else "-"

events = []

for label, pattern in checks:
    rx = re.compile(pattern)
    found = None

    for line in lines:
        if rx.search(line):
            found = {
                "label": label,
                "time": extract_time(line),
                "node": extract_node(line),
                "role": extract_role(line),
                "line": line
            }
            break

    if found:
        events.append(found)
    else:
        events.append({
            "label": label,
            "time": None,
            "node": "-",
            "role": "-",
            "line": "MISSING"
        })

print()
print("SWARM EVO-SE URBAN END-TO-END DEMO TIMING REPORT")
print("=" * 110)
print(f"{'Time(s)':>8} | {'Node':<8} | {'Role':<15} | Evidence")
print("-" * 110)

for event in events:
    time_text = "MISSING" if event["time"] is None else f"{event['time']:.3f}"
    print(f"{time_text:>8} | {event['node']:<8} | {event['role']:<15} | {event['label']}")

def time_of(label):
    for event in events:
        if event["label"] == label:
            return event["time"]
    return None

print()
print("KEY LATENCIES")
print("=" * 110)

latencies = [
    (
        "Pseudonym swarm acceptance latency",
        "Legitimate pseudonym candidate sent",
        "Swarm threshold signature aggregated"
    ),
    (
        "Pseudonym activation to receiver acceptance",
        "New pseudonym activated",
        "Legitimate safety message accepted"
    ),
    (
        "Second malicious ZK failure to revocation threshold",
        "Malicious invalid ZK failure 2 detected",
        "Revocation threshold reached"
    ),
    (
        "Revocation threshold to signed ACF broadcast",
        "Revocation threshold reached",
        "Signed ACF update broadcast"
    ),
    (
        "Signed ACF broadcast to malicious hard-drop",
        "Signed ACF update broadcast",
        "Post-revocation malicious safety dropped"
    ),
]

for name, start_label, end_label in latencies:
    start = time_of(start_label)
    end = time_of(end_label)

    if start is None or end is None:
        print(f"{name}: MISSING")
    else:
        print(f"{name}: {end - start:.3f}s simulation time")

missing = [event["label"] for event in events if event["time"] is None]

print()
print("FINAL RESULT")
print("=" * 110)

if missing:
    print("INCOMPLETE: Some expected evidence lines are missing:")
    for item in missing:
        print(f"- {item}")
else:
    print("SUCCESS: All expected legitimate and malicious-path evidence lines were found.")
    print("The demo proves pseudonym generation, swarm acceptance, authentication, revocation, ACF update, and malicious hard-drop.")
