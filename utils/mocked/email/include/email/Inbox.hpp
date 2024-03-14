#pragma once
#include <string>
#include <fstream>


namespace email {

    class Inbox {
    public:
        static void send(const std::string& userId, const std::string& body);
        static void receive(const std::string& userId, std::string& body);
    };

} // email