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
        utils/transport/TcpSocket.hpp
        utils/transport/TcpClientSocket.hpp
        InvoiceMasterClient/Application.cpp
        InvoiceMasterClient/Application.hpp
        InvoiceMasterClient/ServiceConnector/ServiceConnector.cpp
        InvoiceMasterClient/ServiceConnector/ServiceConnector.hpp
        settings/ServiceList.hpp
        InvoiceMasterClient/ServiceConnector/Request.cpp
        InvoiceMasterClient/ServiceConnector/Request.hpp
        InvoiceMasterClient/ServiceConnector/Response.cpp
        InvoiceMasterClient/ServiceConnector/Response.hpp)

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
        InvoiceMasterServer/model/AuthenticationManager.cpp
        InvoiceMasterServer/model/AuthenticationManager.hpp)

target_link_libraries(InvoiceMasterServer ${ALL_LIBS})