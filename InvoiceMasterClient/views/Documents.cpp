#include "Documents.hpp"
#include "protocol/Request.hpp"
#include "config/settings.hpp"
#include <vector>

namespace InvoiceMasterClient {

    std::unique_ptr<CommandStruct> Documents::run() {
        std::string name, price, quantity;
        auto command = std::make_unique<CommandStruct>();
        char choice;
        context->userOutputSystem->outputLine("0. Main menu");
        context->userOutputSystem->outputLine("1. Documents list");
        context->userOutputSystem->outputLine("2. Read document");
        context->userOutputSystem->outputLine("3. Save invoice to documents");
        context->userOutputSystem->outputLine("4. Delete document");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(choice);

        std::string documentNo, password;

        switch (choice) {
            case '0':
                command->internalCommand = protocol::requestMainMenu;
                break;
            case '1':
                command->internalCommand = protocol::requestDocuments;
                command->request = protocol::Request::build({
                    protocol::requestDocuments,
                    std::vector<std::string>{
                        std::string(1, protocol::requestDocuments)}
                });
                break;
                case '2':
                    context->userOutputSystem->outputLine("Enter document number");
                    context->userOutputSystem->output(":> ");
                    context->userInputSystem->readNumerical(documentNo);
                    context->userOutputSystem->outputLine("Enter password");
                    context->userOutputSystem->output(":> ");
                    context->userInputSystem->read(password);
                    command->internalCommand = protocol::requestDocuments;
                    command->request = protocol::Request::build(
                            {
                                protocol::requestDocuments,
                                std::vector<std::string>{
                                    std::string(1, protocol::documentLoad),
                                    documentNo,
                                    password
                                }
                            });
                    break;
                case '3':
                    context->userOutputSystem->outputLine("Enter document number");
                    context->userOutputSystem->output(":> ");
                    context->userInputSystem->readNumerical(documentNo);
                    context->userOutputSystem->outputLine("Create password");
                    context->userOutputSystem->output(":> ");
                    context->userInputSystem->read(password);
                    command->internalCommand = protocol::requestDocuments;
                    command->request = protocol::Request::build(
                        {
                                protocol::requestDocuments,
                                std::vector<std::string>{
                                    std::string(1, protocol::documentSave),
                                    documentNo,
                                    password
                                }
                        });
                    break;
                case '4':
                    context->userOutputSystem->outputLine("Enter document number");
                    context->userOutputSystem->output(":> ");
                    context->userInputSystem->readNumerical(documentNo);
                    command->internalCommand = protocol::requestDocuments;
                    command->request = protocol::Request::build(
                        {
                                protocol::requestDocuments,
                                std::vector<std::string>{
                                        std::string(1, protocol::documentDelete)
                                }
                        });
                    break;
                default:
                    context->userOutputSystem->outputLine("Incorrect input");
            }
        return command;
    }

} // InvoiceMasterClient