#include "Controller.hpp"
#include "views/Login.hpp"
#include "views/AdminAccess.hpp"
#include "views/MainMenu.hpp"
#include "views/Quit.hpp"
#include "views/Logout.hpp"
#include "views/InvoiceMenu.hpp"
#include "views/InvoiceNew.hpp"
#include "views/InvoiceGet.hpp"
#include "views/InvoiceDelete.hpp"
#include "views/Licence.hpp"
#include "views/LicenceVerify.hpp"
#include "views/Documents.hpp"
#include "views/SignUp.hpp"
#include "protocol/ApiAccess.hpp"

namespace InvoiceMasterClient {

    std::unique_ptr<View> Controller::run(char code)
    {
        switch (code) {
            case protocol::invoiceNew:
                return std::make_unique<InvoiceNew>(context);
            case protocol::invoiceGet:
                return std::make_unique<InvoiceGet>(context);
            case protocol::invoiceDelete:
                return std::make_unique<InvoiceDelete>(context);
            case protocol::requestInvoice:
                return std::make_unique<InvoiceMenu>(context);
            case protocol::requestLogout:
                return std::make_unique<Logout>(context);
            case protocol::requestLogin:
                return std::make_unique<Login>(context);
            case protocol::requestAdminAccess:
                return std::make_unique<AdminAccess>(context);
            case protocol::requestDisconnect:
                return std::make_unique<Quit>(context);
            case protocol::requestLicence:
                return std::make_unique<Licence>(context);
            case protocol::requestVerifyLicence:
                return std::make_unique<LicenceVerify>(context);
            case protocol::requestSignUp:
                return std::make_unique<SignUp>(context);
            case protocol::requestDocuments:
                return std::make_unique<Documents>(context);
            default:
                return std::make_unique<MainMenu>(context);
        }
    }
} // InvoiceMasterClient
