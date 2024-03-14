#pragma once
#include <map>
#include <set>
#include <string>
#include <memory>

namespace database {

    class Entity {
    protected:
        std::map<std::string, std::string> record;
        bool isFieldExists(const std::string&);
    public:
        std::string id;
        static const std::string tableName;
        Entity(const std::string& newId = "") : id(newId)
        {};
        virtual std::set<std::string> getFields() = 0;
        void setField(const std::string& key,const std::string& value);
        virtual void setFields(const std::map<std::string, std::string>& values);
        std::map<std::string, std::string> getRecord();
        std::string toString();
        std::string getField(const std::string& key);
        virtual void saveRecord(const std::string& id) = 0;
        virtual void saveRecord() = 0;
    };

} // database
