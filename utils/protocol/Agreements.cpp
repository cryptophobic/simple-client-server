#include "protocol/Agreements.hpp"
#include <set>

namespace protocol {
    const std::set<const char> responseCodes = {responseError, responseSuccess};
    const std::set<const char> authorizedCodes = {authorized, notAuthorized};
    const std::set<const char> licenceStatuses = {licenceConfirmed, licenceNotConfirmed};
    const std::set<const char> connectionStatuses = {connected, disconnected};

    void Agreements::validateResponseCode(const std::string& responseCode) {
        if (responseCode.length() != 1) {
            throw std::invalid_argument("protocol::validateResponseCode: Invalid response code");
        }
        validateResponseCode(responseCode[0]);
    }

    void Agreements::validateResponseCode(const char responseCode) {
        if (!responseCodes.contains(responseCode)) {
            throw std::invalid_argument("protocol::validateResponseCode: Invalid response code");
        }
    }

    void Agreements::validateAuthorizedCode(const std::string& authorizedCode) {
        if (authorizedCode.length() != 1) {
            throw std::invalid_argument("protocol::validateAuthorizedCode: Invalid authorized code");
        }
        validateAuthorizedCode(authorizedCode[0]);
    }

    void Agreements::validateAuthorizedCode(const char authorizedCode) {
        if (!authorizedCodes.contains(authorizedCode)) {
            throw std::invalid_argument("protocol::validateAuthorizedCode: Invalid authorized code");
        }
    }

    void Agreements::validateLicenceStatus(const std::string& licenceStatus) {
        if (licenceStatus.length() != 1) {
            throw std::invalid_argument("protocol::validateLicenceStatus: Invalid licence status code");
        }
        validateLicenceStatus(licenceStatus[0]);
    }

    void Agreements::validateLicenceStatus(const char code) {
        if (!licenceStatuses.contains(code)) {
            throw std::invalid_argument("protocol::validateLicenceStatus: Invalid licence status code");
        }
    }

    void Agreements::validateConnectionStatus(const std::string& connectionStatus) {
        if (connectionStatus.length() != 1) {
            throw std::invalid_argument("protocol::validateConnectionStatus: Invalid connection status code");
        }
        validateConnectionStatus(connectionStatus[0]);
    }

    void Agreements::validateConnectionStatus(const char code) {
        if (!connectionStatuses.contains(code)) {
            throw std::invalid_argument("protocol::validateConnectionStatus: Invalid connection status code");
        }
    }
}
