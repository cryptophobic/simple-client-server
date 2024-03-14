#include "security/Sha2Wrapper.hpp"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <memory>

namespace security {

    void Sha2Wrapper::handleErrors() {
        auto errorCode = ERR_get_error();
        if (errorCode) {
            throw std::runtime_error(ERR_error_string(errorCode, nullptr));
        }
    }

    void Sha2Wrapper::hashString(
            const unsigned char *message,
            size_t message_len,
            unsigned char **digest,
            unsigned int *digest_len) {

        auto mdCtx = std::unique_ptr<EVP_MD_CTX, decltype(&::EVP_MD_CTX_free)>(EVP_MD_CTX_new(), ::EVP_MD_CTX_free);

        if(mdCtx == nullptr) {
            handleErrors();
        }

        if(1 != EVP_DigestInit_ex(mdCtx.get(), EVP_sha512(), nullptr)) {
            handleErrors();
        }

        if(1 != EVP_DigestUpdate(mdCtx.get(), message, message_len)) {
            handleErrors();
        }

        if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha512()))) == nullptr) {
            handleErrors();
        }

        if(1 != EVP_DigestFinal_ex(mdCtx.get(), *digest, digest_len)) {
            handleErrors();
        }
    }

    void Sha2Wrapper::hashString(const std::string &str, std::string &outHash) {
        unsigned char* res;
        unsigned int length;
        auto* message = new unsigned char[str.length() + 1];
        std::copy(str.data(), str.data() + str.length() + 1, message);
        hashString(message, str.length(), &res, &length);
        outHash = {res, res + length};
    }

    bool Sha2Wrapper::verify(const std::string &str, const std::string &hashToCompare) {
        std::string hash;

        hashString(str, hash);
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