cmake_minimum_required (VERSION 3.17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

project(rtype CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(ClientSrc
client/main.cpp)

set(ServerSrc
server/main.cpp)

add_executable(r-type_client ${ClientSrc})
add_executable(r-type_server ${ServerSrc})