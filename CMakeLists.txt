cmake_minimum_required(VERSION 3.16.3)
project(CGEO C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory( extern/pybind11 EXCLUDE_FROM_ALL)
add_subdirectory(src/2D/algorithms_2D)
add_subdirectory(src/data_structures)
add_subdirectory(src/2D/shapes_2D)

add_library(_cgeo MODULE src/2D/2D_bindings.cpp
        src/main.cpp)

target_link_libraries(_cgeo PRIVATE Shapes2D)
target_link_libraries(_cgeo PRIVATE Algorithms2D)
target_link_libraries(_cgeo PRIVATE Datastructures2D)
target_link_libraries(_cgeo PUBLIC pybind11::module)

pybind11_add_module(Point2D MODULE src/2D/shapes_2D/Point2d.cpp)

add_definitions( -DEXTENSION_NAME=_cgeo )

install(TARGETS _cgeo
        PUBLIC_HEADER
        DESTINATION lib
        LIBRARY DESTINATION lib
        )

