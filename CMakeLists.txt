cmake_minimum_required(VERSION 3.16.3)
project(CGEO C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(extern/pybind11)

add_library(Geo_2D MODULE 2D/2D_bindings.cpp
                          2D/Shapes_2D/Point2d.cpp
                          2D/Shapes_2D/Segment2d.cpp
                          2D/Shapes_2D/Polygon.cpp
                          2D/Shapes_2D/Line2d.cpp
                          2D/Shapes_2D/Triangle2d.cpp
                          2D/Shapes_2D/Circle2d.cpp

                          DataStructures/SegmentBalancedTree.cpp
                          DataStructures/Node.h

                          2D/Algorithms_2D/ConvexHull2D.cpp
                          2D/Algorithms_2D/Triangulation2D.cpp
                          2D/Algorithms_2D/SegmentIntersection2D.cpp
                          2D/Algorithms_2D/SmallestEnclosingDisk.cpp 3D/Point3d.cpp 3D/Point3d.h 3D/Face3d.cpp 3D/Face3d.h)

target_link_libraries(Geo_2D PUBLIC pybind11::module)

install(TARGETS Geo_2D
        PUBLIC_HEADER
        DESTINATION lib
        LIBRARY DESTINATION lib
        )

