cmake_minimum_required(VERSION 3.20)

project(ImTag VERSION 0.1.0 LANGUAGES C CXX)

# ==============================================================================
# CONFIGURACIÓN GENERAL
# ==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ImTag
    src/main.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
)

target_include_directories(ImTag PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
