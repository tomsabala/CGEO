#include "../2D/shapes_2D/Segment2d.h"

class Node{
public:
    Shapes2D::Segment2d *s;
    int height;
    Node * left;
    Node * right;
    explicit Node(Shapes2D::Segment2d *seg){
        height = 1;
        s = seg;
        left = nullptr;
        right = nullptr;
    }
};
