#pragma once
#include <string>

namespace protocol
{
    static constexpr char delimiter             = 0x7C; // '|'
    static constexpr char terminateChar         = 0x4; //EOT End of transmission
    static constexpr char responseError         = 0x30; // 0
    static constexpr char responseSuccess       = 0x31; // 1
    static constexpr char responseCorruptedData = 0x32; // 2
    static constexpr char authorized            = 0x33; // 3
    static constexpr char notAuthorized         = 0x34; // 4
    static constexpr char disconnected          = 0x35; // 5
    static constexpr char connected             = 0x36; // 6
    static constexpr char licenceConfirmed      = 0x37; // 7
    static constexpr char licenceNotConfirmed   = 0x38; // 8


    class Agreements {
    public:
        static void validateResponseCode(const std::string& responseCode);
        static void validateResponseCode(char responseCode);
        static void validateAuthorizedCode(char authorizedCode);
        static void validateAuthorizedCode(const std::string& authorizedCode);
        static void validateLicenceStatus(const std::string& licenceStatus);
        static void validateLicenceStatus(char code);
        static void validateConnectionStatus(const std::string& connectionStatus);
        static void validateConnectionStatus(char code);
    };
}
