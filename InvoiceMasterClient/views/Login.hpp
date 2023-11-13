#pragma once

#include <string>
#include <vector>
#include "../View.hpp"

namespace InvoiceMasterClient {

    class Login : public View{
    public:
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
