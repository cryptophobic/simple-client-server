#pragma once
#include <vector>
#include <memory>
#include "BaseApplication.hpp"
#include "protocol/Response.hpp"
#include "protocol/Request.hpp"

namespace InvoiceMasterServer {

    class Controller {
    public:
        explicit Controller(std::shared_ptr<BaseApplication> newContext) : context(newContext) {};
        std::string execute(std::string& requestMessage);
    protected:
        std::shared_ptr<BaseApplication> context;
        virtual std::unique_ptr<protocol::RequestStructure> parseRequest(const std::string& requestMessage);
        virtual std::string processRequest(std::unique_ptr<protocol::RequestStructure> request);
    };

} // InvoiceMasterServer
