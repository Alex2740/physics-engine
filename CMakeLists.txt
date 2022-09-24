cmake_minimum_required(VERSION 3.0.0)
project(physic-engine VERSION 0.1.0)

include(CTest)
enable_testing()

link_directories(${CMAKE_SOURCE_DIR}/imgui/libs/glfw/lib-vs2010-32)
link_directories(${CMAKE_SOURCE_DIR}/imgui/libs/glfw/lib-vs2010-64)


set(ENGINES ./engine/Forces.cpp ./engine/Particule.cpp ./engine/Vector3.cpp ./engine/Forces.h ./engine/Particule.h ./engine/Vector3.h)

set(IMGUI ./imgui/imgui.cpp ./imgui/imgui_demo.cpp ./imgui/imgui_draw.cpp ./imgui/imgui_tables.cpp ./imgui/imgui_widgets.cpp ./imgui/imgui_impl_glfw.cpp ./imgui/imgui_impl_opengl3.cpp)

add_executable(physic-engine main.cpp ${ENGINES} ${IMGUI})
target_include_directories(physic-engine PUBLIC ./engine ./imgui ./imgui/libs/glfw/include)
target_link_directories(physic-engine PUBLIC imgui/libs/glfw/lib-vc2010-64 imgui/libs/glfw/lib-vc2010-32)
target_link_libraries(physic-engine PRIVATE opengl32.lib glfw3.lib)
SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"msvcrt.lib\")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)