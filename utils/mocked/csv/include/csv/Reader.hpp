#pragma once
#include <string>
#include <vector>
#include <map>
#include "FileHelper.hpp"

namespace csv {

    class Reader {
    protected:
        std::string filePath;
        void load();
        std::vector<std::map<std::string, std::string>> parsedCsv;
        std::vector<std::string> fetchHeader(const std::vector<std::string>& row);
        std::map<std::string, std::string> parseRow(const std::string& row, const std::vector<std::string>& header);
    public:
        Reader(const std::string& csvFilePath) : filePath(csvFilePath){
            if (!helpers::FileHelper::isFileExists(csvFilePath)) {
                throw std::invalid_argument("File does not exists: " + csvFilePath);
            }
        };
        std::vector<std::map<std::string, std::string>> getParsed();
    };

} // csv