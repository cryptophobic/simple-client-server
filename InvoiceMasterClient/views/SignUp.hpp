#pragma once

#include <string>
#include <vector>
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class SignUp : public View{
    public:
        explicit SignUp(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    };

} // InvoiceMasterClient
