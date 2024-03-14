#include "database/schema/Invoice.hpp"
#include "database/Tables.hpp"
#include <string>

namespace database {
    const std::string Invoice::invoiceNumber = "invoiceNumber";
    const std::string Invoice::totals        = "totals";
    const std::string Invoice::userId        = "userId";
    const std::string Invoice::tableName     = "invoices";
    const std::set<std::string>Invoice::fields {invoiceNumber, totals, userId};

    void Invoice::saveRecord(const std::string& newId) {
        invoiceTable.setRecordWithId(newId, shared_from_this());
    }

    void Invoice::saveRecord() {
        invoiceTable.setNewRecord(shared_from_this());
    }
}
