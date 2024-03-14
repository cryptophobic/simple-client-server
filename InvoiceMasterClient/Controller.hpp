#pragma once

#include <memory>
#include "View.hpp"
#include "BaseApplication.hpp"

namespace InvoiceMasterClient {

    class Controller {
    public:
        explicit Controller(std::shared_ptr<BaseApplication> newContext) : context(newContext) {};
        std::unique_ptr<View> run(char code);
    protected:
        std::shared_ptr<BaseApplication> context;
    };
} // InvoiceMasterClient
