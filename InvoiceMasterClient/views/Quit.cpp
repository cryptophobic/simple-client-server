//
// Created by Dmytro Uglach on 13.11.2023.
//

#include "Quit.hpp"

namespace InvoiceMasterClient {

    std::unique_ptr<CommandStruct> Quit::run()
    {
        std::unique_ptr<CommandStruct> command = std::make_unique<CommandStruct>();
        command->request = std::make_unique<Request>(settings::services.quit, std::vector<std::string>{});

        return std::move(command);
    }

} // InvoiceMasterClient