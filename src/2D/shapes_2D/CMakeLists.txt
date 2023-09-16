project( Shapes_2D )

add_library( Shapes2D SHARED
        Circle2d.cpp
        Line2d.cpp
        Point2d.cpp
        Polygon.cpp
        Segment2d.cpp
        Triangle2d.cpp
        ../Exception2D.cpp
)

target_link_libraries(Shapes2D  PUBLIC pybind11::module)