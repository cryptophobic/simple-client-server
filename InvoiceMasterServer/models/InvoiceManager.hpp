#pragma once
#include "InvoiceMasterServer/entities/Invoice.hpp"

#include <memory>

namespace InvoiceMasterServer {

    class InvoiceManager {
    protected:
        std::string userId;
    public:
        std::unique_ptr<Invoice> currentInvoice;
        bool isInvoiceOpened();
        std::string execute(const std::vector<std::string>& arguments);
        void init(const std::string& newUserId = "");
        void finalise();
    };

} // InvoiceMasterServer
