#pragma once
#include "models/AuthenticationManager.hpp"
#include "models/InvoiceManager.hpp"
#include "models/LicenceManager.hpp"
#include "models/DocumentsManager.hpp"
#include "models/UserManager.hpp"

namespace InvoiceMasterServer {

    class BaseApplication {
    public:
        void setQuit();
        void setDisconnected();
        bool isDisconnected();

        //Preloaded services
        UserManager userService;
        AuthenticationManager loginService;
        InvoiceManager invoiceService;
        DocumentsManager documentsService;
        LicenceManager licenceService;

    protected:

        bool quit = false;
        bool disconnected = false;
    };

} // InvoiceMasterServer
