#pragma once

#include "../settings/ServiceList.hpp"
#include "ServiceConnector/Request.hpp"
#include <memory>

namespace InvoiceMasterClient {

    struct CommandStruct {
    public:
        std::unique_ptr<settings::ServiceSignature> internalCommand = std::make_unique<settings::ServiceSignature>(settings::services.mainMenu);
        std::unique_ptr<Request> request = nullptr;
    };

    class View {
    public:
        virtual ~View() = default;
        virtual std::unique_ptr<CommandStruct> run() = 0;
    };

} // InvoiceMasterClient
