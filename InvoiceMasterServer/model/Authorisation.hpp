#pragma once
#include <string>

namespace InvoiceMasterServer {

    class Authorisation {
    private:

        //std::hash for admin|qwerty
        size_t authorisationHash = 10792133666949253313U;

        bool _authorised;
    public:
        bool isAuthorised();
        bool authorise (const std::string& login, const std::string& password);
    };

} // InvoiceMasterServer
