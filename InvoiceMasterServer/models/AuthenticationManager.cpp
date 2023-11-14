#include "AuthenticationManager.hpp"
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterServer {
    bool AuthenticationManager::isAuthorized() const
    {
        return _authorized;
    }

    bool AuthenticationManager::authorize(const std::string& login, const std::string& password) {
        size_t concatenation = std::hash<std::string>{}(login + "|" + password);
        _authorized = concatenation == authorizationHash;
        return _authorized;
    }
} // InvoiceMasterServer
