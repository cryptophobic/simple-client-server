#pragma once

#include <vector>
#include <string>
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class AdminAccess: public View {
    public:
        explicit AdminAccess(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
