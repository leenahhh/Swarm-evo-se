#include "TrustedAuthority.h"

#include "../crypto/HSM.h"

#include <functional>
#include <openssl/rand.h>

TrustedAuthority& TrustedAuthority::instance() {
    static TrustedAuthority authority;
    return authority;
}

bool TrustedAuthority::registerVehicle(const std::string& vehicleId,
                                       const std::string& h0,
                                       HSM* hsm) {
    if (vehicleId.empty() || h0.empty() || hsm == nullptr) {
        return false;
    }

    KeyBytes nonce(32);
    if (RAND_bytes(nonce.data(), static_cast<int>(nonce.size())) != 1) {
        return false;
    }

    const KeyBytes signature = hsm->signNonce(nonce);
    if (signature.empty()) {
        return false;
    }

    vehicleH0_[vehicleId] = h0;
    const std::size_t cluster = std::hash<std::string>{}(vehicleId) % 16;
    vehicleClusters_[vehicleId] = "cluster-" + std::to_string(cluster);
    return true;
}

std::string TrustedAuthority::getClusterId(const std::string& vehicleId) const {
    const auto it = vehicleClusters_.find(vehicleId);
    return it == vehicleClusters_.end() ? std::string{} : it->second;
}
