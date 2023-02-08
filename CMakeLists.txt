cmake_minimum_required(VERSION 3.00)
project(sfPaint LANGUAGES CXX)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
add_subdirectory(deps)
add_library(
    brush
    src/brush.cpp
    src/brush.hpp
)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
add_executable(sfPaint src/main.cpp)
target_link_libraries(sfPaint PRIVATE  brush ImGui-SFML::ImGui-SFML stdc++fs)
