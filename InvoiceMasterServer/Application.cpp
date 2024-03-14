#include "Application.hpp"
#include "protocol/ApiAccess.hpp"
#include <memory>
#include <vector>

namespace InvoiceMasterServer {

    void Application::run()
    {
        while (!quit) {
            waitForConnection();
            std::string requestMessage;
            if (controller == nullptr) {
                controller = std::make_unique<Controller>(shared_from_this());
            }
            disconnected = false;
            invoiceService.init();
            while(readFromClient(requestMessage)) {
                std::string response = controller->execute(requestMessage);
                service.sendResponse(response);
            }
            loginService.logout();
        }
    }

    void Application::waitForConnection()
    {
        try {
            service.listen();
        }
        catch (std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            quit = true;
        }
    }

    bool Application::readFromClient(std::string &s)
    {
        if (!service.isClientConnected()) {
            return false;
        }
        service.read(s);
        return true;
    }
}
