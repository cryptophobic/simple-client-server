#pragma once
#include "InvoiceMasterClient/View.hpp"
#include <memory>

namespace InvoiceMasterClient {

    class Documents: public View {
    public:
        explicit Documents(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient