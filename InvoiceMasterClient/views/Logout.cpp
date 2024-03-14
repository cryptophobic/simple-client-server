#include "Logout.hpp"
#include "protocol/Request.hpp"

namespace InvoiceMasterClient {
    std::unique_ptr<CommandStruct> Logout::run()
    {
        auto command = std::make_unique<CommandStruct>();
        command->request = protocol::Request::build({protocol::requestLogout, {}});
        return command;
    }

} // InvoiceMasterClient
