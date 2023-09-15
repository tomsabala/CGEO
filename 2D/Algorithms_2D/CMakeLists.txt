project( Algorithms_2D )
#set( sources ${ALGORITHMS_2D_SOURCES}
#        ConvexHull2D.cpp
#        SegmentIntersection2D.cpp
#        SmallestEnclosingDisk.cpp
#        Triangulation2D.cpp) # Setup the list of sources here.

#add_library( Algorithms2D ${ALGORITHMS_2D_SOURCES} )

add_library( Algorithms2D SHARED
        ConvexHull2D.cpp
        SegmentIntersection2D.cpp
        SmallestEnclosingDisk.cpp
        Triangulation2D.cpp
)

target_link_libraries( Algorithms2D PRIVATE Shapes2D Datastructures2D )
