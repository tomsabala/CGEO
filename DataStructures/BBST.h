#pragma once

#include <iostream>
#include "TreeNode.h"
#include "../2D/Shapes_2D/Line2d.h"


class BST {
    TreeNode* root;
    Shapes2D::Point2d height;
    int size;

    bool remove(TreeNode*);
    TreeNode* insert(Shapes2D::Segment2d* s, TreeNode* node);
    void setRoot(TreeNode* node);
    void setSize(int s);
    TreeNode* rr_leftRotation(TreeNode*);
    TreeNode* ll_rightRotation(TreeNode*);
    TreeNode* lr_doubleRightRotation(TreeNode*);
    TreeNode* rl_doubleLeftRotation(TreeNode*);

    /* comparison functions */
    bool _le_(Shapes2D::Segment2d v, Shapes2D::Segment2d u);
    bool _ge_(Shapes2D::Segment2d v, Shapes2D::Segment2d u);

public:
    BST();
    int getSize();
    TreeNode* getRoot();
    void insertSegment(Shapes2D::Segment2d* s);
    TreeNode* searchSegment(Shapes2D::Segment2d);
    TreeNode* searchPoint(Shapes2D::Point2d *);
    TreeNode* getPredecessor(TreeNode *);
    TreeNode* getSuccessor(TreeNode *);
    TreeNode* maxx(TreeNode*);
    TreeNode* minn(TreeNode*);
    void walkInOrder(TreeNode*);
    void walkPreOrder(TreeNode*);
    void walkPostOrder(TreeNode*);
    int high(TreeNode*);
    bool removeSegment(Shapes2D::Segment2d);
    Shapes2D::Segment2d parentDisplay(Shapes2D::Segment2d);
    void setHeight(Shapes2D::Point2d p);
    ~BST();
};
