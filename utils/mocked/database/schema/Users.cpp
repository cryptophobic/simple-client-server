#include "database/schema/Users.hpp"
#include "database/Tables.hpp"

namespace database {
    const std::string Users::userId   = "userId";
    const std::string Users::salt     = "salt";
    const std::string Users::password = "password";
    const std::string Users::role     = "role";
    const std::set<std::string>Users::fields {userId, password, salt, role};
    const std::string Users::tableName = "users";

    void Users::saveRecord(const std::string& newId) {
        usersTable.setRecordWithId(newId, shared_from_this());
    }

    void Users::saveRecord() {
        usersTable.setNewRecord(shared_from_this());
    }
} // database
