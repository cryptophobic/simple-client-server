#include "Authorisation.hpp"
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterServer {
    bool Authorisation::isAuthorised()
    {
        return _authorised;
    }

    bool Authorisation::authorise(const std::string& login, const std::string& password) {
        size_t concatenation = std::hash<std::string>{}(login + "|" + password);
        _authorised = concatenation == authorisationHash;
        return _authorised;
    }
} // InvoiceMasterServer
