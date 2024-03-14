#pragma once
#include "InvoiceMasterClient/View.hpp"
#include <memory>

namespace InvoiceMasterClient {

    class InvoiceGet: public View {
    public:
        explicit InvoiceGet(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient