cmake_minimum_required(VERSION 3.26)
project(utils)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt)

IF(DEFINED ENV{INVOICE_MASTER_DEVELOPMENT})
    include_directories(/usr/local/include)
ENDIF()

#argon2
find_library(argon2_location NAMES libargon2.a)
add_library(argon2 STATIC IMPORTED)
set_target_properties(argon2 PROPERTIES IMPORTED_LOCATION ${argon2_location})
#end of argon2

#openSSL
include(FindOpenSSL)
include_directories(${OPENSSL_INCLUDE_DIR})
#end of openSSL

add_library(commonDirectories INTERFACE)
target_compile_definitions(commonDirectories
        INTERFACE CERTIFICATE_DIR="${PROJECT_SOURCE_DIR}/mocked/cert"
        MAILBOX_DIR="${PROJECT_SOURCE_DIR}/mocked/email/mailbox"
        LICENCE_PATH="${PROJECT_SOURCE_DIR}/utils/licence/files/licence"
        DATABASE_DUMP_DIR="${PROJECT_SOURCE_DIR}/mocked/database/dump"
)

#DbConnectionLib

file(GLOB_RECURSE DATABASE_SRC_FILES mocked/database/*.cpp)
file(GLOB_RECURSE DATABASE_HEADER_FILES mocked/database/*.hpp)

add_library(DbConnectionLib ${DATABASE_SRC_FILES} ${DATABASE_FILES})

target_include_directories(DbConnectionLib
        PUBLIC mocked/database/include
        PUBLIC helpers/include
        PUBLIC mocked/csv/include
)

target_link_libraries(DbConnectionLib HelpersLib commonDirectories)
#end of DbConnectionLib


#HelpersLib
file(GLOB_RECURSE HELPERS_FILES helpers/*.cpp helpers/*.hpp)

add_library(HelpersLib ${HELPERS_FILES})

target_include_directories(HelpersLib
        PUBLIC helpers/include
        PUBLIC ${OPENSSL_INCLUDE_DIR}
)
target_link_libraries(HelpersLib PUBLIC ${OPENSSL_LIBRARIES})

#end of HelpersLib

#CsvLib
file(GLOB_RECURSE CSV_FILES mocked/csv/*.cpp mocked/csv/*.hpp)

add_library(CsvLib ${CSV_FILES})

target_include_directories(CsvLib
        PUBLIC mocked/csv/include
        PUBLIC helpers/include
)

target_link_libraries(CsvLib HelpersLib)
#end of CsvLib

#EmailLib
file(GLOB_RECURSE EMAIL_FILES mocked/email/*.cpp mocked/email/*.hpp)
add_library(EmailLib ${EMAIL_FILES})

target_link_libraries(EmailLib HelpersLib commonDirectories)
target_include_directories(EmailLib PUBLIC mocked/email/include)
#end of EmailLib

#SecurityLib
file(GLOB_RECURSE SECURITY_FILES security/*.cpp security/*.hpp)

add_library(SecurityLib ${SECURITY_FILES})

target_link_libraries(SecurityLib PUBLIC argon2 ${OPENSSL_LIBRARIES})
target_include_directories(SecurityLib
        PUBLIC security/include
        PUBLIC ${OPENSSL_INCLUDE_DIR}
)
#end of SecurityLib

#LicenceServiceLib
file(GLOB_RECURSE LICENCE_FILES licence/*.cpp licence/*.hpp)

add_library(LicenceLib ${LICENCE_FILES})

target_link_libraries(LicenceLib HelpersLib SecurityLib DbConnectionLib ProtocolLib fmt::fmt-header-only commonDirectories)
target_include_directories(LicenceLib
        PUBLIC licence/include
        PUBLIC helpers/include
        PUBLIC mocked/email/include
        PUBLIC mocked/database/include
)
#end of LicenceServiceLib

#TransportLib
IF (WIN32)
    SET(ALL_LIBS ws2_32)
ENDIF()

file(GLOB_RECURSE TRANSPORT_FILES transport/*.cpp transport/*.hpp)

add_library(TransportLib ${TRANSPORT_FILES})

target_link_libraries(TransportLib PUBLIC ${OPENSSL_LIBRARIES} ${ALL_LIBS} commonDirectories)
target_include_directories(TransportLib
        PUBLIC transport/include
        PUBLIC ${OPENSSL_INCLUDE_DIR}
)
#end of TransportLib

#ProtocolLib
file(GLOB_RECURSE PROTOCOL_FILES protocol/*.cpp protocol/*.hpp)

add_library(ProtocolLib ${PROTOCOL_FILES})

target_link_libraries(ProtocolLib PUBLIC SecurityLib HelpersLib)
target_include_directories(ProtocolLib
        PUBLIC protocol/include
)
#end of ProtocolLib

#UserInputOutputLib
file(GLOB_RECURSE USER_INPUT_OUTPUT_FILES userInputOutput/*.cpp userInputOutput/*.hpp)

add_library(UserInputOutputLib ${USER_INPUT_OUTPUT_FILES})

target_link_libraries(UserInputOutputLib ProtocolLib)
target_include_directories(UserInputOutputLib
        PUBLIC userInputOutput/include
)
#end of UserInputOutputLib