#include "Quit.hpp"
#include "protocol/Request.hpp"
#include "protocol/ApiAccess.hpp"

namespace InvoiceMasterClient {

    std::unique_ptr<CommandStruct> Quit::run()
    {
        auto command = std::make_unique<CommandStruct>();
        command->request = protocol::Request::build({protocol::requestDisconnect, {}});

        return command;
    }
} // InvoiceMasterClient
