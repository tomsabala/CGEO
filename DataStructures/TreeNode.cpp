#include "TreeNode.h"

TreeNode::TreeNode(Shapes2D::Segment2d s)
{
    segment = new Shapes2D::Segment2d(s);
    right = left = parent = NULL;
}

void TreeNode::setSegment(Shapes2D::Segment2d s) {
    segment = new Shapes2D::Segment2d(s);
}

void TreeNode::setRight(TreeNode* r) {
    right = r;
}

void TreeNode::setLeft(TreeNode* l) {
    left = l;
}

void TreeNode::setParent(TreeNode* p) {
    parent = p;
}

Shapes2D::Segment2d* TreeNode::getSegment() {
    return segment;
}

TreeNode* TreeNode::getRight() {
    return right;
}

TreeNode* TreeNode::getLeft() {
    return left;
}

TreeNode* TreeNode::getParent() {
    return parent;
}

TreeNode::~TreeNode(){}