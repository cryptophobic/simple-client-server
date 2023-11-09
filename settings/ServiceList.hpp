#pragma once

namespace settings {

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
    };

    constexpr ServiceList services {
        .login = {'1', 2}
    };

    constexpr char delimiter = '|';
    constexpr char terminateChar = 0x4; //EOT End of transmission
    constexpr char hostName[10] = "localhost";
    constexpr char port[10] = "5001";
}