#include "AuthenticationManager.hpp"
#include "config/settings.hpp"
#include "security/Argon2Wrapper.hpp"
#include "database/Tables.hpp"
#include <regex>

namespace InvoiceMasterServer {
    bool AuthenticationManager::isAuthorized() const
    {
        return _authorized;
    }

    void AuthenticationManager::logout()
    {
        _authorized = false;
        userId = "";
    }

    void AuthenticationManager::login(const std::string& id, std::string& password)
    {
        validateUserId(id);
        authorize(id, password);
        userId = _authorized ? id : userId;
    }

    void AuthenticationManager::authorize(const std::string& id, std::string& password)
    {
        security::Argon2Wrapper hashing;
        auto records = database::usersTable.getRecordsByField(
                database::Users::userId, id);

        if (!records.empty()) {
            _authorized = hashing.verify(
                    password,
                    records[0]->getField(database::Users::salt),
                    records[0]->getField(database::Users::password));
        }
        password.clear();
        records.clear();
        if (!_authorized) {
            throw std::invalid_argument("Login or password is incorrect. Please try again.");
        }
    }

    void AuthenticationManager::validateUserId(const std::string &login)
    {
        std::regex regex("^[^']+$");

        if (!std::regex_match(login, regex) || login.length() > settings::userLoginMaxSize) {
            throw std::invalid_argument("Login or password is incorrect. Please try again.");
        }
    }

    std::string AuthenticationManager::getUserId() {
        return userId;
    }
} // InvoiceMasterServer
