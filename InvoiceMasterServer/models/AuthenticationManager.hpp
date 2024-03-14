#pragma once
#include <string>
#include <memory>
#include "database/DB.hpp"

namespace InvoiceMasterServer {

    class AuthenticationManager {
    public:
        [[nodiscard]] bool isAuthorized() const;
        virtual void login(const std::string& id, std::string& password);
        virtual void logout();
        virtual std::string getUserId();
        AuthenticationManager(std::unique_ptr<database::DB> newDbConnection) : dbConnection(std::move(newDbConnection)) {};
        AuthenticationManager() : dbConnection(std::make_unique<database::DB>()){};

    protected:
        std::string userId;
        std::unique_ptr<database::DB> dbConnection;

        bool _authorized = false;

        virtual void authorize (const std::string& userId, std::string& password);
        virtual void validateUserId(const std::string& userId);
    };

} // InvoiceMasterServer
