#include "security/AESGCMEncrypt.hpp"
#include "security/config.hpp"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/core_names.h>
#include <openssl/rand.h>
#include <vector>

namespace security {

    void AESGCMEncrypt::handleErrors() {
        ERR_print_errors_fp(stderr);
        cleanup();
        throw std::invalid_argument("Unexpected error");
    }

    void AESGCMEncrypt::init() {
        if (ctx == nullptr) {
            if(!(ctx = EVP_CIPHER_CTX_new())) {
                handleErrors();
            }
        }
    }

    void AESGCMEncrypt::cleanup() {
        if (ctx != nullptr) {
            EVP_CIPHER_CTX_free(ctx);
            ctx = nullptr;
        }
    }

    void AESGCMEncrypt::produceIVAndKey(const std::string &password, const unsigned char* salt, unsigned char *key, unsigned char *iv) {

        unsigned char derived[keyLength + ivLength]; // 32 bytes for both key and IV

        // Derive 48 bytes
        if(!PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), password.size(), salt, saltLength,1000,sizeof(derived), derived)) {
            handleErrors();
        }
        // Use the first 16 bytes as the key
        memcpy(key, derived, keyLength);
        // Use the remaining 32 bytes as the IV
        memcpy(iv, derived + keyLength, ivLength);
    }

    void AESGCMEncrypt::encrypt(const std::string& password,
                                const std::vector<unsigned char>& plainText,
                                std::vector<unsigned char>& salt,
                                std::vector<unsigned char>& outputBuffer) {

        unsigned char key[keyLength], iv[ivLength], saltArray[saltLength], retrievedTag[authenticationTagLength];
        EVP_CIPHER *cipher;
        size_t gcmIVLength = sizeof(iv);
        auto* cipherText = new unsigned char [plainText.size() + AES_BLOCK_SIZE];
        int tmpLength = 0, cipherTextLength = 0;
        OSSL_PARAM params[2] {OSSL_PARAM_END, OSSL_PARAM_END};

        init();

        RAND_bytes(saltArray, saltLength);
        produceIVAndKey(password, saltArray, key, iv);

        /* Fetch the cipher implementation */
        if ((cipher = EVP_CIPHER_fetch(nullptr, "AES-256-GCM", nullptr)) == nullptr) {
            handleErrors();
        }

        /* Set IV length if default 96 bits is not appropriate */
        params[0] = OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_AEAD_IVLEN,&gcmIVLength);

        /*
         * Initialise an encrypt operation with the cipher/mode, key, IV and
         * IV length parameter.
         * For demonstration purposes the IV is being set here. In a compliant
         * application the IV would be generated internally so the iv passed in
         * would be nullptr.
         */
        if (!EVP_EncryptInit_ex2(ctx, cipher, key, iv, params)) {
            handleErrors();
        }

        /*
         * Provide the message to be encrypted, and obtain the encrypted output.
         * EVP_EncryptUpdate can be called multiple times if necessary
         */
        if(1 != EVP_EncryptUpdate(ctx, cipherText, &tmpLength, &plainText[0], plainText.size())) {
            handleErrors();
        }
        cipherTextLength = tmpLength;

        /*
         * Finalise the encryption. Normally ciphertext bytes may be written at
         * this stage, but this does not occur in GCM mode
         */
        if(1 != EVP_EncryptFinal_ex(ctx, cipherText + tmpLength, &tmpLength)) {
            handleErrors();
        }
        cipherTextLength += tmpLength;

        /* Get the tag */
        params[0] = OSSL_PARAM_construct_octet_string(
                OSSL_CIPHER_PARAM_AEAD_TAG,
                retrievedTag,
                authenticationTagLength);

        if (!EVP_CIPHER_CTX_get_params(ctx, params)) {
            handleErrors();
        }

        outputBuffer.clear();
        outputBuffer.insert(outputBuffer.end(), retrievedTag, retrievedTag + authenticationTagLength);
        outputBuffer.insert(outputBuffer.end(), cipherText, cipherText + cipherTextLength);

        salt.clear();
        salt.insert(salt.end(), saltArray, saltArray + saltLength);
        cleanup();
    }

    void AESGCMEncrypt::decrypt(const std::string& password,
                                const std::vector<unsigned char>& salt,
                                const std::vector<unsigned char>& encryptedBuffer,
                                std::vector<unsigned char>& outputBuffer) {
        unsigned char key[keyLength], iv[ivLength];
        EVP_CIPHER *cipher;
        size_t gcmIVLength = sizeof(iv);
        OSSL_PARAM params[2] = {OSSL_PARAM_END, OSSL_PARAM_END};
        std::vector<unsigned char>tag (encryptedBuffer.begin(), encryptedBuffer.begin() + authenticationTagLength);
        std::vector<unsigned char>cipherText (encryptedBuffer.begin() + authenticationTagLength, encryptedBuffer.end());
        /* Buffer for the decrypted text */
        auto* plainText = new unsigned char[cipherText.size() + AES_BLOCK_SIZE];
        int tmpLength = 0, plainTextLength = 0;

        init();

        produceIVAndKey(password, &salt[0], key, iv);

        /* Fetch the cipher implementation */
        if ((cipher = EVP_CIPHER_fetch(nullptr, "AES-256-GCM", nullptr)) == nullptr) {
            handleErrors();
        }

        /* Set IV length if default 96 bits is not appropriate */
        params[0] = OSSL_PARAM_construct_size_t(OSSL_CIPHER_PARAM_AEAD_IVLEN,&gcmIVLength);

        /*
         * Initialise an encrypt operation with the cipher/mode, key, IV and
         * IV length parameter.
         */
        if (!EVP_DecryptInit_ex2(ctx, cipher, key, iv, params)) {
            handleErrors();
        }

        /*
         * Provide the message to be decrypted, and obtain the plaintext output.
         * EVP_DecryptUpdate can be called multiple times if necessary
         */
        if(!EVP_DecryptUpdate(ctx, plainText, &tmpLength, &cipherText[0], cipherText.size())) {
            handleErrors();
        }
        plainTextLength = tmpLength;

        params[0] = OSSL_PARAM_construct_octet_string(OSSL_CIPHER_PARAM_AEAD_TAG,(void*)&tag[0], tag.size());

        if(1 != EVP_CIPHER_CTX_set_params(ctx, params)) {
            handleErrors();
        }
        /*
         * Finalise the decryption. A positive return value indicates success,
         * anything else is a failure - the plaintext is not trustworthy.
         */
        if(!EVP_DecryptFinal_ex(ctx, plainText + tmpLength, &tmpLength)) {
            handleErrors();
        }

        plainTextLength += tmpLength;
        outputBuffer.clear();
        outputBuffer.insert(outputBuffer.end(), plainText, plainText + plainTextLength);

        cleanup();
    }
} // security