#include<iostream>
#include "Node.h"

class SegmentBalancedTree{
public:

    Node *root = nullptr;
    int size;
    Shapes2D::Point2d *sweepLine;

    SegmentBalancedTree();

    void insert(const Shapes2D::Segment2d &);
    void remove(const Shapes2D::Segment2d&);
    Node * search(const Shapes2D::Segment2d &);
    Node * search_p(const Shapes2D::Point2d&);
    void walkInOrder();
    [[nodiscard]] Node * minn() const;
    [[nodiscard]] Node * maxx() const;
    Node * getPred(Node *);
    Node * getSucc(Node *);

private:
    Node * _insert_(Node *, const Shapes2D::Segment2d &);
    Node * _remove_(Node *, const Shapes2D::Segment2d&);
    Node * _search_(Node *, const Shapes2D::Segment2d &);
    Node * _search_p_(Node *, const Shapes2D::Point2d &);
    void _walkInOrder_(Node *);
    static int _height_(Node *);
    static Node * _rightRotation_(Node *);
    static Node * _leftRotation_(Node *);
    [[nodiscard]] bool _le_(const Shapes2D::Segment2d &, const Shapes2D::Segment2d &) const;
    void _items_(std::vector<Node *> *, Node *);
};
