#pragma once
#include <memory>
#include "database/DB.hpp"

namespace InvoiceMasterServer {

    class LicenceManager {
    protected:
        bool _licenceConfirmed = false;
        std::unique_ptr<database::DB> dbConnection;
    public:
        LicenceManager() : dbConnection(std::make_unique<database::DB>()){};
        [[nodiscard]] bool isLicenceConfirmed() const;
        virtual std::string enrollLicence(const std::string& userId);
        virtual std::string verifyLicence(const std::string& userId);
        virtual void confirmLicence(const std::string& userId, const std::string& licenceFormatted);
        virtual void validateDateFormat(const std::string& date);
        virtual std::string setLicence(
                const std::string& userId,
                const std::string& key,
                const std::string& date,
                const std::string& format);
    };

} // InvoiceMasterServer