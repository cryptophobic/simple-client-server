#pragma once
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class Logout : public View {
    public:
        explicit Logout(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
