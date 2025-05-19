cmake_minimum_required(VERSION 3.22)

set(NPROJ rutubeload)
set(SOURCE_EXE ${CMAKE_HOME_DIRECTORY}/src/main.cpp
                ${CMAKE_HOME_DIRECTORY}/src/headerurl.cpp
                ${CMAKE_HOME_DIRECTORY}/src/net_tools.cpp
)

include_directories(include)

project(${NPROJ})

add_compile_options("-g")

add_executable(${NPROJ} ${SOURCE_EXE})

target_link_libraries(${NPROJ} curl)