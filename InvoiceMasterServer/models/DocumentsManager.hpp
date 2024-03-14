#pragma once
#include <string>
#include <vector>

namespace InvoiceMasterServer {

    class DocumentsManager {
    protected:
        const std::string serverFilesDir = std::string(SERVER_PROJECT_DIR) + "/localFiles/";
    public:
        std::string execute(const std::string& userId, const std::vector<std::string>& arguments);
    };

} // InvoiceMasterServer