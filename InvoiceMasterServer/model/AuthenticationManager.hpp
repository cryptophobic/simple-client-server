#pragma once
#include <string>

namespace InvoiceMasterServer {

    class AuthenticationManager {
    private:

        //std::hash for admin|qwerty
        size_t authorizationHash = 10792133666949253313U;

        bool _authorized;
    public:
        bool isAuthorized();
        bool authorize (const std::string& login, const std::string& password);
    };

} // InvoiceMasterServer
