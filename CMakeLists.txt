cmake_minimum_required(VERSION 3.16.3)
project(CGEO C CXX)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory( extern/pybind11 )
add_subdirectory( 2D/Algorithms_2D )
add_subdirectory( DataStructures )
add_subdirectory( 2D/Shapes_2D )

add_library(Geo_2D MODULE 2D/2D_bindings.cpp)

target_link_libraries(Geo_2D PRIVATE Shapes2D)
target_link_libraries(Geo_2D PRIVATE Algorithms2D)
target_link_libraries(Geo_2D PRIVATE Datastructures2D)
target_link_libraries(Geo_2D PUBLIC pybind11::module)

install(TARGETS Geo_2D
        PUBLIC_HEADER
        DESTINATION lib
        LIBRARY DESTINATION lib
        )

