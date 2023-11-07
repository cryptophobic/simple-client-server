cmake_minimum_required(VERSION 3.26)
project(client_server)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

IF (WIN32)
    set(ALL_LIBS ws2_32)
ENDIF()

add_executable(client client.cpp
        sockets/TcpSocket.hpp
        sockets/TcpClientSocket.hpp)

target_link_libraries(client ${ALL_LIBS})

add_executable(server server.cpp
        sockets/TcpSocket.hpp
        sockets/TcpServerSocket.hpp)

target_link_libraries(server ${ALL_LIBS})