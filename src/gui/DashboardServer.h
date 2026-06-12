#ifndef DASHBOARDSERVER_H
#define DASHBOARDSERVER_H

// DashboardServer.h — WebSocket server that pushes simulation events to the dashboard
//
// Every time something significant happens in the simulation — packet sent,
// ZK proof verified, revocation issued, ACF updated — the vehicle module calls
// emit() with a JSON payload. This server broadcasts it to all connected browsers.
//
// Uses websocketpp (header-only library) over localhost:8765.

#include <string>
#include <thread>
#include <mutex>
#include <set>
#include <functional>

class DashboardServer {
public:
    // Singleton access
    static DashboardServer& instance();

    // Start the server on the given port (runs in background thread)
    void start(uint16_t port = 8765);

    // Stop the server
    void stop();

    // Broadcast a JSON event to all connected dashboard clients
    // eventType: e.g. "PACKET_EVENT", "VEHICLE_UPDATE", "REVOCATION"
    // payload:   JSON string (the event data)
    void emit(const std::string& eventType, const std::string& payload);

    // Helper: emit a pre-built JSON string
    void emitRaw(const std::string& jsonStr);

    // Is the server running?
    bool isRunning() const { return running_; }

private:
    DashboardServer() = default;
    ~DashboardServer() { stop(); }
    DashboardServer(const DashboardServer&) = delete;

    bool running_ = false;
    uint16_t port_;
    std::thread serverThread_;
    std::mutex mutex_;

    void runServer();
};

// ---- JSON builder helpers ----
// These build the specific JSON payloads the dashboard expects

std::string buildVehicleUpdateJson(
    const std::string& vehicleId,
    const std::string& pseudonym,
    const std::string& h0,
    double posX, double posY,
    uint32_t epoch,
    uint32_t threshold,
    uint32_t neighbours,
    bool isMalicious,
    const std::string& maliciousMode,
    const std::string& status
);

std::string buildPacketEventJson(
    const std::string& msgType,
    const std::string& senderId,
    const std::string& receiverId,
    const std::string& outcome,
    double latencyMs,
    bool isMalicious,
    const std::string& dropReason,
    const std::string& extraFields  // additional JSON key:value pairs
);

std::string buildACFUpdateJson(
    uint32_t epoch,
    bool isFresh,
    const std::string& entriesJson  // JSON array of entry objects
);

std::string buildRevocationJson(
    const std::string& suspectId,
    const std::string& reason,
    uint32_t epoch
);

std::string buildZKProofJson(
    const std::string& vehicleId,
    bool verified,
    uint32_t epoch,
    uint32_t index
);

std::string buildBLSAggJson(
    uint32_t signerCount,
    const std::string& pseudonym,
    uint32_t epoch
);

std::string buildSimStateJson(
    double simTime,
    uint32_t epoch,
    double epochProgress
);

#endif // DASHBOARDSERVER_H