#include "UserManager.hpp"
#include "config/settings.hpp"
#include "security/config.hpp"
#include "security/Argon2Wrapper.hpp"
#include "database/schema/Users.hpp"
#include "StringHelper.hpp"
#include <regex>

namespace InvoiceMasterServer {

    void UserManager::signUp(const std::string &userId, const std::string &password) {
        validateUserId(userId);
        validatePassword(password);

        std::string salt{};
        helpers::StringHelper::randomBytes(salt, security::saltLength);
        security::Argon2Wrapper hashing;
        std::string hash{};
        hashing.hashString(password, salt, hash);

        auto userNewRecord = std::make_shared<database::Users>();
        userNewRecord->setField(database::Users::userId, userId);
        userNewRecord->setField(database::Users::salt, salt);
        userNewRecord->setField(database::Users::password, hash);
        userNewRecord->saveRecord();
    }

    void UserManager::validateUserId(const std::string &userId) {
        std::regex regex("^[a-zA-Z]+[a-zA-Z0-9_]*$");

        if (!std::regex_match(userId, regex) || userId.length() > settings::userLoginMaxSize) {
            throw std::invalid_argument("User id max length is " + std::to_string(settings::userLoginMaxSize) + ". Only alphanumeric characters and underscores are allowed.");
        }
    }

    void UserManager::validatePassword(const std::string &password) {
        std::regex regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
        if (!std::regex_match(password, regex)) {
            throw std::invalid_argument("Password value must be minimum eight characters, at least one uppercase letter, one lowercase letter and one number");
        }
    }
} // InvoiceMasterServer
