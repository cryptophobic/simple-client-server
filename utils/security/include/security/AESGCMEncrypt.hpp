#pragma once
#include <string>
#include <vector>
#include <openssl/types.h>

namespace security {

    constexpr int keyLength = 32;
    constexpr int ivLength = 16;
    constexpr int authenticationTagLength = 16;

    class AESGCMEncrypt {
    protected:
        void handleErrors();
        void produceIVAndKey(const std::string &password, const unsigned char* salt, unsigned char *key, unsigned char *iv);
        void init();
        void cleanup();
        EVP_CIPHER_CTX *ctx = nullptr;
    public:
        void encrypt(
                const std::string& password,
                const std::vector<unsigned char>& plainText,
                std::vector<unsigned char>& salt,
                std::vector<unsigned char>& outputBuffer);
        void decrypt(
                const std::string& password,
                const std::vector<unsigned char>& salt,
                const std::vector<unsigned char>& encryptedBuffer,
                std::vector<unsigned char>& plainString);
    };

} // security
