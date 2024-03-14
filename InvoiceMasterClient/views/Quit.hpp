#pragma once
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class Quit : public View {
    public:
        explicit Quit(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
