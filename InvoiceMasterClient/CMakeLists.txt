cmake_minimum_required(VERSION 3.26)
project(InvoiceMasterClient)

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(clientDirectories INTERFACE)
target_compile_definitions(clientDirectories INTERFACE CLIENT_PROJECT_DIR="${PROJECT_SOURCE_DIR}/")

find_package(fmt)

file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE SRC_FILES *.cpp)

#InvoiceMasterClient
add_library(InvoiceMasterClientLib ${SRC_FILES} ${HEADER_FILES})

target_include_directories(InvoiceMasterClientLib
        PUBLIC ../

        PUBLIC ../utils/transport/include
        PUBLIC ../utils/userInputOutput
        PUBLIC ../utils/protocol/include
        PUBLIC ../utils/helpers/include
        PUBLIC ../utils/mocked/email/include
        PUBLIC ../utils/licence/include

        PUBLIC ../config/include
)
target_link_libraries(InvoiceMasterClientLib TransportLib UserInputOutputLib ProtocolLib HelpersLib EmailLib LicenceLib clientDirectories fmt::fmt)
#end of InvoiceMasterClient