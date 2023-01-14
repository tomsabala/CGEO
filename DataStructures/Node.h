#include "../2D/Shapes_2D/Segment2d.h"

class Node{
public:
    Shapes2D::Segment2d *s;
    int height;
    Node * left;
    Node * right;
    Node(Shapes2D::Segment2d *seg){
        height = 1;
        s = seg;
        left = NULL;
        right = NULL;
    }
};
