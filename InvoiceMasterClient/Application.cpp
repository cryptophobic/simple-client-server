//
// Created by Dmytro Uglach on 08.11.2023.
//

#include "Application.hpp"

namespace InvoiceMasterClient {
    void Application::run()
    {
        connector.establishConnection();
        while(!quit && connector.isConnected()) {
            switch (menu()) {
                case '1':
                    while (!isAuthorised) {
                        std::unique_ptr<Response> response = controller(settings::services.login);
                        isAuthorised = response->parsed->responseCode == settings::responseSuccess;
                    }
                    break;
                case '2':
                    quit = true;
                    break;
                case '3':
                    std::unique_ptr<Response> response = controller(settings::services.admin);
                    if (response->parsed->responseCode == settings::responseSuccess) {
                        std::cout << "Server has been shut down" << std::endl;
                        quit = true;
                    }
                    break;
            }
        }
        std::cout << "Bye!" << std::endl;
        connector.closeConnection();
    }

    //TODO: going to move to controller component
    std::unique_ptr<Response> Application::controller(settings::ServiceSignature command)
    {
        std::vector<std::string> arguments{};
        switch (command.code) {
            case settings::services.login.code:
                arguments = login();
                break;
            case settings::services.admin.code:
                arguments.emplace_back("quit");
            default:
                break;
        }
        return connector.sendCommand(std::make_unique<Request>(command, arguments));
    }

    char Application::menu()
    {
        char choice;
        if (!isAuthorised) {
            std::cout << "1. Authorise" << std::endl;
        }
        std::cout << "2. Quit" << std::endl << "3. Quit server" << std::endl;
        std::cout << ":> ";
        std::cin >> choice;

        return choice;
    }

    //TODO: going to move to view component
    std::vector<std::string> Application::login()
    {
        std::vector<std::string> arguments{settings::services.login.argumentsNumber, ""};

        std::cout << "Please enter your login and password separated by space" << std::endl;
        std::cout << ":> ";

        for (auto & argument: arguments) {
            std::cin >> argument;
        }

        return arguments;
    }
}
