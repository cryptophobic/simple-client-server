#pragma once

#include <set>

namespace settings {

    constexpr char delimiter = '|';
    constexpr char terminateChar = 0x4; //EOT End of transmission
    constexpr char hostName[10] = "localhost";
    constexpr char port[10] = "5001";

    constexpr char requestLogin = 'l';
    constexpr char adminAccess = 'a';
    const std::set<const char>commands {requestLogin, adminAccess};

    constexpr char responseError = '1';
    constexpr char responseSuccess = '0';
    constexpr char responseCorruptedData = '2';
    const std::set<const char>responseCodes {responseError, responseSuccess};


    struct ServiceSignature {
        const char code;
        const int argumentsNumber;
    };

    struct ServiceList {
        //ServiceSignature documentSearch;
        //ServiceSignature documentUpload;
        //ServiceSignature licenceActivation;
        //ServiceSignature registration;
        //ServiceSignature softwareUpdate;
        const ServiceSignature login;
        const ServiceSignature admin;
    };

    constexpr ServiceList services {
        .login = {requestLogin, 2},
        .admin = {adminAccess, 1}
    };
}
