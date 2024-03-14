#pragma once
#include "InvoiceMasterClient/View.hpp"
#include <memory>

namespace InvoiceMasterClient {

    class InvoiceNew: public View {
    public:
        explicit InvoiceNew(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient