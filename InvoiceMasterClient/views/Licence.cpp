#include "Licence.hpp"
#include "protocol/Request.hpp"
#include "licence/Files.hpp"
#include <fmt/chrono.h>
#include <chrono>
#include <sstream>

namespace InvoiceMasterClient {
    std::unique_ptr<CommandStruct> Licence::run()
    {
        std::string accountName{}, inputName{};
        licence::Files::readClientKey(accountName);

        char choice;
        if (!accountName.empty()) {
            context->userOutputSystem->outputLine("Enter new account name or press Enter to use stored one: " + accountName);
        } else {
            context->userOutputSystem->outputLine("Enter new account name");
        }
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(inputName);
        auto command = std::make_unique<CommandStruct>();

        if (inputName.empty() && accountName.empty()) {
            context->userOutputSystem->outputLine("Invalid input!");
            command->internalCommand = protocol::requestLicence;
            return command;
        }
        accountName = inputName.empty() ? accountName : inputName;
        licence::Files::storeClientKey(accountName);

        context->userOutputSystem->outputLine("1. Enroll licence");
        context->userOutputSystem->outputLine("2. Enter licence key");
        context->userOutputSystem->outputLine("0. Main menu");
        context->userOutputSystem->output(":> ");
        context->userInputSystem->read(choice);

        switch (choice) {
            case '1':
                command->internalCommand = protocol::requestMainMenu;
                command->request = protocol::Request::build(
                        {
                            protocol::requestEnrollLicence,
                            std::vector<std::string>{accountName}
                        });

                break;
            case '2': {
                std::string licenceKey{};
                std::string format = "%s%s";

                const std::chrono::time_point now{std::chrono::system_clock::now()};
                const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};

                std::string date{fmt::format("{:04}{:02}{:02}", static_cast<int>(ymd.year()), static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()))};

                context->userOutputSystem->outputLine("Enter your licence key");
                context->userOutputSystem->output(":> ");
                context->userInputSystem->read(licenceKey);
                command->internalCommand = protocol::requestMainMenu;
                command->request = protocol::Request::build(
                        {
                                protocol::requestSetLicence,
                                std::vector<std::string>{accountName, licenceKey, date, format}
                        });
            }
            break;
            case '0':
                command->internalCommand = protocol::requestMainMenu;
                break;
            default:
                context->userOutputSystem->outputLine("Incorrect input");
                command->internalCommand = protocol::requestLicence;
        }
        return command;
    }
} // InvoiceMasterClient
