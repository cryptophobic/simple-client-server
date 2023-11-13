#include <iostream>
#include <memory>
#include "AdminAccess.hpp"
#include "../../settings/ServiceList.hpp"

namespace InvoiceMasterClient {
    std::unique_ptr<CommandStruct> AdminAccess::run()
    {
        char choice;
        std::cout << "1. Server shut down" << std::endl;
        std::cout << "2. Main menu" << std::endl;
        std::cout << ":> ";
        std::cin >> choice;

        switch(choice) {
            case '1': {
                std::unique_ptr<Request> request = std::make_unique<Request>(
                        settings::services.admin,
                        std::vector<std::string>{"quit"});
                std::unique_ptr<CommandStruct> command = std::make_unique<CommandStruct>();
                command->internalCommand = std::make_unique<settings::ServiceSignature>(settings::services.quit);
                command->request = std::move(request);

                return std::move(command);
            }
            default:
                return std::make_unique<CommandStruct>();
        }
    }
} // InvoiceMasterClient
