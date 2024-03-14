#pragma once
#include "InvoiceMasterClient/View.hpp"
#include <memory>

namespace InvoiceMasterClient {

    class InvoiceDelete: public View {
    public:
        explicit InvoiceDelete(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient