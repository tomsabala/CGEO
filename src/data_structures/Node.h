#include "../2D/shapes_2D/Segment2d.h"

class Node{
public:
    Shapes2D::Segment2d s;
    int height;
    Node * left;
    Node * right;
    explicit Node(const Shapes2D::Segment2d& seg) : s(seg){
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};
