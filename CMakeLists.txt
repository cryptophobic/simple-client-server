cmake_minimum_required(VERSION 3.26)
project(InvoiceMaster)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(config/include)

add_subdirectory(utils)
add_subdirectory(InvoiceMasterServer)
add_subdirectory(InvoiceMasterClient)

add_executable(ClientApp InvoiceMasterClient.cpp)
add_executable(ServerApp InvoiceMasterServer.cpp)

target_link_libraries(ClientApp InvoiceMasterClientLib)
target_link_libraries(ServerApp InvoiceMasterServerLib)
