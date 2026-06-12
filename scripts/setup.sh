#!/bin/bash
# setup.sh
# One-shot script that installs dependencies and prepares the Swarm Evo-SE environment.
# Run this only when setting up the project, not every time you run a simulation.

set -e

echo "=== Swarm Evo-SE Setup ==="

# --- System packages ---
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    git \
    python3 python3-pip \
    libssl-dev \
    libboost-all-dev \
    nlohmann-json3-dev \
    websocketpp-dev \
    python3-websocket \
    pkg-config

# --- Python packages for dashboard and SUMO scenario generation ---
pip3 install websockets asyncio matplotlib numpy

# --- OMNeT++ environment ---
OMNETPP_DIR="$HOME/omnetpp-6.1"
if [ -f "$OMNETPP_DIR/setenv" ]; then
    # shellcheck disable=SC1090
    source "$OMNETPP_DIR/setenv"
    export OMNETPP_ROOT="$OMNETPP_DIR"
    export OMNET_HOME="$OMNETPP_DIR"
    echo "OMNeT++ environment loaded from $OMNETPP_DIR"
else
    echo "WARNING: OMNeT++ setenv not found at $OMNETPP_DIR. Set it manually."
fi

# --- Veins environment ---
VEINS_DIR="$HOME/veins"
if [ -d "$VEINS_DIR" ]; then
    export VEINS_ROOT="$VEINS_DIR"
    export VEINS_HOME="$VEINS_DIR"
    echo "Veins loaded from $VEINS_DIR"
else
    echo "WARNING: Veins not found at $VEINS_DIR."
fi

# --- SUMO environment ---
# Your installed compatible SUMO version is:
#   ~/sumo-1.22.0-install
#
# SUMO binaries are in:
#   ~/sumo-1.22.0-install/bin
#
# SUMO tools such as randomTrips.py are in:
#   ~/sumo-1.22.0-install/share/sumo/tools

SUMO_PREFIX="$HOME/sumo-1.22.0-install"

if [ -x "$SUMO_PREFIX/bin/sumo" ]; then
    export PATH="$SUMO_PREFIX/bin:$PATH"
    export SUMO_HOME="$SUMO_PREFIX/share/sumo"
    echo "SUMO loaded from $SUMO_PREFIX"
    echo "SUMO binary: $(command -v sumo)"
    sumo --version | head -1
else
    echo "WARNING: SUMO 1.22.0 not found at $SUMO_PREFIX/bin/sumo."
    echo "Falling back to system SUMO if available."
    if command -v sumo >/dev/null 2>&1; then
        echo "System SUMO binary: $(command -v sumo)"
        sumo --version | head -1
    fi
fi

echo ""
echo "=== Setup complete ==="
echo ""
echo "For normal simulation runs, use:"
echo "  cd ~/swarm-evo-se"
echo "  source ~/omnetpp-6.1/setenv"
echo "  export SUMO_PREFIX=\"\$HOME/sumo-1.22.0-install\""
echo "  export SUMO_HOME=\"\$SUMO_PREFIX/share/sumo\""
echo "  export PATH=\"\$SUMO_PREFIX/bin:\$PATH\""
echo "  python3 scripts/generate_sumo_scenario.py"
echo "  make"
echo "  bash scripts/run_simulation.sh Highway"
echo ""
echo "To open the dashboard manually from Windows:"
echo "  explorer.exe \"http://localhost:8766/dashboard/index.html\""