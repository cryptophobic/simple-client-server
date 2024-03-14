#include "InvoiceNew.hpp"
#include "protocol/Request.hpp"
#include "config/settings.hpp"
#include <vector>

namespace InvoiceMasterClient {

    std::unique_ptr<CommandStruct> InvoiceNew::run() {
        std::string name, price, quantity;
        auto command = std::make_unique<CommandStruct>();

        do {
            bool ready = !(name.empty() || price.empty() || quantity.empty());
            context->userOutputSystem->outputLine("Please enter item's name, price and quantity fields");
            context->userOutputSystem->outputLine("1. Edit name. (" + name + ")");
            context->userOutputSystem->outputLine("2. Edit price. (" + price + ")");
            context->userOutputSystem->outputLine("3. Edit quantity. (" + quantity + ")");
            if (ready) {
                context->userOutputSystem->outputLine("4. Add item");
            }
            context->userOutputSystem->outputLine("5. Place invoice");
            context->userOutputSystem->outputLine("6. Place invoice overdue");
            context->userOutputSystem->outputLine("0. Cancel");
            context->userOutputSystem->output(":> ");

            char choice;
            context->userInputSystem->read(choice);

            switch (choice) {
                case '0':
                    command->internalCommand = protocol::requestInvoice;
                    command->request = protocol::Request::build(
                            {
                                    protocol::requestInvoice,
                                    std::vector<std::string>{std::string{protocol::invoiceCancel}}
                            });
                    break;
                case '1':
                    context->userOutputSystem->outputLine("Enter name");
                    context->userOutputSystem->output(":> ");
                    context->userInputSystem->read(name);
                    break;
                case '2':
                    context->userOutputSystem->outputLine("Enter price (integer only)");
                    context->userOutputSystem->output(":> ");
                    context->userInputSystem->readNumerical(price);
                    break;
                case '3':
                    context->userOutputSystem->outputLine("Enter quantity (integer only)");
                    context->userOutputSystem->output(":> ");
                    context->userInputSystem->readNumerical(quantity);
                    break;
                case '4':
                    if (ready) {
                        command->internalCommand = protocol::invoiceNew;
                        command->request = protocol::Request::build(
                                {
                                        protocol::requestInvoice,
                                        std::vector<std::string>{
                                                std::string{protocol::invoiceNewLine},
                                                name,
                                                price,
                                                quantity
                                        }
                                });
                    } else {
                        context->userOutputSystem->outputLine("Incorrect input");
                    }
                    break;
                case '5':
                    command->internalCommand = protocol::requestInvoice;
                    command->request = protocol::Request::build(
                            {
                                    protocol::requestInvoice,
                                    std::vector<std::string>{std::string{protocol::invoiceSave}}
                            });
                    break;
                case '6':
                    command->internalCommand = protocol::requestInvoice;
                    command->request = protocol::Request::build(
                            {
                                    protocol::requestInvoice,
                                    std::vector<std::string>{
                                        std::string{protocol::invoiceSaveOverdue},
                                        std::string{std::to_string(settings::defaultOverdueFee)}}
                            });
                    break;
                default:
                    context->userOutputSystem->outputLine("Incorrect input");
            }
        } while (command->request.empty());
        return command;
    }

} // InvoiceMasterClient