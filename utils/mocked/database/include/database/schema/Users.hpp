#pragma once
#include "database/Entity.hpp"
#include <set>
#include <string>
#include <memory>

namespace database {

    class Users : public Entity, public std::enable_shared_from_this<Users> {
    public:
        static const std::string userId;
        static const std::string salt;
        static const std::string password;
        static const std::string role;
        static const std::string tableName;

        static const std::set<std::string>fields;
        std::set<std::string> getFields() override {
            return fields;
        }

        void saveRecord(const std::string& id) override;
        void saveRecord() override;
    };
} // database
