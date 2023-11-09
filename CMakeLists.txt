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
        InvoiceMasterClient/ServiceConnector.cpp
        InvoiceMasterClient/ServiceConnector.hpp
        settings/ServiceList.hpp)

target_link_libraries(InvoiceMasterClient ${ALL_LIBS})

add_executable(InvoiceMasterServer InvoiceMasterServer.cpp
        utils/transport/TcpSocket.hpp
        utils/transport/TcpServerSocket.hpp)

target_link_libraries(server ${ALL_LIBS})