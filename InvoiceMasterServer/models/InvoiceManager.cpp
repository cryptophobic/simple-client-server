#include "InvoiceManager.hpp"
#include "database/Tables.hpp"
#include "protocol/ApiAccess.hpp"
#include "InvoiceMasterServer/import/Invoice/XMLImport.hpp"

namespace InvoiceMasterServer {

    std::string InvoiceManager::execute(const std::vector<std::string>& arguments)
    {
        if (userId.empty()) {
            throw std::invalid_argument("Unauthorized operation");
        }

        std::string command = arguments[0];
        std::string result;
        switch (command[0]) {
            case protocol::invoiceNew:
                currentInvoice = std::make_unique<Invoice>(userId);
                result = database::InvoiceItem::invoiceNumber + ": " + currentInvoice->getInvoiceNumber();
                break;
            case protocol::invoiceImport: {
                auto invoicePtr = std::make_shared<Invoice>(userId);
                XMLImport xmlImport;
                xmlImport.importInvoice(invoicePtr, arguments[1]);
                result = "Successfully imported " + database::InvoiceItem::invoiceNumber + ": " + invoicePtr->getInvoiceNumber();
                break;
            }
            case protocol::invoiceNewLine:
                if (currentInvoice == nullptr) {
                    throw std::invalid_argument("Please create the invoice before adding the items");
                }
                currentInvoice->addItem(arguments[1], std::stoi(arguments[2]), std::stoi(arguments[3]));
                result = currentInvoice->dump();
                break;
            case protocol::invoiceCancel:
                if (currentInvoice != nullptr) {
                    currentInvoice.reset();
                }
                break;
            case protocol::invoiceSave:
                if (currentInvoice == nullptr) {
                    throw std::invalid_argument("Please create the invoice first");
                }
                currentInvoice->save();
                result = database::InvoiceItem::invoiceNumber + ": " + currentInvoice->getInvoiceNumber();
                currentInvoice.reset();
                break;
            case protocol::invoiceSaveOverdue:
                if (currentInvoice == nullptr) {
                    throw std::invalid_argument("Please create the invoice first");
                }
                currentInvoice->save(std::stoi(arguments[1]));
                result = database::InvoiceItem::invoiceNumber + ": " + currentInvoice->getInvoiceNumber();
                currentInvoice.reset();
                break;
            case protocol::invoiceGet:
                {
                    if (auto invoice = database::invoiceTable.getRecordById(arguments[1]);
                        invoice != nullptr && invoice->getField(database::Invoice::userId) == userId) {
                        result = invoice->toString();
                    }

                    if (auto overdueInvoice = database::overdueInvoiceTable.getRecordById(arguments[1]);
                        overdueInvoice != nullptr && overdueInvoice->getField(database::Invoice::userId) == userId) {
                        result = overdueInvoice->toString();
                    }

                    if (!result.empty()) {
                        for (const auto &record: database::invoiceItemTable.getRecordsByField(
                                database::InvoiceItem::invoiceNumber, arguments[1])) {
                            result += "\n" + record->toString();
                        }
                    }
                }
                break;
            case protocol::invoiceDelete:
                database::invoiceTable.deleteRecordById(arguments[1]);
                database::invoiceItemTable.deleteRecordByField(
                        database::InvoiceItem::invoiceNumber,
                        arguments[1]);
                break;
            case protocol::requestInvoiceList: {
                auto records = database::invoiceTable.getRecordsByField(database::Invoice::userId, userId);
                for (const auto &record: records) {
                    result += database::Invoice::invoiceNumber + ": " +
                              record->getField(database::Invoice::invoiceNumber) + "\n";
                }

                auto overdueRecords = database::overdueInvoiceTable.getRecordsByField(database::OverdueInvoice::userId,
                                                                                      userId);
                for (const auto &record: overdueRecords) {
                    result += database::OverdueInvoice::invoiceNumber + ": " +
                              record->getField(database::OverdueInvoice::invoiceNumber) + "\n";
                }
                break;
            }
            default:
                throw std::invalid_argument("InvoiceManager::execute: Incorrect command");

        }
        return result;
    }

    void InvoiceManager::init(const std::string& newUserId) {
        currentInvoice.reset();
        userId = newUserId;
    }

    void InvoiceManager::finalise() {
        currentInvoice.reset();
        userId = "";
    }

} // InvoiceMasterServer
