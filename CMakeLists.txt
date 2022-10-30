cmake_minimum_required(VERSION 3.21)
project(whisper_ipc VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

# LIBS
## GTEST
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(INSTALL_GTEST "Enable installation of googletest." OFF)
FetchContent_MakeAvailable(googletest)

## sockbuf
FetchContent_Declare(
        sockbuf
        GIT_REPOSITORY https://github.com/NateSeymour/sockbuf.git
        GIT_TAG v1.0.2
)
FetchContent_MakeAvailable(sockbuf)

## format
FetchContent_Declare(
        format
        GIT_REPOSITORY https://github.com/NateSeymour/format.git
        GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(format)

# Whisper
add_library(whisperipc
        src/Client.cpp
        src/Client.h
        src/Connection.cpp
        src/Connection.h
        src/Header.cpp
        src/Header.h
        src/Server.cpp
        src/Header.h
        src/Messageable.cpp
        src/Messageable.h
        src/ipc_error.cpp
        src/ipc_error.h
        src/Message.cpp
        src/Message.h)
target_link_libraries(whisperipc PRIVATE sockbuf format)

# Tests
add_executable(whisper-unit-tests
        test/unit/Header.test.cpp)
target_link_libraries(whisper-unit-tests PUBLIC whisperipc PRIVATE gtest_main)