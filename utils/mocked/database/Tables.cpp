#include "include/database/Tables.hpp"

namespace database {
    ActiveRecord<Invoice> invoiceTable;
    ActiveRecord<OverdueInvoice> overdueInvoiceTable;
    ActiveRecord<InvoiceItem> invoiceItemTable;
    ActiveRecord<Users> usersTable;
    ActiveRecord<Document> documentsTable;
    ActiveRecord<Licence> licenceTable;
}