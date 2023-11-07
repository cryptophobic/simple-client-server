#include "sockets/TcpClientSocket.hpp"
#include <cstring>
#include <iostream>

int main() {

    TcpClientSocket client(std::string("localhost"), std::string("5001"));

    std::string message;
    do {

        if (!client.isConnected()) {
            client.openConnection();
            std::cout << "Go ahead, say something, server awaits" << std::endl;
        }

        std::cout << "server: " << message << std::endl << "client: ";
        if (message == "bye") {
            break;
        }
        std::cin >> message;

        client.safeSendData(message);
    } while (client.safeReceiveData(message) > 0);
    client.closeConnections();

    return 0;
}
