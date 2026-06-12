#!/usr/bin/env python3
"""
generate_sumo_scenario.py
Generates SUMO network and route files for highway and urban scenarios.
Run this before the simulation to create the road network files.
Usage: python3 scripts/generate_sumo_scenario.py
"""

import os
import subprocess

OUTPUT_DIR = os.path.expanduser("~/swarm-evo-se/scripts")

# -------------------------------------------------------
# Highway scenario: straight 5km road, 8 vehicles
# -------------------------------------------------------
HIGHWAY_NOD = """<?xml version="1.0"?>
<!-- Highway nodes: two endpoints of a 5km straight road -->
<nodes>
    <node id="start" x="0"    y="0"/>
    <node id="end"   x="5000" y="0"/>
</nodes>
"""

HIGHWAY_EDG = """<?xml version="1.0"?>
<!-- Highway edge: 5km, 3 lanes, 120km/h speed limit -->
<edges>
    <edge id="highway" from="start" to="end"
          numLanes="3" speed="33.33" spreadType="center"/>
</edges>
"""

HIGHWAY_ROU = """<?xml version="1.0"?>
<!-- Highway routes: 8 vehicles spaced 500m apart -->
<routes>
    <vType id="car" accel="2.6" decel="4.5" sigma="0.5"
           length="5" maxSpeed="33.33" color="0,0,255"/>
    <route id="r0" edges="highway"/>
    <!-- Vehicles depart at 0, 5, 10... seconds to spread them out -->
    <vehicle id="v0" type="car" route="r0" depart="0"   departPos="0"/>
    <vehicle id="v1" type="car" route="r0" depart="5"   departPos="500"/>
    <vehicle id="v2" type="car" route="r0" depart="10"  departPos="1000"/>
    <vehicle id="v3" type="car" route="r0" depart="15"  departPos="1500"/>
    <vehicle id="v4" type="car" route="r0" depart="20"  departPos="2000"/>
    <vehicle id="v5" type="car" route="r0" depart="25"  departPos="2500"/>
    <vehicle id="v6" type="car" route="r0" depart="30"  departPos="3000"/>
    <vehicle id="v7" type="car" route="r0" depart="35"  departPos="3500"/>
</routes>
"""

# -------------------------------------------------------
# Urban scenario: 1km x 1km Manhattan grid, 120 vehicles
# Use SUMO's built-in netgenerate tool for the grid
# -------------------------------------------------------

def write_file(path, content):
    with open(path, 'w') as f:
        f.write(content)
    print(f"  Written: {path}")

def run(cmd):
    print(f"  Running: {cmd}")
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"  WARNING: {result.stderr}")

def generate_highway():
    print("\n[Highway scenario]")
    write_file(f"{OUTPUT_DIR}/highway.nod.xml", HIGHWAY_NOD)
    write_file(f"{OUTPUT_DIR}/highway.edg.xml", HIGHWAY_EDG)
    write_file(f"{OUTPUT_DIR}/highway.rou.xml", HIGHWAY_ROU)
    # Build the network file
    run(f"netconvert --node-files={OUTPUT_DIR}/highway.nod.xml "
        f"--edge-files={OUTPUT_DIR}/highway.edg.xml "
        f"-o {OUTPUT_DIR}/highway.net.xml")

def generate_urban():
    print("\n[Urban scenario]")
    # netgenerate creates a Manhattan grid automatically
    run(f"netgenerate --grid --grid.x-number=6 --grid.y-number=6 "
        f"--grid.length=200 --default.lanenumber=2 --default.speed=13.89 "
        f"-o {OUTPUT_DIR}/urban.net.xml")
    # Generate random routes for 120 vehicles over 300 seconds
    run(f"python3 $SUMO_HOME/tools/randomTrips.py "
        f"-n {OUTPUT_DIR}/urban.net.xml "
        f"-r {OUTPUT_DIR}/urban.rou.xml "
        f"-e 300 -p 2.5 --fringe-factor 1.0")

def generate_launchd_files():
    """Generate the .launchd.xml files that OMNeT++ TraCI manager uses to start SUMO"""
    print("\n[LaunchD config files]")

    for scenario in ["highway", "urban"]:
        content = f"""<?xml version="1.0"?>
<!-- TraCI launchd config for {scenario} scenario -->
<launch>
    <copy file="{OUTPUT_DIR}/{scenario}.net.xml"/>
    <copy file="{OUTPUT_DIR}/{scenario}.rou.xml"/>
    <sumo-launchd port="9999" seed="23423">
        <basedir path="{OUTPUT_DIR}"/>
        <simulate>
            <sumo-options>
                <option name="net-file"   value="{scenario}.net.xml"/>
                <option name="route-files" value="{scenario}.rou.xml"/>
                <option name="step-length" value="0.1"/>
                <option name="collision.action" value="warn"/>
            </sumo-options>
        </simulate>
    </sumo-launchd>
</launch>
"""
        write_file(f"{OUTPUT_DIR}/sumo_{scenario}.launchd.xml", content)

if __name__ == "__main__":
    generate_highway()
    generate_urban()
    generate_launchd_files()
    print("\n=== SUMO scenario files generated successfully ===")