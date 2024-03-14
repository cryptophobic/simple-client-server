#pragma once

#include "protocol/ApiAccess.hpp"
#include "BaseApplication.hpp"
#include <memory>
#include <vector>
#include <string>

namespace InvoiceMasterClient {

    struct CommandStruct {
    public:
        char internalCommand = protocol::requestMainMenu;;
        std::string request;
    };

    class View {
    public:
        explicit View(std::shared_ptr<BaseApplication> newContext) : context(newContext) {};
        virtual ~View() = default;
        virtual std::unique_ptr<CommandStruct> run() = 0;
    protected:
        std::shared_ptr<BaseApplication> context;
    };

} // InvoiceMasterClient
