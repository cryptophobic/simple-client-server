#include "LicenceVerify.hpp"
#include "protocol/Request.hpp"
#include "licence/Files.hpp"
#include <string>

namespace InvoiceMasterClient {
    std::unique_ptr<CommandStruct> LicenceVerify::run()
    {
        auto command = std::make_unique<CommandStruct>();
        command->internalCommand = protocol::requestMainMenu;
        std::string clientKey;
        licence::Files::readClientKey(clientKey);

        if (!clientKey.empty()) {
            command->request = protocol::Request::build(
                    {
                            protocol::requestVerifyLicence,
                            std::vector<std::string>{clientKey}
                    });
        }
        return command;
    }
} // InvoiceMasterClient
