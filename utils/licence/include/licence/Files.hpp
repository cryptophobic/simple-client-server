#pragma once
#include <string>

namespace licence {

    class Files {
    public:
        static void storeClientKey(const std::string& userId);
        static void readClientKey(std::string& clientKey);
    };

} // licence