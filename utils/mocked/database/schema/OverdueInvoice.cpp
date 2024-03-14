#include "database/schema/OverdueInvoice.hpp"
#include "database/Tables.hpp"
#include <string>
#include <set>

namespace database {
    const std::string OverdueInvoice::feeCharged    = "chargedFee";
    const std::string OverdueInvoice::invoiceNumber = "invoiceNumber";
    const std::string OverdueInvoice::totals        = "totals";
    const std::string OverdueInvoice::userId        = "userId";
    const std::string OverdueInvoice::tableName     = "overdue_invoices";

    const std::set<std::string>OverdueInvoice::fields {
        OverdueInvoice::invoiceNumber,
        OverdueInvoice::totals,
        OverdueInvoice::userId,
        OverdueInvoice::feeCharged};

    void OverdueInvoice::saveRecord(const std::string& newId) {
        overdueInvoiceTable.setRecordWithId(newId, shared_from_this());
    }

    void OverdueInvoice::saveRecord() {
        overdueInvoiceTable.setNewRecord(shared_from_this());
    }
}
