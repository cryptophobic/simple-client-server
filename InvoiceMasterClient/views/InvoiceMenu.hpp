#pragma once

#include <memory>
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class InvoiceMenu: public View {
    protected:
        const std::string invoiceFilePathXML = std::string(CLIENT_PROJECT_DIR) + "/localFiles/invoice.xml";
    public:
        explicit InvoiceMenu(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
