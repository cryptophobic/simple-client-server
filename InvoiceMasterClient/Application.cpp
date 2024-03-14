#include "Application.hpp"
#include "licence/Files.hpp"
#include "View.hpp"
#include "protocol/Request.hpp"
#include <memory>

namespace InvoiceMasterClient {

    void Application::run()
    {
        connector.establishConnection();

        if (controller == nullptr) {
            controller = std::make_unique<Controller>(shared_from_this());
        }
        std::unique_ptr<CommandStruct> command = std::make_unique<CommandStruct>();
        command->internalCommand = protocol::requestVerifyLicence;
        while(connector.isConnected()) {
            std::unique_ptr<View> view = controller->run(command->internalCommand);
            try {
                command = view->run();
                if (!command->request.empty()) {
                    std::unique_ptr<protocol::ResponseStructure> response = connector.sendCommand(command->request);
                    userOutputSystem->formatResponse(response);
                    authorized = response->authorized == protocol::authorized;
                    licenceConfirmed = response->licenceStatus == protocol::licenceConfirmed;
                    if (response->connectionStatus == protocol::disconnected) {
                        connector.closeConnection();
                    }
                }
            }
            catch (std::invalid_argument& e) {
                userOutputSystem->outputLine(e.what());
            } catch (std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                connector.closeConnection();
            }
        }
        std::cout << "Bye!" << std::endl;
        connector.closeConnection();
    }
}
