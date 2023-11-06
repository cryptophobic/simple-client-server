#include "sockets/TcpClientSocket.hpp"
#include <cstring>
#include <iostream>

int main() {

    TcpClientSocket client(std::string("localhost"), std::string("5001"));
    for (auto i = 2; i > 0; i--) {
        if (!client.isConnected()) {
            client.openConnection();
        }

        char message[100] = "quit";
        client.safeSendData(message, strlen(message));
        if (client.safeReceiveData(message, 100) > 0) {
            std::cout << message << std::endl;
        }
    }
    client.closeConnections();

    return 0;
}
