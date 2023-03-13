cmake_minimum_required(VERSION 3.00)
project(sfPaint LANGUAGES CXX)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
add_subdirectory(deps)
add_library(
    brush
    src/brush.cpp
    src/brush.hpp
)
add_library(
    line
    src/lineTool.cpp
    src/lineTool.hpp
)
# find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
add_executable(sfPaint src/main.cpp)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET CMakeSFMLProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:CMakeSFMLProject> $<TARGET_FILE_DIR:CMakeSFMLProject> COMMAND_EXPAND_LISTS)
endif()
target_link_libraries(sfPaint PRIVATE line brush ImGui-SFML::ImGui-SFML stdc++fs)
