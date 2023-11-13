#pragma once

#include <memory>
#include "ServiceConnector/Request.hpp"
#include "../settings/ServiceList.hpp"
#include "View.hpp"

namespace InvoiceMasterClient {

    class Controller {
    public:
        static std::unique_ptr<View> run(char code);

    };

} // InvoiceMasterClient
