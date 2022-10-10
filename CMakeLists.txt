cmake_minimum_required (VERSION 3.17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

project(rtype CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(ClientSrc
client/main.cpp)

set(ServerSrc
server/main.cpp)

include(FetchContent)
FetchContent_Declare(sfml                             # name of the content
    GIT_REPOSITORY https://github.com/SFML/SFML.git  # the repository
    GIT_TAG        2.5.1                             # the tag
)
FetchContent_MakeAvailable(sfml)
FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()
# add_subdirectory(SFML)
# find_package(SFML 2.5 COMPONENTS window graphics system network REQUIRED)

add_executable(r-type_client ${ClientSrc})
add_executable(r-type_server ${ServerSrc})
target_compile_options(r-type_client
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
					   $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>)

target_link_libraries(r-type_client PRIVATE sfml-window)
target_link_libraries(r-type_client PRIVATE sfml-network)
target_link_libraries(r-type_client PRIVATE sfml-system)
target_link_libraries(r-type_client PRIVATE sfml-graphics)



# cmake_minimum_required(VERSION 3.6)
# project(simple-sfml-cmake-example)

# set(CMAKE_MODULE_PATH
#     ${CMAKE_SOURCE_DIR}/cmake_modules
#     ${CMAKE_MODULE_PATH})

#     include_directories(${SFML_INCLUDE_DIR})

# find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# set(ClientSrc
# client/main.cpp)

# set(ServerSrc
# server/main.cpp)

# add_executable(r-type_client ${ClientSrc})
# add_executable(r-type_server ${ServerSrc})

# target_compile_features(r-type_client
#                         PRIVATE
#                         cxx_std_17)

# # Any additional include files would go here
# #target_include_directories(r-type_client
# #                           PUBLIC
# #                           )

# target_compile_definitions(r-type_client
#                            PRIVATE
#                            $<$<CONFIG:Debug>:DEBUG>)
