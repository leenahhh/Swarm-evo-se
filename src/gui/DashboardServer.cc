#include "DashboardServer.h"

#include <sstream>
#include <string>

// Dashboard disabled stub.
// This file keeps the simulation linkable without starting WebSocket,
// browser server, or external dashboard dependencies.

static std::string esc(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '"') out += "\\\"";
        else if (c == '\\') out += "\\\\";
        else if (c == '\n') out += "\\n";
        else out += c;
    }
    return out;
}

DashboardServer& DashboardServer::instance() {
    static DashboardServer server;
    return server;
}

void DashboardServer::start(uint16_t port) {
    port_ = port;
    running_ = false;
}

void DashboardServer::stop() {
    running_ = false;
}

void DashboardServer::emit(const std::string& eventType, const std::string& payload) {
    // Dashboard disabled: intentionally do nothing.
    (void)eventType;
    (void)payload;
}

void DashboardServer::emitRaw(const std::string& jsonStr) {
    // Dashboard disabled: intentionally do nothing.
    (void)jsonStr;
}

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
) {
    std::ostringstream o;
    o << "{"
      << "\"vehicleId\":\"" << esc(vehicleId) << "\","
      << "\"pseudonym\":\"" << esc(pseudonym) << "\","
      << "\"h0\":\"" << esc(h0) << "\","
      << "\"posX\":" << posX << ","
      << "\"posY\":" << posY << ","
      << "\"epoch\":" << epoch << ","
      << "\"threshold\":" << threshold << ","
      << "\"neighbours\":" << neighbours << ","
      << "\"isMalicious\":" << (isMalicious ? "true" : "false") << ","
      << "\"maliciousMode\":\"" << esc(maliciousMode) << "\","
      << "\"status\":\"" << esc(status) << "\""
      << "}";
    return o.str();
}

std::string buildPacketEventJson(
    const std::string& msgType,
    const std::string& senderId,
    const std::string& receiverId,
    const std::string& outcome,
    double latencyMs,
    bool isMalicious,
    const std::string& dropReason,
    const std::string& extraFields
) {
    std::ostringstream o;
    o << "{"
      << "\"msgType\":\"" << esc(msgType) << "\","
      << "\"senderId\":\"" << esc(senderId) << "\","
      << "\"receiverId\":\"" << esc(receiverId) << "\","
      << "\"outcome\":\"" << esc(outcome) << "\","
      << "\"latencyMs\":" << latencyMs << ","
      << "\"isMalicious\":" << (isMalicious ? "true" : "false") << ","
      << "\"dropReason\":\"" << esc(dropReason) << "\"";

    if (!extraFields.empty()) {
        o << "," << extraFields;
    }

    o << "}";
    return o.str();
}

std::string buildACFUpdateJson(
    uint32_t epoch,
    bool isFresh,
    const std::string& entriesJson
) {
    std::ostringstream o;
    o << "{"
      << "\"epoch\":" << epoch << ","
      << "\"isFresh\":" << (isFresh ? "true" : "false") << ","
      << "\"entries\":" << (entriesJson.empty() ? "[]" : entriesJson)
      << "}";
    return o.str();
}

std::string buildRevocationJson(
    const std::string& suspectId,
    const std::string& reason,
    uint32_t epoch
) {
    std::ostringstream o;
    o << "{"
      << "\"suspectId\":\"" << esc(suspectId) << "\","
      << "\"reason\":\"" << esc(reason) << "\","
      << "\"epoch\":" << epoch
      << "}";
    return o.str();
}

std::string buildZKProofJson(
    const std::string& vehicleId,
    bool verified,
    uint32_t epoch,
    uint32_t index
) {
    std::ostringstream o;
    o << "{"
      << "\"vehicleId\":\"" << esc(vehicleId) << "\","
      << "\"verified\":" << (verified ? "true" : "false") << ","
      << "\"epoch\":" << epoch << ","
      << "\"index\":" << index
      << "}";
    return o.str();
}

std::string buildBLSAggJson(
    uint32_t signerCount,
    const std::string& pseudonym,
    uint32_t epoch
) {
    std::ostringstream o;
    o << "{"
      << "\"signerCount\":" << signerCount << ","
      << "\"pseudonym\":\"" << esc(pseudonym) << "\","
      << "\"epoch\":" << epoch
      << "}";
    return o.str();
}

std::string buildSimStateJson(
    double simTime,
    uint32_t epoch,
    double epochProgress
) {
    std::ostringstream o;
    o << "{"
      << "\"simTime\":" << simTime << ","
      << "\"epoch\":" << epoch << ","
      << "\"epochProgress\":" << epochProgress
      << "}";
    return o.str();
}
