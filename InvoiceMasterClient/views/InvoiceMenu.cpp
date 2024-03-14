#include "InvoiceMenu.hpp"
#include "protocol/Request.hpp"
#include "FileHelper.hpp"
#include "config/settings.hpp"
#include <vector>
#include <string>

namespace InvoiceMasterClient {
    std::unique_ptr<CommandStruct> InvoiceMenu::run()
    {
        char choice;
        context->userOutputSystem->outputLine("0. Main menu");
        context->userOutputSystem->outputLine("1. Get invoice list");
        context->userOutputSystem->outputLine("2. Get invoice by id");
        context->userOutputSystem->outputLine("3. Delete invoice by id");
        context->userOutputSystem->outputLine("4. Create invoice");
        context->userOutputSystem->outputLine("5. import invoice");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(choice);
        auto command = std::make_unique<CommandStruct>();

        switch (choice) {
            case '1':
                command->internalCommand = protocol::requestInvoice;
                command->request = protocol::Request::build({
                    protocol::requestInvoice,
                    std::vector<std::string>{std::string{protocol::requestInvoiceList}}
                    });
                break;
            case '2':
                command->internalCommand = protocol::invoiceGet;
                break;
            case '3':
                command->internalCommand = protocol::invoiceDelete;
                break;
            case '4':
                command->internalCommand = protocol::invoiceNew;
                command->request = protocol::Request::build(
                        {protocol::requestInvoice,
                        std::vector<std::string>{std::string{protocol::invoiceNew}}});
                break;
            case '5':
                {
                    std::string fileBuf;
                    std::string fileName =  invoiceFilePathXML;
                    helpers::FileHelper::readEntireFileToString(fileName, fileBuf);
                    command->internalCommand = protocol::requestInvoice;
                    command->request = protocol::Request::build(
                            {protocol::requestInvoice,
                             std::vector<std::string>{std::string{protocol::invoiceImport}, fileBuf}});
                }
                break;
            case '0':
                command->internalCommand = protocol::requestMainMenu;
                break;
            default:
                context->userOutputSystem->outputLine("Incorrect input");
                command->internalCommand = protocol::requestInvoice;
        }
        return command;
    }
} // InvoiceMasterClient
