#include "include/csv/Writer.hpp"
#include "StringHelper.hpp"
#include "FileHelper.hpp"

namespace csv {

    void Writer::save(const std::string &fileName) {
        auto header = fetchHeader();
        std::string csvContents{}, buffer{};
        std::vector<std::string> rowArray{header.size(), ""};

        for (int i = 0; i < header.size(); i++) {
            rowArray[i] = header[i];
            helpers::StringHelper::quoteString(rowArray[i]);
        }

        helpers::StringHelper::join(rowArray, ',', buffer);
        csvContents += buffer;

        for(auto& row: rows) {
            if (header.size() != row.size()) {
                throw std::invalid_argument("Corrupted csv data");
            }
            for (int i = 0; i < header.size(); i++) {
                rowArray[i] = row[header[i]];
                helpers::StringHelper::quoteString(rowArray[i]);
            }
            helpers::StringHelper::join(rowArray, ',', buffer);
            csvContents += std::string(1, '\n') + buffer;
        }
        helpers::FileHelper::writeStringToFile(fileName, csvContents);

    }

    std::vector<std::string> Writer::fetchHeader() {
        std::vector<std::string> header;
        if (!rows.empty()) {
            for (auto const& [key, value] : rows[0]) {
                header.emplace_back(key);
            }
        }
        return header;
    }
} // csv
