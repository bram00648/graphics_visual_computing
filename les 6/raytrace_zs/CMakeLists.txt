cmake_minimum_required(VERSION 3.5)
project(raytrace_framework)

set(CMAKE_CXX_STANDARD 17)

set(glm_DIR includes/glm/cmake/glm) # if necessary
find_package(glm REQUIRED)

if(NOT WIN32)
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads REQUIRED)
endif()

if(X11_FOUND)
    link_directories(${X11_LIB_DIRS})
    include_directories(${X11_INCLUDE_DIR})
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES} )
endif()

add_executable(raytrace_framework main.cpp CImg.h RayTracer.cpp RayTracer.h RGBColor.h Shape.cpp Shape.h)
target_link_libraries(raytrace_framework glm::glm)