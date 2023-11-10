#include "Application.hpp"
#include <memory>

namespace InvoiceMasterServer {

    void Application::run() {
        while (!quit) {
            service.listen();

            while (service.isClientConnected()) {
                std::unique_ptr<Request> request = service.receiveCommand();
                std::unique_ptr<Response> response = controller(std::move(request));
                service.sendResponse(std::move(response));
            }
        }
    }

    //TODO: going to move to controller component
    std::unique_ptr<Response> Application::controller(std::unique_ptr<Request> request)
    {
        std::unique_ptr<Response> response = std::make_unique<Response>();
        switch (request->parsed->command) {
            case settings::services.login.code:
                loginService.authorise(request->parsed->arguments[0], request->parsed->arguments[1]);
                if (loginService.isAuthorised()) {
                    return std::make_unique<Response>(settings::responseSuccess, "");
                }
                break;
            case settings::services.admin.code:
                if (loginService.isAuthorised()) {
                    quit = true;
                    return std::make_unique<Response>(settings::responseSuccess, "");
                }
            default:
                break;
        }
        return std::move(response);
    }

}