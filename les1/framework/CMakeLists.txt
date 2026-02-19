cmake_minimum_required(VERSION 3.0)
project(les_1)

set(CMAKE_CXX_STANDARD 11)

if(NOT WIN32)
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads REQUIRED)
endif()

if(X11_FOUND)
    link_directories(${X11_LIB_DIRS})
    include_directories(${X11_INCLUDE_DIR})
endif()

add_executable(les_1 main.cpp CImg.h ActiveEdgeTable.cpp ActiveEdgeTable.h DrawTool.cpp DrawTool.h Point.h RGBColor.h Line.h EdgeTableRow.h EdgeTableRow.cpp Polygon.h Polygon.cpp Line.cpp RGBColor.cpp Point.cpp EdgeTable.cpp EdgeTable.h Edge.cpp)

target_link_libraries(les_1 ${X11_LIBRARIES} )