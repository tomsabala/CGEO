project( Algorithms_2D )

add_library( Algorithms2D SHARED
        ConvexHull2D.cpp
        SegmentIntersection2D.cpp
        SmallestEnclosingDisk.cpp
        Triangulation2D.cpp
)

target_link_libraries( Algorithms2D PRIVATE Shapes2D Datastructures2D )
