cmake_minimum_required(VERSION 3.5)
project(raytrace_framework)

set(CMAKE_CXX_STANDARD 17)

# glm
set(glm_DIR includes/glm/cmake/glm) # indien nodig
find_package(glm REQUIRED)

# X11 en Threads (Linux)
if(NOT WIN32)
    find_package(X11 REQUIRED)
    find_package(Threads REQUIRED)
endif()

# executable met alle cpp files
add_executable(raytrace_framework
    main.cpp
    RayTracer.cpp
    Sphere.cpp
    Scene.cpp
    Shape.cpp
)

# libraries linken
target_link_libraries(raytrace_framework
    glm::glm
    ${X11_LIBRARIES}
    Threads::Threads
)