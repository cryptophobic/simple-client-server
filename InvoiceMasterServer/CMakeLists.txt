cmake_minimum_required(VERSION 3.26)
project(InvoiceMasterServer)

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(serverDirectories INTERFACE)
target_compile_definitions(serverDirectories
        INTERFACE SERVER_PROJECT_DIR="${PROJECT_SOURCE_DIR}/"
)

#xerces
IF(DEFINED ENV{INVOICE_MASTER_DEVELOPMENT})
    include(FindXercesC)
    include_directories(${XercesC_INCLUDE_DIRS})
ELSE()
    find_library(xerces-c_location NAMES libxerces-c.so)
    add_library(xerces-c SHARED IMPORTED)
    set_target_properties(xerces-c PROPERTIES IMPORTED_LOCATION ${xerces-c_location})
ENDIF()
#end of xerces

find_package(fmt)

file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE SRC_FILES *.cpp)

#InvoiceMasterServer
add_library(InvoiceMasterServerLib ${SRC_FILES} ${HEADER_FILES})

target_include_directories(InvoiceMasterServerLib
        PUBLIC ../

        PUBLIC ../utils/mocked/database/include
        PUBLIC ../utils/mocked/email/include
        PUBLIC ../utils/mocked/csv/include

        PUBLIC ../utils/protocol/include
        PUBLIC ../utils/transport/include
        PUBLIC ../utils/protocol/include
        PUBLIC ../utils/security/include
        PUBLIC ../utils/licence/include

        PUBLIC ../config/include
)
target_link_libraries(InvoiceMasterServerLib
        CsvLib TransportLib ProtocolLib DbConnectionLib SecurityLib EmailLib LicenceLib serverDirectories fmt::fmt
)
IF(DEFINED ENV{INVOICE_MASTER_DEVELOPMENT})
    target_link_libraries(InvoiceMasterServerLib ${XercesC_LIBRARIES})
ELSE()
    target_link_libraries(InvoiceMasterServerLib xerces-c)
ENDIF()
#end of InvoiceMasterServer