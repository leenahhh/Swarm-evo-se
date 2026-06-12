import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;

simple SwarmVehicle extends DemoBaseApplLayer
{
    parameters:
        @class(SwarmVehicle);
        @display("i=block/app");

        // Swarm Evo-SE protocol timing
        double epochDuration @unit(s) = default(600s);
        double preActivationLead @unit(s) = default(60s);

        // Trust/cache/revocation parameters
        int trustCacheTTL = default(30);
        int acfMaxStaleness = default(3);
        int proofPoolPrecompute = default(100);

        // Dashboard
        int dashboardPort = default(8765);

        // Attack simulation parameters
        double maliciousRatio = default(0.0);
        string maliciousMode = default("NONE");

        // Optional scenario metadata
        int numVehicles = default(0);
        string scenarioType = default("HIGHWAY");
}
