#!/bin/bash
# run_simulation.sh — Swarm Evo-SE simulation runner WITHOUT dashboard

set -e

SCENARIO=${1:-ContactLegitDemo}

PROJECT="$HOME/swarm-evo-se"
OMNETPP="$HOME/omnetpp-6.1"
VEINS="$HOME/veins"

echo "=== Swarm Evo-SE — $SCENARIO Scenario ==="

# Load OMNeT++ environment
if [ -f "$OMNETPP/setenv" ]; then
    source "$OMNETPP/setenv"
else
    echo "ERROR: OMNeT++ setenv not found at $OMNETPP/setenv"
    exit 1
fi

# SUMO environment
export SUMO_PREFIX="$HOME/sumo-1.22.0-install"
export SUMO_HOME="$SUMO_PREFIX/share/sumo"
export PATH="$SUMO_PREFIX/bin:$PATH"

# Runtime library paths
export LD_LIBRARY_PATH="$PROJECT:$VEINS/src:$OMNETPP/lib:${LD_LIBRARY_PATH:-}"

# Make sure results directory exists
mkdir -p "$PROJECT/simulations/swarm_evo_se/results"
mkdir -p "$PROJECT/results"

# Check that veins_launchd is already running
if ! ss -ltn | grep -q ":9999 "; then
    echo "ERROR: veins_launchd is not running on port 9999."
    echo "Start it first in another terminal:"
    echo ""
    echo "  cd ~/swarm-evo-se"
    echo "  export SUMO_PREFIX=\"\$HOME/sumo-1.22.0-install\""
    echo "  export SUMO_HOME=\"\$SUMO_PREFIX/share/sumo\""
    echo "  export PATH=\"\$SUMO_PREFIX/bin:\$PATH\""
    echo "  ~/veins/bin/veins_launchd -vv -c \"\$(command -v sumo)\" -L /tmp/sumo-launchd.log"
    echo ""
    exit 1
fi

# Build executable and shared library
cd "$PROJECT"
make build

echo ">>> Building shared OMNeT++ module library..."
g++ -shared -pthread -o libSwarmEvoSE.so \
    src/protocol/Messages_m.o \
    src/protocol/RevocationProtocol.o \
    src/protocol/SwarmConsensus.o \
    src/crypto/ACF.o \
    src/crypto/BLSSignature.o \
    src/crypto/HSM.o \
    src/crypto/ZKProof.o \
    src/vehicle/ProofPool.o \
    src/vehicle/PseudonymEngine.o \
    src/vehicle/SwarmVehicle.o \
    src/vehicle/TrustCache.o \
    src/ta/TrustedAuthority.o \
    src/gui/DashboardServer.o \
    -L"$OMNETPP/lib" \
    -L"$VEINS/src" \
    -lssl -lcrypto -lveins -loppenvir -loppsim -loppcommon -lboost_system -pthread

echo ">>> Build complete."
ls -lh "$PROJECT/libSwarmEvoSE.so"

# Run simulation from the simulation directory
echo ">>> Starting simulation: $SCENARIO..."
cd "$PROJECT/simulations/swarm_evo_se"

"$OMNETPP/bin/opp_run" -r 0 -c "$SCENARIO" omnetpp.ini \
    -n ".:../../src:$VEINS/src" \
    -l "$VEINS/src/veins" \
    -l "../../libSwarmEvoSE.so"

echo "=== Simulation complete ==="
