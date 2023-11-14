cmake_minimum_required(VERSION 3.5)
project(sfPaint)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
add_subdirectory(deps)
find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

add_library(
    gen_utils
    src/utils/general.cpp
    src/utils/general.hpp
)

add_library( 
    imfilebrowser
    INTERFACE
    src/utils/imfilebrowser.h
)

add_executable(sfPaint src/main.cpp)


add_subdirectory(src/tools)

link_libraries(imfilebrowser ImGui-SFML::ImGui-SFML)

target_link_libraries(sfPaint PUBLIC gen_utils ImGui-SFML::ImGui-SFML stdc++fs imfilebrowser  Tool Pen Fill Pipet )
