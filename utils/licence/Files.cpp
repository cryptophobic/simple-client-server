#include "licence/Files.hpp"
#include "FileHelper.hpp"
#include <sstream>
#include <fstream>

namespace licence {
    void Files::storeClientKey(const std::string& userId) {
        std::ofstream licenceFile(std::string(LICENCE_PATH), std::ofstream::out | std::ofstream::trunc);
        licenceFile << userId;
        licenceFile.close();
    }

    void Files::readClientKey(std::string& clientKey) {
        clientKey.clear();
        std::string fileName = std::string(LICENCE_PATH);
        if (!helpers::FileHelper::isFileExists(fileName)) {
            return;
        }

        std::ifstream licenceFile(fileName);
        std::stringstream buffer;
        buffer << licenceFile.rdbuf();
        clientKey = buffer.str();
        licenceFile.close();
    }
} // licence