#include "DocumentsManager.hpp"
#include "protocol/ApiAccess.hpp"
#include "database/Tables.hpp"
#include "security/AESGCMEncrypt.hpp"
#include <memory>
#include <vector>

namespace InvoiceMasterServer {
    std::string DocumentsManager::execute(const std::string& userId, const std::vector<std::string>& arguments) {

        std::string command = arguments[0];
        std::string result;

        switch (command[0]) {
            case protocol::requestDocuments:
                for (const auto &record: database::documentsTable.getRecordsByField(database::Document::userId, userId)) {
                    result += database::Document::fileName + ": " + record->getField(database::Document::fileName) + "\n";
                }
                break;
            case protocol::documentSave:
            {
                const std::string& invoiceId = arguments[1];
                std::string fileContents;
                if (auto invoice = database::invoiceTable.getRecordById(invoiceId);
                        invoice != nullptr && invoice->getField(database::Invoice::userId) == userId) {
                    fileContents = invoice->toString();
                }

                if (auto overdueInvoice = database::overdueInvoiceTable.getRecordById(invoiceId);
                        overdueInvoice != nullptr && overdueInvoice->getField(database::Invoice::userId) == userId) {
                    fileContents = overdueInvoice->toString();
                }

                for (const auto &record: database::invoiceItemTable.getRecordsByField(
                        database::InvoiceItem::invoiceNumber, invoiceId)) {
                    fileContents += "\n" + record->toString();
                }
                if (!fileContents.empty()) {
                    std::string fileName{userId + invoiceId};
                    const std::string& password{arguments[2]};
                    std::vector<unsigned char> salt, outputBuffer;
                    const std::vector<unsigned char> plainString(fileContents.begin(), fileContents.end());
                    std::string str(salt.begin(), salt.end());
                    security::AESGCMEncrypt encrypt;
                    encrypt.encrypt(password, plainString, salt, outputBuffer);

                    helpers::FileHelper::writeVectorToFile(serverFilesDir + fileName, outputBuffer);
                    auto document = std::make_shared<database::Document>();
                    document->setField(database::Document::userId, userId);
                    document->setField(database::Document::fileName, fileName);
                    document->setField(database::Document::salt, std::string(salt.begin(), salt.end()));
                    document->saveRecord();
                    result = "Document " + invoiceId + " for user " + userId + " saved successfully";
                }
            }
            break;
            case protocol::documentLoad: {
                const std::string& invoiceId{arguments[1]};
                const std::string& password{arguments[2]};
                std::string fileName{userId + invoiceId};

                if (auto documents = database::documentsTable.getRecordsByField(database::Document::fileName, fileName);
                        !documents.empty() && documents[0]->getField(database::Document::userId) == userId) {

                    auto& document = documents[0];

                    std::vector<unsigned char> fileContents;
                    helpers::FileHelper::readEntireFileToVector(serverFilesDir + fileName, fileContents);


                    std::vector<unsigned char> plaintext;
                    std::string salt = document->getField(database::Document::salt);
                    security::AESGCMEncrypt encrypt;
                    encrypt.decrypt(password, std::vector<unsigned char>(salt.begin(), salt.end()),fileContents,  plaintext);

                    result = "Document #" + fileName + "\n" + std::string(plaintext.begin(), plaintext.end());
                }
            }
            break;
            case protocol::documentDelete: {
                std::string fileName{userId + arguments[1]};

                database::documentsTable.deleteRecordByField(database::Document::fileName, fileName);
            }
            break;
            default:
                throw std::invalid_argument("Incorrect parameter");
        }

        return result;
    }
} // InvoiceMasterServer
