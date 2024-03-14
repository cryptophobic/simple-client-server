#pragma once
#include <string>


namespace InvoiceMasterServer {

    class UserManager {
    public:
        void signUp(const std::string& login, const std::string& password);
    protected:
        virtual void validatePassword(const std::string &password);
        virtual void validateUserId(const std::string &userId);
    };

} // InvoiceMasterServer