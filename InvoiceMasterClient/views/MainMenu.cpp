#include "MainMenu.hpp"
#include "../Application.hpp"

namespace InvoiceMasterClient {
    std::unique_ptr<CommandStruct> MainMenu::run()
    {
        char choice;
        if (!Application::isAuthorized()) {
            std::cout << "1. Authorize" << std::endl;
        }
        std::cout << "2. Quit" << std::endl;
        if (Application::isAuthorized()) {
            std::cout << "3. Admin access" << std::endl;
        }
        std::cout << ":> ";
        std::cin >> choice;

        std::unique_ptr<CommandStruct> command = std::make_unique<CommandStruct>();

        switch(choice) {
            case '1':
                command->internalCommand = std::make_unique<settings::ServiceSignature>(settings::services.login);
                break;
            case '2':
                command->internalCommand = std::make_unique<settings::ServiceSignature>(settings::services.quit);
                break;
            case '3':
                command->internalCommand = std::make_unique<settings::ServiceSignature>(settings::services.admin);
                break;
            default:
                command->internalCommand = std::make_unique<settings::ServiceSignature>(settings::services.mainMenu);;
        }
        return std::move(command);
    }
} // InvoiceMasterClient
