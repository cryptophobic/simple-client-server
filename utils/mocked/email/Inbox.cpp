#include "email/Inbox.hpp"
#include <sstream>
#include "FileHelper.hpp"

namespace email {
    void Inbox::send(const std::string& userId, const std::string& body) {
        std::ofstream dumpFile(std::string(MAILBOX_DIR) + std::filesystem::path::preferred_separator + userId, std::ofstream::out | std::ofstream::trunc);
        dumpFile << body;
        dumpFile.close();
    }

    void Inbox::receive(const std::string& userId, std::string& body) {
        body.clear();
        std::string fileName = std::string(MAILBOX_DIR) + std::filesystem::path::preferred_separator + userId;
        if (!helpers::FileHelper::isFileExists(fileName)) {
            return;
        }

        std::ifstream importFile(fileName);
        std::stringstream buffer;
        buffer << importFile.rdbuf();
        body = buffer.str();
        importFile.close();
    }
} // email
