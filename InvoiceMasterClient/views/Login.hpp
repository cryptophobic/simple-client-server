#pragma once

#include <string>
#include <vector>
#include "InvoiceMasterClient/View.hpp"

namespace InvoiceMasterClient {

    class Login : public View{
    public:
        explicit Login(std::shared_ptr<BaseApplication> newContext) : View(newContext) {};
        std::unique_ptr<CommandStruct> run() override;
    protected:
        virtual std::string buildRequest(const char requestCommand, const std::vector<std::string>& arguments);
    };

} // InvoiceMasterClient
