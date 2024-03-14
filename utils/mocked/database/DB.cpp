#include "database/DB.hpp"
#include "StringHelper.hpp"
#include "database/schema/Invoice.hpp"
#include "database/schema/InvoiceItem.hpp"
#include "database/schema/OverdueInvoice.hpp"
#include "database/schema/Users.hpp"
#include "database/Tables.hpp"

namespace database {

    void DB::parse(const std::string &query) {
        std::regex selectRegex (R"(^.*select\s+(.*?)\s+from\s+([^\s]+)\s+where\s+(.*)$)");
        std::regex deleteRegex (R"(^.*delete\s+from\s+([^\s]+)\s+where\s+(.*)$)");
        std::smatch match;
        std::regex literalRegexReplace("(\'.*?\')");
        std::string queryEscaped = std::regex_replace(query, literalRegexReplace, R"(""*"")");
        std::string conditionsString;
        clear();

        if (std::regex_search(queryEscaped, match, selectRegex)) {
            command = DBCommands::selectCommand;
            std::string fieldsString = match.str(1);
            parseFields(fieldsString);
            table = match.str(2);
            conditionsString = match.str(3);
        } else if (std::regex_search(queryEscaped, match, deleteRegex)) {
            command = DBCommands::deleteCommand;
            table = match.str(1);
            conditionsString = match.str(2);
        } else {
            throw std::invalid_argument("Malformed query: " + query);
        }

        helpers::StringHelper::trimSpaces(table);
        helpers::StringHelper::removeSpaces(conditionsString);
        std::regex literalRegex("(\'.*?\')");
        std::regex escapeLiterals (R"(""\*"")");
        for (std::sregex_iterator it{query.begin(), query.end(), literalRegex}, end{}; it != end; ++it) {
            conditionsString = std::regex_replace(conditionsString, escapeLiterals, it->str(1), std::regex_constants::format_first_only);
        }
        parseCondition(conditionsString);
    }

    std::string DB::prepareParam(const std::string& param) {
        std::stringstream quoted;
        quoted << std::quoted(param, '\'', '\\');
        return quoted.str();
    }

    void DB::execute(const std::string &query, const std::vector<std::string> &arguments) {

        if (query.find('\'') != std::string::npos) {
            throw std::invalid_argument("Malformed query: " + query);
        }

        std::string parametrizedQuery = query;
        std::regex placeHolders(R"(\?)");

        for (const auto& argument : arguments) {
            parametrizedQuery = std::regex_replace(parametrizedQuery, placeHolders, prepareParam(argument), std::regex_constants::format_first_only);
        }
        execute(parametrizedQuery);
    }

    void DB::execute(const std::string& query) {
        parse(query);
        if (table == database::Invoice::tableName) {
            lastResponse = database::invoiceTable.executeCommand(command, condition, fields);
        } else if (table == database::InvoiceItem::tableName) {
            lastResponse = database::invoiceItemTable.executeCommand(command, condition, fields);
        } else if (table == database::OverdueInvoice::tableName) {
            lastResponse = database::overdueInvoiceTable.executeCommand(command, condition, fields);
        } else if (table == database::Users::tableName) {
            lastResponse = database::usersTable.executeCommand(command, condition, fields);
        } else {
            throw std::invalid_argument("Unknown table name: " + table);
        }
    }
    std::vector<std::map<std::string, std::string>> DB::getLastResponse() {
        return lastResponse;
    }

    void DB::parseFields(std::string &fieldsString) {
        helpers::StringHelper::removeSpaces(fieldsString);
        helpers::StringHelper::split(fieldsString, fields, ',');
    }

    void DB::parseCondition(std::string &conditionString) {
        helpers::StringHelper::split(conditionString, condition, '=');
        if(!condition.empty() && condition.size() != 2) {
            throw std::invalid_argument("DB::parseCondition Malformed condition: " + conditionString);
        }
        helpers::StringHelper::trim(condition[1], "\'");
    }

    void DB::clear() {
        command = DBCommands::undefinedCommand;
        table = "";
        fields.clear();
        condition.clear();
    }
} // database
