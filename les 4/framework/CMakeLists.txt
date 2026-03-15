cmake_minimum_required(VERSION 3.10)
project(framework)

set(CMAKE_CXX_STANDARD 11)

if(NOT WIN32)
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads REQUIRED)
endif()

if(X11_FOUND)
    link_directories(${X11_LIB_DIRS})
    include_directories(${X11_INCLUDE_DIR})
    SET( SYSTEM_LIBS ${SYSTEM_LIBS} ${X11_LIBRARIES} )
endif()

add_executable(framework computer_graphics.cpp CImg.h ActiveEdgeTable.cpp ActiveEdgeTable.h DrawTool.cpp DrawTool.h Point.h RGBColor.h Line.h EdgeTableRow.h EdgeTableRow.cpp Polygon.h Polygon.cpp Line.cpp RGBColor.cpp Point.cpp EdgeTable.cpp EdgeTable.h Edge.cpp FileLoader.h FileLoader.cpp ParamCubeCurve.cpp ParamCubeCurve.h Bezier.cpp Bezier.h)
target_include_directories(framework PRIVATE includes)
target_link_libraries(framework PRIVATE ${SYSTEM_LIBS} Threads::Threads)
