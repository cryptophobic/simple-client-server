#pragma once
#include "ActiveRecord.hpp"
#include "schema/Invoice.hpp"
#include "schema/InvoiceItem.hpp"
#include "schema/OverdueInvoice.hpp"
#include "schema/Users.hpp"
#include "schema/Licence.hpp"
#include "schema/Document.hpp"

namespace database {
    extern ActiveRecord<Invoice> invoiceTable;
    extern ActiveRecord<OverdueInvoice> overdueInvoiceTable;
    extern ActiveRecord<InvoiceItem> invoiceItemTable;
    extern ActiveRecord<Users> usersTable;
    extern ActiveRecord<Document> documentsTable;
    extern ActiveRecord<Licence> licenceTable;
} // database