project( Shapes_2D )
#set( ${SHAPES_2D_SOURCES}
#        Circle2d.cpp
#        Line2d.cpp
#        Point2d.cpp
#        Polygon.cpp
#        Segment2d.cpp
#        Triangle2d.cpp) # Setup the list of sources here.

#add_library( Shapes2D ${SHAPES_2D_SOURCES} )

add_library( Shapes2D SHARED
        Circle2d.cpp
        Line2d.cpp
        Point2d.cpp
        Polygon.cpp
        Segment2d.cpp
        Triangle2d.cpp
        ../Exception2D.cpp
)

