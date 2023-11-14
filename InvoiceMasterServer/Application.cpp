#include "Application.hpp"
#include <memory>

namespace InvoiceMasterServer {

    void Application::run() {
        while (!quit) {
            try {
                service.listen();
            }
            catch (std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                quit = true;
            }

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
        switch (request->parsed->command) {
            case settings::services.login.code:
                loginService.authorize(request->parsed->arguments[0], request->parsed->arguments[1]);
                if (loginService.isAuthorized()) {
                    return std::make_unique<Response>(settings::responseSuccess, settings::authorized, "");
                }
                break;
            case settings::services.admin.code:
                if (loginService.isAuthorized()) {
                    quit = true;
                    return std::make_unique<Response>(settings::responseSuccess, settings::disconnected, "");
                }
            case settings::services.quit.code:
                return std::make_unique<Response>(settings::responseSuccess, settings::disconnected, "");
            default:
                break;
        }
        return std::make_unique<Response>(
                settings::responseError,
                loginService.isAuthorized() ? settings::authorized : settings::notAuthorized,
                "");
    }
}