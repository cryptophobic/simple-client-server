cmake_minimum_required(VERSION 3.26)
project(client_server)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

IF (WIN32)
    set(ALL_LIBS ws2_32)
ENDIF()

add_executable(InvoiceMasterClient InvoiceMasterClient.cpp
        InvoiceMasterClient/ServiceConnector/Request.cpp
        InvoiceMasterClient/ServiceConnector/Request.hpp
        InvoiceMasterClient/ServiceConnector/Response.cpp
        InvoiceMasterClient/ServiceConnector/Response.hpp
        InvoiceMasterClient/ServiceConnector/ServiceConnector.cpp
        InvoiceMasterClient/ServiceConnector/ServiceConnector.hpp
        InvoiceMasterClient/views/AdminAccess.cpp
        InvoiceMasterClient/views/AdminAccess.hpp
        InvoiceMasterClient/views/Login.cpp
        InvoiceMasterClient/views/Login.hpp
        InvoiceMasterClient/views/MainMenu.cpp
        InvoiceMasterClient/views/MainMenu.hpp
        InvoiceMasterClient/Application.cpp
        InvoiceMasterClient/Application.hpp
        InvoiceMasterClient/Controller.cpp
        InvoiceMasterClient/Controller.hpp
        InvoiceMasterClient/View.cpp
        InvoiceMasterClient/View.hpp
        utils/transport/TcpSocket.hpp
        utils/transport/TcpClientSocket.hpp
        settings/ServiceList.hpp
        InvoiceMasterClient/views/Quit.cpp
        InvoiceMasterClient/views/Quit.hpp)

target_link_libraries(InvoiceMasterClient ${ALL_LIBS})

add_executable(InvoiceMasterServer InvoiceMasterServer.cpp
        utils/transport/TcpSocket.hpp
        utils/transport/TcpServerSocket.hpp
        settings/ServiceList.hpp
        InvoiceMasterServer/Application.hpp
        InvoiceMasterServer/Application.cpp
        InvoiceMasterServer/Service/Listener.cpp
        InvoiceMasterServer/Service/Listener.hpp
        InvoiceMasterServer/Service/Request.cpp
        InvoiceMasterServer/Service/Request.hpp
        InvoiceMasterServer/Service/Response.cpp
        InvoiceMasterServer/Service/Response.hpp
        InvoiceMasterServer/models/AuthenticationManager.cpp
        InvoiceMasterServer/models/AuthenticationManager.hpp
)

target_link_libraries(InvoiceMasterServer ${ALL_LIBS})