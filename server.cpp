#include "sockets/TcpServerSocket.hpp"
#include <iostream>
#include <cstring>

int main() {

    TcpServerSocket server("localhost", "5001");
    bool quit = false;

    do {
        if (!server.isConnected()) {
            server.acceptConnection();
        }
        char message[100] = "";
        if (server.safeReceiveData(message, 100)) {
            quit = strcmp(message, "quit") == 0;
            std::cout << message << std::endl;
            strcpy(message, "Hello from server!");
            server.safeSendData(message, strlen(message));
        }
    } while (!quit);

    server.closeConnections();
    return 0;
}
