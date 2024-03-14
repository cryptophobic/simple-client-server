#include "database/schema/Document.hpp"
#include "database/Tables.hpp"

namespace database {
    const std::string Document::userId    = "userId";
    const std::string Document::fileName  = "fileName";
    const std::string Document::salt      = "salt";
    const std::string Document::tableName = "documents";

    const std::set<std::string>Document::fields {userId, fileName, salt};

    void Document::saveRecord(const std::string& newId) {
        documentsTable.setRecordWithId(newId, shared_from_this());
    }

    void Document::saveRecord() {
        documentsTable.setNewRecord(shared_from_this());
    }
} // database
