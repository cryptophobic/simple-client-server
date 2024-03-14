#include "security/Argon2Wrapper.hpp"
#include "security/config.hpp"
#include "argon2.h"

namespace security {

    void Argon2Wrapper::hashString(const std::string& str, const std::string& salt, uint8_t** hash, uint32_t& length) {
        (*hash) = new uint8_t[hashLength];
        length = hashLength;

        argon2id_hash_raw(
                timeCost,
                memoryCost,
                threadsNumber,
                str.c_str(),
                str.length(),
                salt.c_str(),
                salt.length(),
                *hash,
                hashLength);
    }

    void Argon2Wrapper::hashString(const std::string& str, const std::string& salt, std::string& outHash) {
        uint8_t* hash = nullptr;
        uint32_t length;
        hashString(str, salt, &hash, length);
        outHash = {hash, hash + length};
    }

    bool Argon2Wrapper::verify(const std::string& str, const std::string& salt, const std::string& hashToCompare) {
        std::string hash;
        hashString(str, salt, hash);
        auto result = false;
        if (auto length = hash.length();length == hashToCompare.length()) {

            for (int i = 0; i < length; i++) {
                result |= (hash[i] != hashToCompare[i]);
            }
            result = !result;
        }
        return result;
    }
} // security
