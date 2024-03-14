#pragma once
#include <set>
#include <map>
#include <string>
#include <vector>

namespace protocol {
    constexpr static char requestLogin         = 0x69;
    constexpr static char requestLogout        = 0x6A;
    constexpr static char requestSignUp        = 0x6B;
    constexpr static char requestAdminAccess   = 0x6C;
    constexpr static char requestMainMenu      = 0x6D;
    constexpr static char requestDisconnect    = 0x6E;
    constexpr static char requestInvoice       = 0x6F;
    constexpr static char requestInvoiceList   = 0x70;
    constexpr static char requestDocuments     = 0x71;

    constexpr static char requestLicence       = 0x72;
    constexpr static char requestSetLicence    = 0x73;
    constexpr static char requestEnrollLicence = 0x74;
    constexpr static char requestVerifyLicence = 0x75;

    constexpr static char invoiceNew         = 0x10;
    constexpr static char invoiceDelete      = 0x11;
    constexpr static char invoiceGet         = 0x12;
    constexpr static char invoiceNewLine     = 0x13;
    constexpr static char invoiceSave        = 0x14;
    constexpr static char invoiceSaveOverdue = 0x15;
    constexpr static char invoiceCancel      = 0x16;
    constexpr static char invoiceImport      = 0x17;
    constexpr static char documentDelete     = 0x18;
    constexpr static char documentSave       = 0x19;
    constexpr static char documentLoad       = 0x1A;

    const std::set<const char>commands {
        requestInvoiceList,
        requestInvoice,
        requestLogin,
        requestAdminAccess,
        requestDisconnect,
        requestLogout,
        requestSetLicence,
        requestEnrollLicence,
        requestVerifyLicence,
        requestSignUp,
        requestDocuments
    };

    const std::map<char, int> argumentsNumber{
        {requestLogin,         2},
        {requestSignUp,        2},
        {requestAdminAccess,   1},
        {requestMainMenu,      0},
        {requestDisconnect,    0},
        {requestLogout,        0},
        {requestInvoiceList,   0},
        {requestSetLicence,    4},
        {requestEnrollLicence, 1},
        {requestVerifyLicence, 1},
    };

    class ApiAccess {
    public:
        static void validateCommand(const std::string& command);
        static void validateCommand(char code);
        static void validateArguments(char command, const std::vector<std::string>& arguments);
    };

}
