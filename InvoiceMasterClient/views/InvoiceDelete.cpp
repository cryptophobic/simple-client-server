#include "InvoiceDelete.hpp"
#include "protocol/Request.hpp"

namespace InvoiceMasterClient {

    std::unique_ptr<CommandStruct> InvoiceDelete::run() {
        std::string choice;
        context->userOutputSystem->outputLine("Please enter existing invoice id");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(choice);
        auto command = std::make_unique<CommandStruct>();
        command->internalCommand = protocol::requestInvoice;
        command->request = protocol::Request::build(
                {
                        protocol::requestInvoice,
                        std::vector<std::string>{std::string{protocol::invoiceDelete}, choice}
                });
        return command;
    }
}
