cmake_minimum_required(VERSION 3.16.3)
project(CGEO C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(extern/pybind11)

add_library(Geo_2D MODULE src/2D/2D_bindings.cpp
        src/2D/Shapes_2D/Point2d.cpp
        src/2D/Shapes_2D/Segment2d.cpp
        src/2D/Shapes_2D/Polygon.cpp
        src/2D/Shapes_2D/Line2d.cpp
        src/2D/Shapes_2D/Triangle2d.cpp
        src/2D/Shapes_2D/Circle2d.cpp

        src/DataStructures/SegmentBalancedTree.cpp
        src/DataStructures/Node.h

        src/2D/Algorithms_2D/ConvexHull2D.cpp
        src/2D/Algorithms_2D/Triangulation2D.cpp
        src/2D/Algorithms_2D/SegmentIntersection2D.cpp
        src/2D/Algorithms_2D/SmallestEnclosingDisk.cpp src/3D/Point3d.cpp src/3D/Point3d.h src/3D/Face3d.cpp src/3D/Face3d.h)

target_link_libraries(Geo_2D PUBLIC pybind11::module)

install(TARGETS Geo_2D
        PUBLIC_HEADER
        DESTINATION lib
        LIBRARY DESTINATION lib
        )

