#pragma once
#include <vector>
#include <map>
#include <string>

namespace csv {

    class Writer {
    protected:
        std::vector<std::map<std::string, std::string>> rows;
        std::vector<std::string> splitContents(const std::string& contents, char delimiter);
        std::vector<std::string> fetchHeader();
        std::map<std::string, std::string> parseRow(const std::string& row, const std::vector<std::string>& header);
    public:
        Writer(const std::vector<std::map<std::string, std::string>>& csvRows) : rows(csvRows){};
        void save(const std::string& fileName);

    };

} // csv