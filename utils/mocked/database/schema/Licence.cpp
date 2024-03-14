#include "database/schema/Licence.hpp"
#include "database/Tables.hpp"

namespace database {
    const std::string Licence::userId    = "userId";
    const std::string Licence::salt      = "salt";
    const std::string Licence::key       = "key";
    const std::string Licence::confirmed = "confirmed";
    const std::set<std::string>Licence::fields {userId, key, salt, confirmed};
    const std::string Licence::tableName = "licence";

    void Licence::saveRecord(const std::string& newId) {
        licenceTable.setRecordWithId(newId, shared_from_this());
    }

    void Licence::saveRecord() {
        licenceTable.setNewRecord(shared_from_this());
    }
} // database
