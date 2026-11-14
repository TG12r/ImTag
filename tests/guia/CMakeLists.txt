cmake_minimum_required(VERSION 3.20)

project(guia VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Dependencias
# ------------------------------------------------------------------------------
include(FetchContent)

# 1. OpenGL
find_package(OpenGL REQUIRED)

# 2. GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# 3. Dear ImGui (rama docking)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

# ------------------------------------------------------------------------------
# Targets: GLAD & ImGui
# ------------------------------------------------------------------------------
# GLAD 2 (OpenGL 4.6 Core)
add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/glad.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ImGui + backends GLFW y OpenGL3
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

# ------------------------------------------------------------------------------
# Ejecutable: Guia
# ------------------------------------------------------------------------------
add_executable(guia
    guia.cpp
)

target_include_directories(guia PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(guia PRIVATE
    GLFW_INCLUDE_NONE
)

target_link_libraries(guia PRIVATE
    glad
    imgui
    glfw
    OpenGL::GL
)

if(WIN32)
    target_link_libraries(guia PRIVATE dwmapi)
endif()
