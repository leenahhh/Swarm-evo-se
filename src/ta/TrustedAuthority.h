#ifndef TRUSTEDAUTHORITY_H
#define TRUSTEDAUTHORITY_H

#include <string>
#include <unordered_map>

class HSM;

class TrustedAuthority {
public:
    static TrustedAuthority& instance();

    bool registerVehicle(const std::string& vehicleId,
                         const std::string& h0,
                         HSM* hsm);
    std::string getClusterId(const std::string& vehicleId) const;

private:
    TrustedAuthority() = default;
    TrustedAuthority(const TrustedAuthority&) = delete;
    TrustedAuthority& operator=(const TrustedAuthority&) = delete;

    std::unordered_map<std::string, std::string> vehicleH0_;
    std::unordered_map<std::string, std::string> vehicleClusters_;
};

#endif // TRUSTEDAUTHORITY_H
