#pragma once

#include <set>

namespace settings {

    constexpr char delimiter = '|';
    constexpr char terminateChar = 0x4; //EOT End of transmission
    constexpr char hostName[10] = "localhost";
    constexpr char port[10] = "5001";

    constexpr char requestLogin = 'l';
    constexpr char adminAccess = 'a';
    constexpr char mainMenu = 'm';
    constexpr char disconnect = 'd';
    const std::set<const char>commands {requestLogin, adminAccess, disconnect};

    constexpr char responseError = '1';
    constexpr char responseSuccess = '0';
    constexpr char responseCorruptedData = '2';
    const std::set<const char>responseCodes {responseError, responseSuccess};

    constexpr char authorized = '1';
    constexpr char notAuthorized = '0';
    constexpr char disconnected = '3';
    const std::set<const char>authorizedCodes {authorized, notAuthorized, disconnected};


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
        const ServiceSignature admin;
        const ServiceSignature login;
        const ServiceSignature mainMenu;
        const ServiceSignature quit;
    };

    constexpr ServiceList services {
        .admin = {adminAccess, 1},
        .login = {requestLogin, 2},
        .mainMenu = {mainMenu, 0},
        .quit = {disconnect, 0},
    };
}
