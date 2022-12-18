cmake_minimum_required(VERSION 3.0.0)
project(physic-engine VERSION 0.1.0)

include(CTest)
enable_testing()

link_directories(${CMAKE_SOURCE_DIR}/src/imgui/libs/glfw/lib-vs2010-32)
link_directories(${CMAKE_SOURCE_DIR}/src/imgui/libs/glfw/lib-vs2010-64)

set(ENGINES
    ./src/physics/contact/ParticleContact.cpp
    ./src/physics/contact/ParticleContact.h
    ./src/physics/contact/ParticleContactResolver.cpp
    ./src/physics/contact/ParticleContactResolver.h
    ./src/physics/contact/ParticleLink.cpp
    ./src/physics/contact/ParticleLink.h
    ./src/physics/contact/ParticleCable.cpp
    ./src/physics/contact/ParticleCable.h
    ./src/physics/contact/ParticleRod.cpp
    ./src/physics/contact/ParticleRod.h
    ./src/physics/contact/NaiveParticleContactGenerator.cpp
    ./src/physics/contact/NaiveParticleContactGenerator.h
    ./src/physics/contact/WallContactGenerator.cpp
    ./src/physics/contact/WallContactGenerator.h
    ./src/physics/contact/BoundingSphere.h
    ./src/physics/contact/BoundingSphere.cpp

    ./src/physics/contact/BVHNode.h
    ./src/physics/contact/BVHNode.cpp
    ./src/physics/contact/Contact.h
    ./src/physics/contact/CollisionData.h
    ./src/physics/contact/PotentialContact.h
    ./src/physics/contact/PotentialContact.cpp
    ./src/physics/contact/CollisionInterpretor.h
    ./src/physics/contact/CollisionInterpretor.cpp
    ./src/physics/contact/CollisionData.h
    ./src/physics/contact/CollisionData.cpp
    ./src/physics/contact/CollisionDetector.cpp
    ./src/physics/contact/CollisionDetector.h
    ./src/physics/contact/Contact.h

    ./src/physics/contact/primitive/Primitive.h
    ./src/physics/contact/primitive/Sphere.h
    ./src/physics/contact/primitive/Sphere.cpp
    ./src/physics/contact/primitive/Plane.h
    ./src/physics/contact/primitive/Plane.cpp
    ./src/physics/contact/primitive/Box.h
    ./src/physics/contact/primitive/Box.cpp

    ./src/physics/Rigidbody.cpp
    ./src/physics/Rigidbody.h

    ./src/physics/Registry.cpp
    ./src/physics/Registry.h
    ./src/physics/Force.cpp
    ./src/physics/Force.h
    ./src/physics/Particule.cpp
    ./src/physics/Particule.h
    ./src/physics/PhysicWorld.cpp
    ./src/physics/PhysicWorld.h
    ./src/physics/Transform.h
    ./src/physics/Transform.cpp
    ./src/physics/IForceAppliable.cpp
    ./src/physics/IForceAppliable.h
)

set(CORE
    ./src/core/Vector3.cpp
    ./src/core/Vector3.h
    ./src/core/Matrix3.cpp
    ./src/core/Matrix3.h
    ./src/core/Matrix4.cpp
    ./src/core/Matrix4.h
    ./src/core/Quaternion.cpp
    ./src/core/Quaternion.h
    ./src/core/Angles.h;
)

set(IMGUI
    ./src/imgui/imgui.cpp
    ./src/imgui/imgui_demo.cpp
    ./src/imgui/imgui_draw.cpp
    ./src/imgui/imgui_tables.cpp
    ./src/imgui/imgui_widgets.cpp
    ./src/imgui/imgui_impl_glfw.cpp
    ./src/imgui/imgui_impl_opengl3.cpp
)

set(GRAPHICS
    ./src/graphics/glad.c
    ./src/graphics/stb.cpp

    ./src/graphics/shader.cpp ./src/graphics/shader.h

    ./src/graphics/vao.cpp ./src/graphics/vao.h
    ./src/graphics/vbo.cpp ./src/graphics/vbo.h
    ./src/graphics/ebo.cpp ./src/graphics/ebo.h

    ./src/graphics/texture.cpp ./src/graphics/texture.h
    ./src/graphics/camera.h ./src/graphics/camera.cpp

    ./src/graphics/api.h ./src/graphics/api.cpp

    ./src/graphics/renderer.cpp ./src/graphics/renderer.h
)

add_executable(main ./main.cpp ${ENGINES} ${IMGUI} ${GRAPHICS} ${CORE})
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/src
src/core
src/physics
src/imgui/libs/glfw/include src/include)
target_link_directories(main PUBLIC src/imgui/libs/glfw/lib-vc2010-64 src/imgui/libs/glfw/lib-vc2010-32)
target_link_libraries(main PRIVATE opengl32.lib glfw3.lib)
target_compile_features(main PRIVATE cxx_std_17)

add_executable(whirlpool ./demo/whirlpool.cpp ${ENGINES} ${IMGUI} ${GRAPHICS} ${CORE})
target_include_directories(whirlpool PUBLIC ${CMAKE_SOURCE_DIR}/src src/core src/physics src/graphics src/imgui/libs/glfw/include src/include)
target_link_directories(whirlpool PUBLIC src/imgui/libs/glfw/lib-vc2010-64 src/imgui/libs/glfw/lib-vc2010-32)
target_link_libraries(whirlpool PRIVATE opengl32.lib glfw3.lib)
target_compile_features(whirlpool PRIVATE cxx_std_17)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/resources
        COMMENT "Copying resources into binary directory")

add_dependencies(main copy_resources)

SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:\"msvcrt.lib\")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
