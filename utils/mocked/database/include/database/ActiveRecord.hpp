#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <concepts>
#include <fstream>
#include <sstream>
#include "database/Entity.hpp"
#include "FileHelper.hpp"
#include "StringHelper.hpp"
#include "csv/Writer.hpp"
#include "csv/Reader.hpp"

#include <iostream>

namespace database {

    enum class DBCommands {selectCommand, deleteCommand, undefinedCommand};

    template<class T>
    requires(std::derived_from<T, Entity>)
    class ActiveRecord {
    protected:
        unsigned long lastId = 0;
        std::map<std::string, std::shared_ptr<T>> table;
    public:
        void importFromFile() {
            try {
                csv::Reader reader(std::string(DATABASE_DUMP_DIR) + std::filesystem::path::preferred_separator + T::tableName);
                auto parsed = reader.getParsed();
                for (const auto& row: parsed) {
                    auto item = std::make_shared<T>();
                    std::string id{};

                    for (const auto& [key, value] : row) {
                        if (key == "id") {
                            id = value;
                        } else {
                            item->setField(key, value);
                        }
                    }

                    if (!id.empty()) {
                        item->saveRecord(id);
                    } else {
                        item->saveRecord();
                    }
                }

            } catch (std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
                return;
            }
        }

        void exportToFile() {
            std::vector<std::map<std::string, std::string>> data;
            for (auto const& [key, entity] : table) {
                auto record = entity->getRecord();
                record["id"] = key;
                data.emplace_back(record);
            }

            csv::Writer writer(data);
            writer.save(std::string(DATABASE_DUMP_DIR) + std::filesystem::path::preferred_separator + T::tableName);
        }

        std::shared_ptr<T> getRecordById(const std::string& id) {
            return table.contains(id) ? table[id] : nullptr;
        };

        std::vector<std::shared_ptr<T>> getRecords() {
            std::vector<std::shared_ptr<T>> result{};
            for (auto const& [key, record] : table) {
                result.emplace_back(record);
            }
            return result;
        };

        std::vector<std::shared_ptr<T>> getRecordsByField(const std::string &field, const std::string &value) {
            std::vector<std::shared_ptr<T>> result{};
            for (auto const& [key, record] : table) {
                if (record->getField(field) == value) {
                    result.emplace_back(record);
                }
            }
            return result;
        };

        std::string getNewId() {
            return std::to_string(++lastId);
        }

        std::string setNewRecord(std::shared_ptr<T> record) {
            if (record->id.empty()) {
                record->id = getNewId();
                table[record->id] = record;
            }
            return record->id;
        };

        void setRecordWithId(const std::string& id, std::shared_ptr<T> record) {
            record->id = id;
            lastId = lastId < std::stoi(record->id) ? std::stoi(record->id) : lastId;
            table[record->id] = record;
        };

        void deleteRecordById(const std::string& id) {
            if (table.contains(id)) {
                table.erase(id);
            }
        };

        void deleteRecords() {
            table.clear();
        };

        void deleteRecordByField(const std::string &field, const std::string &value) {
            std::erase_if(table, [=](const auto& item) {
                auto const& [key, record] = item;
                return (record->getField(field) == value);
            });
        };

        std::vector<std::map<std::string, std::string>> executeCommand(
                DBCommands command,
                std::vector<std::string> condition,
                const std::vector<std::string>& fields) {
            std::vector<std::shared_ptr<T>> lastResponse{};
            std::vector<std::map<std::string, std::string>> response{};
            switch (command) {
                case DBCommands::selectCommand:
                    lastResponse = condition.empty()
                                     ? getRecords()
                                     : getRecordsByField(condition[0], condition[1]);
                    break;
                case DBCommands::deleteCommand:
                    if (condition.empty()) {
                        deleteRecords();
                    } else {
                        deleteRecordByField(condition[0], condition[1]);
                    }
                    break;
                default:
                    throw std::invalid_argument("Undefined SQL command");

            }
            for (const auto& row : lastResponse) {
                std::map<std::string, std::string> filteredRow{};
                for (const auto& field: fields) {
                    filteredRow[field] = row->getField(field);
                }
                response.emplace_back(filteredRow);
            }
            return response;
        };
    };
} // database
