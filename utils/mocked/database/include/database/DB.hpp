#pragma once
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <memory>
#include <set>
#include "database/Entity.hpp"
#include "database/ActiveRecord.hpp"

namespace database {

    class DB {
    protected:

        std::vector<std::map<std::string, std::string>> lastResponse;
        DBCommands command = DBCommands::undefinedCommand;
        std::string table;
        std::vector<std::string> fields;
        std::vector<std::string> condition;
        void parse(const std::string& query);
        void parseFields(std::string& fieldsString);
        void parseCondition(std::string& conditionString);
        std::string prepareParam(const std::string& param);
        void clear();

    public:
        virtual void execute(const std::string& query, const std::vector<std::string>& arguments);
        virtual void execute(const std::string& query);
        virtual std::vector<std::map<std::string, std::string>> getLastResponse();
        virtual ~DB() = default;
    };

} // database
