#pragma once
#include <vector>
#include <string>
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class MainMenu : public View {
    public:
        explicit MainMenu(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
