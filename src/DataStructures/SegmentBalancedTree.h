#include<iostream>
#include "Node.h"

class SegmentBalancedTree{
public:

    Node *root = NULL;
    int size;
    Shapes2D::Point2d *sweepLine;

    void insert(Shapes2D::Segment2d *);
    void remove(Shapes2D::Segment2d *);
    Node * search(Shapes2D::Segment2d *);
    Node * search_p(Shapes2D::Point2d *);
    void walkInOrder();
    Node * minn();
    Node * maxx();
    Node * getPred(Node *);
    Node * getSucc(Node *);

private:
    Node * _insert_(Node *, Shapes2D::Segment2d *);
    Node * _remove_(Node *, Shapes2D::Segment2d *);
    Node * _search_(Node *, Shapes2D::Segment2d *);
    Node * _search_p_(Node *, Shapes2D::Point2d *);
    void _walkInOrder_(Node *);
    int _height_(Node *);
    Node * _rightRotation_(Node *);
    Node * _leftRotation_(Node *);
    bool _le_(Shapes2D::Segment2d *, Shapes2D::Segment2d *);
    void _items_(std::vector<Node *> *, Node *);
};
