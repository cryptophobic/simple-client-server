#include "InvoiceMasterServer/Application.hpp"
#include "database/Tables.hpp"

void initialisation() {
    database::invoiceItemTable.importFromFile();
    database::invoiceTable.importFromFile();
    database::overdueInvoiceTable.importFromFile();
    database::usersTable.importFromFile();
    database::licenceTable.importFromFile();
    database::documentsTable.importFromFile();
}

void finalization() {
    database::invoiceItemTable.exportToFile();
    database::invoiceTable.exportToFile();
    database::overdueInvoiceTable.exportToFile();
    database::usersTable.exportToFile();
    database::licenceTable.exportToFile();
    database::documentsTable.exportToFile();
}

int main()
{
    initialisation();
    std::shared_ptr<InvoiceMasterServer::Application> app = std::make_shared<InvoiceMasterServer::Application>();
    app->run();
    finalization();
    return 0;
}
