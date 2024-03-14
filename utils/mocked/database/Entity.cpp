#include "database/Entity.hpp"
#include "fmt/core.h"

namespace database {

    bool Entity::isFieldExists(const std::string& field)
    {
        return getFields().contains(field);
    }

    std::string Entity::getField(const std::string& key)
    {
        if (!isFieldExists(key)) {
            throw std::invalid_argument("The key doesn't exist: " + key);
        }
        return record[key];
    }

    void Entity::setField(const std::string& key, const std::string& value)
    {
        if (!isFieldExists(key)) {
            throw std::invalid_argument("The key doesn't exist: " + key);
        }
        record[key] = value;
    }

    void Entity::setFields(const std::map<std::string, std::string>& values) {
        for (auto const& [key, value] : values) {
            setField(key, value);
        }
    }

    std::map<std::string, std::string> Entity::getRecord() {
        return record;
    }

    std::string Entity::toString() {
        std::string result;
        for (const auto& field: getFields()) {
            result += fmt::format("{0}: {1}; ", field, record[field]);
        }
        return result;
    }
} // database
