#include "DashboardServer.h"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include <sstream>
#include <set>
#include <mutex>
#include <thread>
#include <atomic>

using websocketpp::connection_hdl;

class DashboardServerRuntime {
public:
    using server_t = websocketpp::server<websocketpp::config::asio>;

    server_t server;
    std::set<connection_hdl, std::owner_less<connection_hdl>> clients;
    std::mutex clientsMutex;
    std::thread serverThread;
    std::atomic<bool> running{false};
};

static DashboardServerRuntime runtime;

DashboardServer& DashboardServer::instance() {
    static DashboardServer instance;
    return instance;
}

void DashboardServer::start(uint16_t port) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (running_) {
        return;
    }

    running_ = true;
    port_ = port;
    runtime.running = true;

    runtime.serverThread = std::thread([port]() {
        try {
            runtime.server.clear_access_channels(websocketpp::log::alevel::all);
            runtime.server.clear_error_channels(websocketpp::log::elevel::all);

            runtime.server.init_asio();
            runtime.server.set_reuse_addr(true);

            runtime.server.set_open_handler([](connection_hdl hdl) {
                std::lock_guard<std::mutex> lock(runtime.clientsMutex);
                runtime.clients.insert(hdl);
                std::cout << "[DashboardServer] Browser connected" << std::endl;
            });

            runtime.server.set_close_handler([](connection_hdl hdl) {
                std::lock_guard<std::mutex> lock(runtime.clientsMutex);
                runtime.clients.erase(hdl);
                std::cout << "[DashboardServer] Browser disconnected" << std::endl;
            });

            runtime.server.listen(port);
            runtime.server.start_accept();

            std::cout << "[DashboardServer] WebSocket listening on ws://0.0.0.0:"
                      << port << std::endl;

            runtime.server.run();
        } catch (const std::exception& e) {
            std::cerr << "[DashboardServer] ERROR: " << e.what() << std::endl;
        }
    });

    runtime.serverThread.detach();
}

void DashboardServer::stop() {
    if (!running_) {
        return;
    }

    running_ = false;
    runtime.running = false;

    try {
        runtime.server.stop_listening();
        runtime.server.stop();
    } catch (...) {
        // Ignore shutdown errors.
    }
}

void DashboardServer::emit(const std::string& eventType, const std::string& payload) {
    std::string json = "{\"type\":\"" + eventType + "\",";

    if (!payload.empty() && payload.front() == '{') {
        json += payload.substr(1);
    } else {
        json += "\"payload\":\"" + payload + "\"}";
    }

    emitRaw(json);
}

void DashboardServer::emitRaw(const std::string& jsonStr) {
    std::cout << "[DashboardServer] " << jsonStr << std::endl;

    std::lock_guard<std::mutex> lock(runtime.clientsMutex);

    for (auto it = runtime.clients.begin(); it != runtime.clients.end(); ) {
        try {
            runtime.server.send(*it, jsonStr, websocketpp::frame::opcode::text);
            ++it;
        } catch (...) {
            it = runtime.clients.erase(it);
        }
    }
}

static std::string esc(const std::string& s) {
    std::string out;
    for (char c : s) {
        if (c == '"') out += "\\\"";
        else if (c == '\\') out += "\\\\";
        else out += c;
    }
    return out;
}

std::string buildVehicleUpdateJson(
    const std::string& vehicleId,
    const std::string& pseudonym,
    const std::string& h0,
    double posX,
    double posY,
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
      << "\"isMalicious\":" << (isMalicious ? "true" : "false");

    if (!dropReason.empty()) {
        o << ",\"dropReason\":\"" << esc(dropReason) << "\"";
    }

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
      << "\"entries\":" << entriesJson
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
