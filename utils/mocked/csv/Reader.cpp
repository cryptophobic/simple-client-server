#include "include/csv/Reader.hpp"
#include "StringHelper.hpp"

namespace csv {

    void Reader::load() {
        std::string contents{};
        helpers::FileHelper::readEntireFileToString(filePath, contents);

        std::vector<std::string> rows{};
        helpers::StringHelper::splitQuoted(contents, '\n', rows);
        auto header = fetchHeader(rows);
        for (int i = 1; i < rows.size(); i++) {
            auto parsed = parseRow(rows[i], header);
            parsedCsv.emplace_back(parsed);
        }
    }

    std::vector<std::string> Reader::fetchHeader(const std::vector<std::string> &rows) {
        if (rows.empty()) {
            return {};
        }
        std::vector<std::string> header{};
        helpers::StringHelper::splitQuoted(rows[0], ',', header);
        for (auto& column : header) {
            helpers::StringHelper::unquoteString(column);
        }
        return header;
    }

    std::map<std::string, std::string>
    Reader::parseRow(const std::string &row, const std::vector<std::string> &header) {
        std::map<std::string, std::string> parsedRow{};
        std::vector<std::string> rowArray{};
        helpers::StringHelper::splitQuoted(row, ',', rowArray);
        if (rowArray.size() != header.size()) {
            throw std::invalid_argument("CSV file is corrupted");
        }
        for(int i = 0; i < header.size(); i++) {
            parsedRow[header[i]] = rowArray[i];
            helpers::StringHelper::unquoteString(parsedRow[header[i]]);
        }
        return parsedRow;
    }

    std::vector<std::map<std::string, std::string>> Reader::getParsed() {
        if (parsedCsv.empty()) {
            load();
        }
        return parsedCsv;
    }

} // csv
