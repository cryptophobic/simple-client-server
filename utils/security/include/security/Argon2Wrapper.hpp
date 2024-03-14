#pragma once
#include <string>
#include <vector>

namespace security {

    class Argon2Wrapper {
    public:
        void hashString(const std::string& str, const std::string& salt, uint8_t** hash, uint32_t& length);
        void hashString(const std::string& str, const std::string& salt, std::string& outHash);
        bool verify(const std::string& str, const std::string& salt, const std::string& hash);
    };

} // security