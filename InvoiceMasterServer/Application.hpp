#pragma once

#include "Service/Listener.hpp"
#include "models/AuthenticationManager.hpp"

namespace InvoiceMasterServer {
    class Application {
    public:
        void run();
    private:
        //Preloaded services
        AuthenticationManager loginService;

        bool quit = false;
        Listener service;
        std::unique_ptr<Response> controller(std::unique_ptr<Request> request);
    };
}