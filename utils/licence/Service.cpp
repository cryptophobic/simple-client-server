#include "licence/Service.hpp"
#include "StringHelper.hpp"
#include "security/Argon2Wrapper.hpp"
#include "security/config.hpp"
#include "database/Tables.hpp"
#include "protocol/Agreements.hpp"
#include "email/Inbox.hpp"
#include <chrono>
#include <sstream>
#include <iostream>
#include <fmt/chrono.h>

namespace licence {

    const std::set<std::string> Service::licences{"admin", "user"};

    void Service::confirmLicence(const std::string& userId, const std::string& key) {
        if (licences.contains(userId)) {
            auto records = database::licenceTable.getRecordsByField(database::Licence::userId, userId);
            if (!records.empty()) {
                std::string confirmed{1, protocol::licenceNotConfirmed};
                security::Argon2Wrapper hashing;
                if (hashing.verify(
                        key,
                        records[0]->getField(database::Licence::salt),
                        records[0]->getField(database::Licence::key))) {
                    confirmed = protocol::licenceConfirmed;
                }
                records[0]->setField(database::Licence::confirmed, confirmed);
                records[0]->saveRecord();
            }
        }
    }
    void Service::enrollLicence(const std::string& userId) {

        if (!licences.contains(userId)) {
            throw std::invalid_argument("Invalid userId");
        }

        const std::chrono::time_point now{std::chrono::system_clock::now()};
        const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};

        std::string salt{};
        std::string clientKey{};
        helpers::StringHelper::randomString(salt, security::saltLength);
        helpers::StringHelper::randomString(clientKey, 16);

        std::stringstream clientKeyUpdated;
        clientKeyUpdated << clientKey << fmt::format("{:04}{:02}{:02}", static_cast<int>(ymd.year()), static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()));

        std::string hash;
        security::Argon2Wrapper hashing;

        hashing.hashString(clientKeyUpdated.str(), salt, hash);

        auto records = database::licenceTable.getRecordsByField(database::Licence::userId, userId);
        std::shared_ptr<database::Licence> licenceRecord;
        if (!records.empty()) {
            licenceRecord = records[0];
        } else {
            licenceRecord = std::make_shared<database::Licence>();
            licenceRecord->setField(database::Licence::userId, userId);
        }
        licenceRecord->setField(database::Licence::key, hash);
        licenceRecord->setField(database::Licence::salt, salt);
        licenceRecord->setField(database::Licence::confirmed, {1, protocol::licenceNotConfirmed});
        licenceRecord->saveRecord();

        email::Inbox::send(userId, "Please submit this key to confirm your licence: " + clientKey);
    }

} // licenceService
