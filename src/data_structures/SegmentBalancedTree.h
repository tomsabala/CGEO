#include<iostream>
#include "Node.h"

class SegmentBalancedTree{
public:

    Node *root = nullptr;
    int size{};
    Shapes2D::Point2d *sweepLine{};

    void insert(Shapes2D::Segment2d *);
    void remove(Shapes2D::Segment2d *);
    Node * search(Shapes2D::Segment2d *);
    Node * search_p(Shapes2D::Point2d *);
    void walkInOrder();
    Node * minn() const;
    Node * maxx() const;
    Node * getPred(Node *);
    Node * getSucc(Node *);

private:
    Node * _insert_(Node *, Shapes2D::Segment2d *);
    Node * _remove_(Node *, Shapes2D::Segment2d *);
    Node * _search_(Node *, Shapes2D::Segment2d *);
    Node * _search_p_(Node *, Shapes2D::Point2d *);
    void _walkInOrder_(Node *);
    static int _height_(Node *);
    static Node * _rightRotation_(Node *);
    static Node * _leftRotation_(Node *);
    bool _le_(Shapes2D::Segment2d *, Shapes2D::Segment2d *) const;
    void _items_(std::vector<Node *> *, Node *);
};
