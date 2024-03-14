#include "MainMenu.hpp"
#include "protocol/ApiAccess.hpp"
#include "email/Inbox.hpp"
#include "licence/Files.hpp"

namespace InvoiceMasterClient {
    std::unique_ptr<CommandStruct> MainMenu::run()
    {
        char choice;
        if (!context->isAuthorized()) {
            context->userOutputSystem->outputLine("1. Sign in");
            context->userOutputSystem->outputLine("2. Sign up");
        } else {
            context->userOutputSystem->outputLine("1. Sign out");
            context->userOutputSystem->outputLine("3. Invoices");
            context->userOutputSystem->outputLine("4. Documents");
            context->userOutputSystem->outputLine("5. Admin access");
        }

        if (!context->isLicenceConfirmed()) {
            context->userOutputSystem->outputLine("6. Licence menu");
        }
        context->userOutputSystem->outputLine("7. Check email");

        context->userOutputSystem->outputLine("0. Quit");

        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(choice);

        auto command = std::make_unique<CommandStruct>();

        switch (choice) {
            case '0':
                command->internalCommand = protocol::requestDisconnect;
                break;
            case '1':
                command->internalCommand = context->isAuthorized() ? protocol::requestLogout : protocol::requestLogin;
                break;
            case '2':
                command->internalCommand = protocol::requestSignUp;
                break;
            case '3':
                command->internalCommand = protocol::requestInvoice;
                break;
            case '4':
                command->internalCommand = protocol::requestDocuments;
                break;
            case '5':
                command->internalCommand = protocol::requestAdminAccess;
                break;
            case '6':
                command->internalCommand = protocol::requestLicence;
                break;
            case '7': {

                std::string userName{}, body{}, inputName{};
                licence::Files::readClientKey(userName);

                if (!userName.empty()) {
                    context->userOutputSystem->outputLine("Enter your username or press Enter to use stored one: " + userName);
                } else {
                    context->userOutputSystem->outputLine("Enter your username");
                }

                command->internalCommand = protocol::requestMainMenu;
                context->userOutputSystem->output(":> ");
                context->userInputSystem->read(inputName);
                userName = inputName.empty() ? userName : inputName;

                email::Inbox::receive(userName, body);
                if (body.empty()) {
                    context->userOutputSystem->outputLine("Empty mailbox");
                } else {
                    context->userOutputSystem->outputLine(body);
                }
            }
            break;
            default:
                context->userOutputSystem->outputLine("Incorrect input");
                command->internalCommand = protocol::requestMainMenu;
        }
        return command;
    }
} // InvoiceMasterClient
