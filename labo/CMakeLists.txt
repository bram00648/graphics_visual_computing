cmake_minimum_required(VERSION 3.24)
project(opengl_project)
set(CMAKE_CXX_STANDARD 17)

add_library(GLAD glad.c)
target_include_directories(GLAD PUBLIC ${CMAKE_SOURCE_DIR}/includes)

add_executable(opengl_project main.cpp)
target_include_directories(opengl_project PRIVATE ${CMAKE_SOURCE_DIR}/includes)

if(WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/lib)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

    find_package(OpenGL REQUIRED)
    find_package(GLM REQUIRED)
    find_package(GLFW3 REQUIRED)

    message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
    message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

    target_include_directories(opengl_project PRIVATE ${GLM_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR})

    target_link_libraries(opengl_project PRIVATE
        GLAD
        glfw3
        opengl32
    )

elseif(UNIX)
    # -------------------------------------------------------
    # Linux: uses system packages
    # install appropriate glfw version vor your desktop environment, an example is pacman -S glfw-wayland for wayland and pacman -S glfw-x11 for x11
    # -------------------------------------------------------
    find_package(OpenGL REQUIRED)
    find_package(glfw3 3.3 REQUIRED)
    find_package(glm REQUIRED)

    message(STATUS "Found GLFW3")
    message(STATUS "Found GLM")

    target_link_libraries(opengl_project PRIVATE
        GLAD
        glfw
        OpenGL::GL
        glm::glm
        pthread
        dl
    )

endif()