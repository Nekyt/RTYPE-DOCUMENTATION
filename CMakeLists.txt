cmake_minimum_required(VERSION 3.19)
project(RTYPE LANGUAGES CXX)

set(DEBUG_MODE TRUE)
set(CMAKE_BUILD_TYPE DEBUG)

set(CLIENT RTYPE_client)
set(SERVER RTYPE_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

add_definitions("-fPIC -Wall -Wextra -Wno-empty-body -Wno-switch")
if(CMAKE_BUILD_TYPE MATCHES DEV)
    add_definitions("")
endif()

if(CMAKE_BUILD_TYPE MATCHES RELEASE)
    add_definitions("-O3 -lto")
endif()

if(DEBUG_MODE MATCHES TRUE)
    add_definitions("-g -DDEBUG")
endif()

#find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
#include_directories(${SFML_INCLUDE_DIRS})
#include_directories("/opt/homebrew/Cellar/sfml/2.5.1_1/include")

include(build/conanbuildinfo.cmake)
include(build/conan_paths.cmake)
conan_basic_setup(KEEP_RPATHS)

file(GLOB_RECURSE SRC_CLIENT Client/*)
file(GLOB_RECURSE SRC_COMMON ${PROJECT_SOURCE_DIR}/Ecs/*)
file(GLOB_RECURSE SRC_COMMONS ${PROJECT_SOURCE_DIR}/Graphics/*)

# include(conan.cmake)

# conan_cmake_run(REQUIRES Catch2/2.6.0@catchorg/stable
#                 BASIC_SETUP)

add_executable(${CLIENT} ${SRC_CLIENT} ${SRC_COMMON} ${SRC_COMMONS})

set(SHARED_INCLUDE_FOLDER shared)
target_include_directories(${CLIENT} PUBLIC SHARED_INCLUDE_FOLDER)

#conan_target_link_libraries(${CLIENT} PRIVATE CONAN_PKG::SFML)

target_link_libraries(${CLIENT} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
# target_link_libraries(${CLIENT} CONAN_PKG::SFML)

# conan_target_link_libraries(${SERVER} PRIVATE CONAN_PKG::ASIO)
# conan_target_link_libraries(${CLIENT} PRIVATE CONAN_PKG::BOOST)