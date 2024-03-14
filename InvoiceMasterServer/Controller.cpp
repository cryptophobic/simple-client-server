#include "Controller.hpp"
#include "protocol/ApiAccess.hpp"
#include "protocol/Request.hpp"
#include "protocol/Response.hpp"
#include <string>

namespace InvoiceMasterServer {

    std::string Controller::execute(std::string &requestMessage) {
        char responseCode = protocol::responseSuccess;
        std::string responseBody;
        try {
            std::unique_ptr<protocol::RequestStructure> request = parseRequest(requestMessage);
            responseBody = processRequest(std::move(request));
        } catch (std::invalid_argument &e) {
            responseCode = protocol::responseError;
            responseBody = e.what();
        } catch (std::runtime_error &e) {
            // Problems with connection.
            std::cout << e.what();
            return {};
        }

        return protocol::Response::build(
                {
                    responseCode,
                    context->loginService.isAuthorized() ? protocol::authorized : protocol::notAuthorized,
                    context->isDisconnected() ? protocol::disconnected : protocol::connected,
                    context->licenceService.isLicenceConfirmed() ? protocol::licenceConfirmed : protocol::licenceNotConfirmed,
                    responseBody
                });
    }

    std::unique_ptr<protocol::RequestStructure> Controller::parseRequest(const std::string& requestMessage) {
        return protocol::Request::parse(requestMessage);
    }

    std::string Controller::processRequest(std::unique_ptr<protocol::RequestStructure> request) {
        std::string responseBody;
        switch (request->command) {
            case protocol::requestInvoice:
                responseBody = context->invoiceService.execute(request->arguments);
                break;
            case protocol::requestDocuments:
                responseBody = context->documentsService.execute(context->loginService.getUserId(), request->arguments);
                break;
            case protocol::requestLogout:
                context->loginService.logout();
                context->invoiceService.finalise();
                break;
            case protocol::requestSignUp:
                context->userService.signUp(request->arguments[0], request->arguments[1]);
                responseBody = request->arguments[0] + " signed up successfully. Please proceed to sign in.";
                break;
            case protocol::requestLogin:
                context->loginService.login(request->arguments[0], request->arguments[1]);
                context->invoiceService.init(context->loginService.getUserId());
                if (context->loginService.isAuthorized()) {
                    responseBody = context->loginService.getUserId() + " authorized successfully.";
                }
                break;
            case protocol::requestAdminAccess:
                if (context->loginService.isAuthorized()) {
                    context->loginService.logout();
                    context->setQuit();
                    context->setDisconnected();
                }
                break;
            case protocol::requestSetLicence:
                responseBody = context->licenceService.setLicence(
                        request->arguments[0],
                        request->arguments[1],
                        request->arguments[2],
                        request->arguments[3]);
                break;
            case protocol::requestEnrollLicence:
                responseBody = context->licenceService.enrollLicence(request->arguments[0]);
                break;
            case protocol::requestVerifyLicence:
                responseBody = context->licenceService.verifyLicence(request->arguments[0]);
                break;
            case protocol::requestDisconnect:
                context->loginService.logout();
                context->invoiceService.finalise();
                context->setDisconnected();
                break;
            default:
                throw std::invalid_argument("Invalid command");
        }
        return responseBody;
    }
} // InvoiceMasterServer
