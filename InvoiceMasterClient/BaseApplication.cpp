#include "BaseApplication.hpp"

namespace InvoiceMasterClient {
    bool BaseApplication::isAuthorized()
    {
        return authorized;
    }
    bool BaseApplication::isLicenceConfirmed()
    {
        return licenceConfirmed;
    }
} // InvoiceMasterClient
