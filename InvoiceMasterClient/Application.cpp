#include "Application.hpp"
#include "View.hpp"

namespace InvoiceMasterClient {

    bool Application::authorized;
    ServiceConnector Application::connector;

    void Application::run()
    {
        connector.establishConnection();
        std::unique_ptr<CommandStruct> command = std::make_unique<CommandStruct>();
        while(connector.isConnected()) {
            std::unique_ptr<View> view = Controller::run(command->internalCommand->code);
            command = view->run();
            if (command->request != nullptr) {
                try {
                    std::unique_ptr<Response> response = connector.sendCommand(std::move(command->request));
                    //TODO: response body handling
                    authorized = response->parsed->isAuthorized;
                    if (response->parsed->disconnected) {
                        connector.closeConnection();
                    }

                }
                catch (std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                    connector.closeConnection();
                }
            }
        }
        std::cout << "Bye!" << std::endl;
        connector.closeConnection();
    }

    bool Application::isAuthorized()
    {
        return authorized;
    }
}
