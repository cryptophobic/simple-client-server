#pragma once
#include <string>

namespace security {

    class Sha2Wrapper {
    public:
        void hashString(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len);
        void hashString(const std::string& str, std::string& outHash);
        bool verify(const std::string& str, const std::string& hash);
    protected:
        void handleErrors();
    };

} // security