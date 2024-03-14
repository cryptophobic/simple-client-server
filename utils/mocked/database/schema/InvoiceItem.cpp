#include "database/schema/InvoiceItem.hpp"
#include <string>
#include "database/Tables.hpp"

namespace database {
    const std::string InvoiceItem::invoiceNumber = "invoiceNumber";
    const std::string InvoiceItem::price         = "price";
    const std::string InvoiceItem::quantity      = "quantity";
    const std::string InvoiceItem::itemName      = "itemName";
    const std::string InvoiceItem::tableName     = "invoice_items";
    const std::set<std::string>InvoiceItem::fields {invoiceNumber, price, quantity, itemName};

    void InvoiceItem::saveRecord(const std::string& newId) {
        invoiceItemTable.setRecordWithId(newId, shared_from_this());
    }

    void InvoiceItem::saveRecord() {
        invoiceItemTable.setNewRecord(shared_from_this());
    }
}