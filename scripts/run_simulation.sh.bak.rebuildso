#!/bin/bash
export VEINS="$HOME/veins"
export VEINS_HOME="$VEINS"
export VEINS_ROOT="$VEINS"
export LD_LIBRARY_PATH="$VEINS/src:$HOME/omnetpp-6.1/lib:$HOME/swarm-evo-se:$LD_LIBRARY_PATH"
# run_simulation.sh — Launches the full simulation stack:
#   1. Serves the dashboard over HTTP
#   2. Starts SUMO via TraCI
#   3. Runs the OMNeT++ simulation
#   4. Opens the dashboard in your browser

set -e

SCENARIO=${1:-Highway}  # Default to Highway. Pass "Urban", "Sybil" etc.
PROJECT="$HOME/swarm-evo-se"
OMNETPP="$HOME/omnetpp-6.1"
VEINS="$HOME/veins"

echo "=== Swarm Evo-SE — $SCENARIO Scenario ==="

# Load environments
source "$OMNETPP/setenv"
# export SUMO_HOME="$HOME/sumo-1.22.0-install"
# export PATH="$SUMO_HOME/bin:$PATH"
SUMO_PREFIX="$HOME/sumo-1.22.0-install"
export SUMO_HOME="$SUMO_PREFIX/share/sumo"
export PATH="$SUMO_PREFIX/bin:$PATH"

# Generate SUMO files if not present
if [ ! -f "$PROJECT/scripts/urban.net.xml" ]; then
    echo ">>> Generating SUMO scenarios..."
    python3 "$PROJECT/scripts/generate_sumo_scenario.py"
fi

# Build if needed
cd "$PROJECT"
make build

# Start dashboard HTTP server in background
echo ">>> Starting dashboard server on port 8766..."
python3 -m http.server 8766 --directory "$PROJECT" &
HTTP_PID=$!
trap 'kill $HTTP_PID 2>/dev/null || true' EXIT

# Give server time to start
sleep 1

# Open browser
echo ">>> Opening dashboard..."
#xdg-open "http://localhost:8766/dashboard/index.html" 2>/dev/null &
if command -v explorer.exe >/dev/null 2>&1; then
    explorer.exe "http://localhost:8766/dashboard/index.html" >/dev/null 2>&1 &
else
    xdg-open "http://localhost:8766/dashboard/index.html" 2>/dev/null &
fi

# Run simulation
echo ">>> Starting simulation: $SCENARIO..."
cd "$PROJECT/simulations/swarm_evo_se"
"$OMNETPP/bin/opp_run" -r 0 -c "$SCENARIO" omnetpp.ini \
    -n ".:../../src:$VEINS/src" \
    -l "$VEINS/src/veins" \
    -l "../../SwarmEvoSE"

# Cleanup
kill $HTTP_PID 2>/dev/null || true
echo "=== Simulation complete ==="
