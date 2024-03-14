#pragma once
#include "database/Entity.hpp"
#include <set>
#include <string>
#include <memory>

namespace database {

    class InvoiceItem : public Entity, public std::enable_shared_from_this<database::InvoiceItem> {
    public:
        static const std::string invoiceNumber;
        static const std::string price;
        static const std::string itemName;
        static const std::string quantity;
        static const std::string tableName;

        static const std::set<std::string>fields;
        std::set<std::string> getFields() override {
            return fields;
        }

        void saveRecord(const std::string& id) override;
        void saveRecord() override;
    };
} // database

