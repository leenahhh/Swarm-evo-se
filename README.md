# Swarm Evo-SE: Infrastructure-Free VANET Authentication, Pseudonym Validation and Revocation

## Description

Swarm Evo-SE is an infrastructure-free Vehicular Ad Hoc Network (VANET) security prototype. It demonstrates Trusted Authority (TA) registration, Hardware Security Module (HSM)-rooted trust, pseudonym generation, Zero-Knowledge (ZK) proof validation, swarm-based threshold acceptance, authenticated safety-message transmission, malicious node detection, revocation voting, signed ACF update propagation, and post-revocation hard-drop enforcement.

## Technology Stack

- Ubuntu / WSL2 Ubuntu
- OMNeT++ 6.1
- Veins
- SUMO
- C++17
- Python 3
- Bash scripts

## Project Structure

- `src/` - C++ source code, message definitions, NED modules, and protocol components.
- `simulations/swarm_evo_se/` - OMNeT++ simulation configurations and network definitions.
- `scenarios/` - SUMO maps, routes, traffic definitions, and scenario assets.
- `scripts/` - Python and Bash utilities for running demos and generating reports.
- `results/` - Generated simulation logs, vectors, scalars, and timing reports.
- `tests/` - Automated and manual protocol tests.

## Prerequisites

- OMNeT++ 6.1
- Veins
- SUMO
- Python 3
- GNU Make
- `g++` with C++17 support
- Linux or WSL2 Ubuntu environment

## Environment Setup

```bash
export OMNETPP="$HOME/omnetpp-6.1"
export VEINS="$HOME/veins"
export SUMO_PREFIX="$HOME/sumo-1.22.0-install"
export SUMO_HOME="$SUMO_PREFIX/share/sumo"
export PATH="$SUMO_PREFIX/bin:$PATH"
export LD_LIBRARY_PATH="$HOME/swarm-evo-se:$VEINS/src:$OMNETPP/lib:${LD_LIBRARY_PATH:-}"
```

## Run the SUMO/Veins Bridge

```bash
cd ~/swarm-evo-se

pkill -f opp_run || true
pkill -f sumo || true
pkill -f veins_launchd || true

export SUMO_PREFIX="$HOME/sumo-1.22.0-install"
export SUMO_HOME="$SUMO_PREFIX/share/sumo"
export PATH="$SUMO_PREFIX/bin:$PATH"

~/veins/bin/veins_launchd -vv -c "$(command -v sumo-gui)" -L /tmp/sumo-launchd.log
```

Expected output:

```text
Listening on port 9999
```

## Run the UrbanEndToEndDemo Simulation

```bash
cd ~/swarm-evo-se

export OMNETPP="$HOME/omnetpp-6.1"
export VEINS="$HOME/veins"
export LD_LIBRARY_PATH="$HOME/swarm-evo-se:$VEINS/src:$OMNETPP/lib:${LD_LIBRARY_PATH:-}"

rm -f /tmp/urban_full_demo_trace.txt
rm -f /tmp/phase1_ta_demo_trace.txt

cd simulations/swarm_evo_se

"$OMNETPP/bin/opp_run" -u Qtenv -r 0 -c UrbanEndToEndDemo omnetpp.ini \
    -n ".:../../src:$VEINS/src" \
    -l "$VEINS/src/veins" \
    -l "../../libSwarmEvoSE.so" \
    2>&1 | tee results/urban_end_to_end_demo_qtenv.log
```

## Monitor the TA Registration Trace

```bash
tail -F /tmp/phase1_ta_demo_trace.txt
```

## Monitor the Live Protocol Trace

```bash
tail -F /tmp/urban_full_demo_trace.txt | grep -E "PHASE_2|CANDIDATE|proofValid|PARTIAL|collected=|threshold signature|PSEUDONYM|SAFETY_MSG ACCEPTED|MALICIOUS|HARD_DROP invalid_zk|failures=|REVOKE|votes=|SIGNED_ACF_UPDATE|HARD_DROP SAFETY_MSG"
```

## Generate the Timing Report

```bash
cd ~/swarm-evo-se
mkdir -p results
python3 scripts/demo_timing_report.py | tee results/urban_end_to_end_timing_report.txt
```

## Expected Demo Evidence

- TA registration successful
- HSM proof-of-possession verified
- Candidate pseudonym broadcast
- ZK proof valid for legitimate node
- Partial signatures collected
- Threshold signature aggregated
- New pseudonym activated
- Safety message accepted
- Malicious invalid ZK proof rejected
- Revocation proposal sent
- Revocation votes collected
- Signed ACF update propagated
- Post-revocation malicious safety message hard-dropped

## Notes

This project is a simulation prototype for academic evaluation. HSM, ZK, BLS, and ACF behaviour are modelled to demonstrate the protocol workflow in OMNeT++, Veins, and SUMO.
