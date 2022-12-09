#pragma once

#include <iostream>
#include "../2D/Shapes_2D/Segment2d.h"

class TreeNode {
private:
    /* attributes */
    Shapes2D::Segment2d* segment;
    TreeNode* right;
    TreeNode* left;
    TreeNode* parent;

public:
    TreeNode(Shapes2D::Segment2d s); /* standard constructor */

    /* set attributes */
    void setSegment(Shapes2D::Segment2d s);
    void setRight(TreeNode* r);
    void setLeft(TreeNode* l);
    void setParent(TreeNode* p);

    /* get attributes */
    Shapes2D::Segment2d* getSegment();
    TreeNode* getRight();
    TreeNode* getLeft();
    TreeNode* getParent();
    ~TreeNode();
};
