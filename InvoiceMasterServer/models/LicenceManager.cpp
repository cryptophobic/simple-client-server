#include "InvoiceMasterServer/models/LicenceManager.hpp"
#include "database/Tables.hpp"
#include "security/Argon2Wrapper.hpp"
#include "licence/Service.hpp"
#include "protocol/Agreements.hpp"
#include <ctime>
#include <sstream>

namespace InvoiceMasterServer {
    bool LicenceManager::isLicenceConfirmed() const {
        return _licenceConfirmed;
    }

    std::string LicenceManager::setLicence(
            const std::string& userId,
            const std::string& key,
            const std::string& date,
            const std::string& format) {
        validateDateFormat(date);
        confirmLicence(userId, key+date);
        verifyLicence(userId);
        return "Licence successfully confirmed.";
    }

    void LicenceManager::validateDateFormat(const std::string& date) {
        struct tm date_time = {};
        std::istringstream ss(date);
        ss >> std::get_time(&date_time, "%Y%m%d");
        if (ss.fail()) {
            throw std::invalid_argument("Incorrect format of date");
        }
    }

    void LicenceManager::confirmLicence(const std::string& userId, const std::string& licenceFormatted) {
        licence::Service::confirmLicence(userId, licenceFormatted);
    }

    std::string LicenceManager::enrollLicence(const std::string& userId) {
        licence::Service::enrollLicence(userId);
        return "Licence key has been sent to your " + userId + " account. Please check your mailbox";
    }

    std::string LicenceManager::verifyLicence(const std::string& userId) {
        auto result = database::licenceTable.getRecordsByField(database::Licence::userId, userId);
        if (!result.empty() && result[0]->getField(database::Licence::confirmed) == std::string{protocol::licenceConfirmed}) {
            _licenceConfirmed = true;
        } else {
            _licenceConfirmed = false;
            throw std::invalid_argument("Incorrect licence data");
        }
        return "Licence successfully verified";
    }

} // InvoiceMasterServer
