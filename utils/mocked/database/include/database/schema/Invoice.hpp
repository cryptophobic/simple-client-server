#pragma once
#include "config/settings.hpp"
#include "database/Entity.hpp"
#include <string>
#include <set>
#include <memory>

namespace database {

    class Invoice : public Entity, public std::enable_shared_from_this<database::Invoice> {
    public:
        static const std::string invoiceNumber;
        static const std::string totals;
        static const std::string userId;
        static const std::string tableName;
        static const std::set<std::string>fields;

        std::set<std::string> getFields() override {
            return fields;
        }

        void saveRecord(const std::string& id) override;
        void saveRecord() override;
    };
} // database
