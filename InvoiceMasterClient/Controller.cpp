#include "Controller.hpp"
#include "views/Login.hpp"
#include "views/AdminAccess.hpp"
#include "views/MainMenu.hpp"
#include "views/Quit.hpp"
#include "ServiceConnector/Request.hpp"

namespace InvoiceMasterClient {

    std::unique_ptr<View> Controller::run(char code)
    {
        switch (code) {
            case settings::services.login.code:
                return std::make_unique<Login>();
            case settings::services.admin.code:
                return std::make_unique<AdminAccess>();
            case settings::services.quit.code:
                return std::make_unique<Quit>();
            default:
                return std::make_unique<MainMenu>();
        }
    }
} // InvoiceMasterClient
