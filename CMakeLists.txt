cmake_minimum_required(VERSION 3.16.3)
project(CGEO C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory( extern/pybind11 )
add_subdirectory(src/2D/algorithms_2D)
add_subdirectory(src/data_structures)
add_subdirectory(src/2D/shapes_2D)

add_library(Geo_2D MODULE src/2D/2D_bindings.cpp)

target_link_libraries(Geo_2D PRIVATE Shapes2D)
target_link_libraries(Geo_2D PRIVATE Algorithms2D)
target_link_libraries(Geo_2D PRIVATE Datastructures2D)
target_link_libraries(Geo_2D PUBLIC pybind11::module)

pybind11_add_module(Point2D MODULE src/2D/shapes_2D/Point2d.cpp)

install(TARGETS Geo_2D
        PUBLIC_HEADER
        DESTINATION lib
        LIBRARY DESTINATION lib
        )

