project( Datastructures_2D )
#set( sources ${ALGORITHMS_2D_SOURCES}
#        ConvexHull2D.cpp
#        SegmentIntersection2D.cpp
#        SmallestEnclosingDisk.cpp
#        Triangulation2D.cpp) # Setup the list of sources here.

#add_library( Algorithms2D ${ALGORITHMS_2D_SOURCES} )

add_library( Datastructures2D SHARED
        SegmentBalancedTree.cpp
        Node.h
)

target_link_libraries( Datastructures2D PRIVATE Shapes2D )
