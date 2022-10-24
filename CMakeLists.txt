cmake_minimum_required(VERSION 3.0.0)
project(physic-engine VERSION 0.1.0)

include(CTest)
enable_testing()

link_directories(${CMAKE_SOURCE_DIR}/imgui/libs/glfw/lib-vs2010-32)
link_directories(${CMAKE_SOURCE_DIR}/imgui/libs/glfw/lib-vs2010-64)


set(ENGINES ./engine/Registry.cpp ./engine/Registry.h ./engine/Force.cpp ./engine/Forces.cpp ./engine/Particule.cpp ./engine/Vector3.cpp ./engine/Force.h ./engine/Forces.h ./engine/Particule.h ./engine/Vector3.h ./engine/PhysicWorld.h ./engine/PhysicWorld.cpp ./engine/ParticleContact.cpp ./engine/ParticleContact.h ./engine/ParticleContactResolver.h ./engine/ParticleContactResolver.cpp ./engine/ParticleLink.h ./engine/ParticleLink.cpp ./engine/ParticleCable.h ./engine/ParticleCable.cpp ./engine/ParticleRod.h ./engine/ParticleRod.cpp ./engine/NaiveParticleContactGenerator.h ./engine/NaiveParticleContactGenerator.cpp ./engine/WallContactGenerator.cpp ./engine/WallContactGenerator.h)

set(IMGUI ./imgui/imgui.cpp ./imgui/imgui_demo.cpp ./imgui/imgui_draw.cpp ./imgui/imgui_tables.cpp ./imgui/imgui_widgets.cpp ./imgui/imgui_impl_glfw.cpp ./imgui/imgui_impl_opengl3.cpp)

add_executable(test1 test1.cpp ${ENGINES} ${IMGUI})
target_include_directories(test1 PUBLIC ./engine ./imgui ./imgui/libs/glfw/include)
target_link_directories(test1 PUBLIC imgui/libs/glfw/lib-vc2010-64 imgui/libs/glfw/lib-vc2010-32)
target_link_libraries(test1 PRIVATE opengl32.lib glfw3.lib)

add_executable(test2 test2.cpp ${ENGINES} ${IMGUI})
target_include_directories(test2 PUBLIC ./engine ./imgui ./imgui/libs/glfw/include)
target_link_directories(test2 PUBLIC imgui/libs/glfw/lib-vc2010-64 imgui/libs/glfw/lib-vc2010-32)
target_link_libraries(test2 PRIVATE opengl32.lib glfw3.lib)

add_executable(test3 "test3.cpp" ${ENGINES} ${IMGUI})
target_include_directories(test3 PUBLIC ./engine ./imgui ./imgui/libs/glfw/include)
target_link_directories(test3 PUBLIC imgui/libs/glfw/lib-vc2010-64 imgui/libs/glfw/lib-vc2010-32)
target_link_libraries(test3 PRIVATE opengl32.lib glfw3.lib)

add_executable(pool pool.cpp ${ENGINES} ${IMGUI})
target_include_directories(pool PUBLIC ./engine ./imgui ./imgui/libs/glfw/include)
target_link_directories(pool PUBLIC imgui/libs/glfw/lib-vc2010-64 imgui/libs/glfw/lib-vc2010-32)
target_link_libraries(pool PRIVATE opengl32.lib glfw3.lib)

add_executable(amas "amas.cpp" ${ENGINES} ${IMGUI})
target_include_directories(amas PUBLIC ./engine ./imgui ./imgui/libs/glfw/include)
target_link_directories(amas PUBLIC imgui/libs/glfw/lib-vc2010-64 imgui/libs/glfw/lib-vc2010-32)
target_link_libraries(amas PRIVATE opengl32.lib glfw3.lib)

SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"msvcrt.lib\")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
