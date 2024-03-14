#pragma once
#include <string>
#include <set>

namespace licence {

    class Service {
    protected:
        static const std::set<std::string> licences;

    public:
        static void enrollLicence(const std::string& userId);
        static void confirmLicence(const std::string& userId, const std::string& key);
    };

} // licenceService