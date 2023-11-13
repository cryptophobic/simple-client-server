#pragma once
#include <vector>
#include <string>
#include "../View.hpp"

namespace InvoiceMasterClient {

    class MainMenu : public View{
    public:
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
