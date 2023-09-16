project( Datastructures_2D )

add_library( Datastructures2D SHARED
        SegmentBalancedTree.cpp
        Node.h
)

target_link_libraries( Datastructures2D PRIVATE Shapes2D )
