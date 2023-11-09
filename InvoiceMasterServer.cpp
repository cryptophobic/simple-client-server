#include "utils/transport/TcpServerSocket.hpp"
#include <iostream>
#include <string>

int main() {

    TcpServerSocket server("localhost", "5001");
    bool quit = false;

    do {
        if (!server.isConnected()) {
            server.acceptConnection();
        }
        std::string message;
        if (server.safeReceiveData(message)) {
            server.safeSendData("OK");
            quit = message == "quit";
            std::cout << message << std::endl;
            if (quit) {
                message = "bye";
            } else {
                message += " response!";
            }
            server.safeSendData(message);
        }
    } while (!quit);

    server.closeConnections();
    return 0;
}
