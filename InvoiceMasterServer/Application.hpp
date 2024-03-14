#pragma once

#include "Service/Listener.hpp"
#include "Controller.hpp"
#include <vector>
#include <string>

namespace InvoiceMasterServer {
    class Application : public BaseApplication, public std::enable_shared_from_this<Application> {
    public:
        virtual void run();

    protected:
        std::unique_ptr<Controller> controller;
        void waitForConnection();
        bool readFromClient(std::string& );
        Listener service;
    };
}