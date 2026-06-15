import org.car2x.veins.nodes.Scenario;

// Visual placeholder only.
// The real Trusted Authority logic is implemented in src/ta/TrustedAuthority.cc.
// This module exists so the TA is visible in OMNeT++ during the demo.
module TrustedAuthorityVisual
{
    parameters:
        @display("p=260,120;i=device/server;t=Trusted Authority (TA)");
}

network SwarmNetwork extends Scenario
{
    parameters:
        @display("bgb=1400,1400");

    submodules:
        trustedAuthority: TrustedAuthorityVisual {
            @display("p=260,120;i=device/server;t=Trusted Authority (TA)");
        }
}
