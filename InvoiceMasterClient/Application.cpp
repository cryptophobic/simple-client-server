//
// Created by Dmytro Uglach on 08.11.2023.
//

#include "Application.hpp"

namespace InvoiceMasterClient {
    void Application::Run() {
        connector.establishConnection();
        std::vector<std::string> message{settings::services.login.argumentsNumber, ""};

        std::cout << "Please enter your login and password separated by space" << std::endl;
        std::cout << ":> ";

        for (int i = 0; i < settings::services.login.argumentsNumber; i++) {
            std::cin >> message[i];
        }

        std::string result = connector.sendCommand(settings::services.login, message);

        std::cout << "response: " << result << std::endl;
        //connect
        //login
    }
}
