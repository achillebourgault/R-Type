cmake_minimum_required(VERSION 3.17)
project(r-type)
set(CMAKE_CXX_STANDARD 20)
#set binary output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/.monsters)

set(CONAN_DISABLE_CHECK_COMPILER 1)
if(WIN32)
    set(CMAKE_BUILD_TYPE Debug)
    # We have to set _WIN32_WINNT for Asio
    if(${CMAKE_SYSTEM_VERSION} EQUAL 10) # Windows 10
        add_definitions(-D _WIN32_WINNT=0x0A00)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.3) # Windows 8.1
        add_definitions(-D _WIN32_WINNT=0x0603)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.2) # Windows 8
        add_definitions(-D _WIN32_WINNT=0x0602)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.1) # Windows 7
        add_definitions(-D _WIN32_WINNT=0x0601)
    elseif(${CMAKE_SYSTEM_VERSION} EQUAL 6.0) # Windows Vista
        add_definitions(-D _WIN32_WINNT=0x0600)
    endif()
endif()

#conan init
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS)

include_directories(Shared)
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Monsters)