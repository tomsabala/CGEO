
#include "BBST.h"

BST::BST()
{
    this->root = NULL;
    this->size = 0;
}

/** public function for inserting a new segment to the tree
 * @param s new segment object to insert
 * */
void BST::insertSegment(Shapes2D::Segment2d* s)
{
    this->root = insert(s, this->root);
}

/**
 * this is the main private function for inserting a new segment to the tree
 * @param s new segment to insert
 * @param node sub-tree in which segment should be inserted to
 * @return pointer to the new node that contains the segment
 */
TreeNode* BST::insert(Shapes2D::Segment2d* s, TreeNode* node)
{

    /* if node is null than insert segment as a leaf */
    if (node == NULL)
    {
        size++;
        node = new TreeNode(*s);
    }

    /* search the subtree in which segment should be inserted in */
    else if (this->_le_(*s, *node->getSegment()))
    {
        TreeNode* left = node->getLeft();
        if (left == NULL)
            node->setLeft(insert(s, NULL));
        else
            node->setLeft(insert(s, left));

        node->getLeft()->setParent(node);
        if (this->high(node->getLeft()) - this->high(node->getRight()) == 2)
        {
            if (_le_(*s, *node->getLeft()->getSegment()))
                node = this->ll_rightRotation(node);
            else
                node = this->lr_doubleRightRotation(node);
        }
    }

    else if (this->_ge_(*s, *node->getSegment()))
    {
        TreeNode* right = node->getRight();
        if (right == NULL)
            node->setRight(insert(s, NULL));
        else
            node->setRight(insert(s, right));
        node->getRight()->setParent(node);
        if (this->high(node->getRight()) - this->high(node->getLeft()) == 2)
        {
            if (this->_ge_(*s, *node->getRight()->getSegment()))
                node = this->rr_leftRotation(node);
            else
                node = this->rl_doubleLeftRotation(node);
        }
    }
    return node;
}

/**
 * rotate the tree to the right
 * @param node
 * @return
 */
TreeNode* BST::ll_rightRotation(TreeNode* node)
{
    TreeNode* node_l = node->getLeft();

    node->setLeft(node_l->getRight());

    if (node_l->getRight())
        node_l->getRight()->setParent(node);

    node_l->setRight(node);
    node->setParent(node_l);

    return node_l;
}

/**
 * rotate the tree to the left
 * @param node
 * @return
 */
TreeNode* BST::rr_leftRotation(TreeNode* node)
{
    TreeNode* node_r = node->getRight();

    node->setRight(node_r->getLeft());

    if (node_r->getLeft())
        node_r->getLeft()->setParent(node);

    node_r->setLeft(node);
    node->setParent(node_r);

    return node_r;
}

/**
 * rotate the node subtree, first to the right than to the left
 * @param node
 * @return
 */
TreeNode* BST::rl_doubleLeftRotation(TreeNode* node)
{
    node->setRight(this->ll_rightRotation(node->getRight()));
    return this->rr_leftRotation(node);
}

/**
 * rotate the tree first to the left, than to the right
 * @param node
 */
TreeNode* BST::lr_doubleRightRotation(TreeNode* node)
{
    node->setLeft(this->rr_leftRotation(node->getLeft()));
    return this->ll_rightRotation(node);
}

//
//bool BST::balanceFactor(Shapes2D::Segment2d s) {
//    TreeNode* toCheck = search(s);
//    if (!s) return false;
//
//    int left = high(toCheck->getLeft());
//    int right = high(toCheck->getRight());
//    if (left - right == 1 || left - right == -1 || left - right == 0)
//        return true;
//    else
//        return false;
//}

/**
 * set the size of the tree to s
 */
 void BST::setSize(int s) {
    size = s;
}

/**
 * return the size of the tree
 */
int BST::getSize() {
    return size;
}

//inline void BST::successor(Shapes2D::Segment2d val) {
//    levelOrder(search(val));
//}

//void BST::mirror(TreeNode* tmp1, BST* tmp2) {
//    if (!tmp1) return;
//
//    TreeNode* node = new TreeNode(tmp1->getSegment());
//    if (tmp2->getRoot() == NULL) {
//        tmp2->setRoot(node);
//    }
//    else {
//        TreeNode* temp = tmp2->getRoot();
//        while (temp != NULL) {
//            if (_ge_(temp->getSegment(), tmp1->getSegment())) {
//                if (temp->getRight() == NULL)
//                {
//                    temp->setRight(node);
//                    node->setParent(temp);
//                    break;
//                }
//                temp = temp->getRight();
//            }
//            else if (_le_(temp->getSegment(), tmp1->getSegment())) {
//                if (temp->getLeft() == NULL)
//                {
//                    temp->setLeft(node);
//                    node->setParent(temp);
//                    break;
//                }
//                temp = temp->getLeft();
//            }
//            else
//            {
//                break;
//            }
//        }
//    }
//
//    mirror(tmp1->getLeft(), tmp2);
//    mirror(tmp1->getRight(), tmp2);
//}

//
//inline void BST::predecessor(Shapes2D::Segment2d val) {
//    TreeNode* tmp = search(val);
//    do {
//        std::cout << tmp->getParent()->getSegment() << " ";
//        tmp = tmp->getParent();
//    } while (tmp->getParent() != NULL);
//}

/**
 * return the parent segment if the segment given.
 * assume that val is indeed in the tree
 * @param val
 * @return
 */
Shapes2D::Segment2d BST::parentDisplay(Shapes2D::Segment2d val)
{
    TreeNode* tmp = searchSegment(val);
    return *tmp->getParent()->getSegment();
}

/**
 * function responsible from calculating the height of the node in the tree
 * @param tmp the corresponded subtree root
 * @return integer value
 */
int BST::high(TreeNode* tmp)
{
    if (tmp == NULL)	return -1;

    int lft = this->high(tmp->getLeft());
    int rht = this->high(tmp->getRight());
    if (lft < rht)
    {
        return rht + 1;
    }
    return lft + 1;
}

/**
 * remove a segment from the tree
 * first we look for the relevant pointer, and the delete it.
 * @param toFind segment to be deleted
 * @return true iff segment deleted successfully
 */
bool BST::removeSegment(Shapes2D::Segment2d toFind)
{
    return remove(searchSegment(toFind));
}

/**
 * function is responsible for removing a node from the tree
 * @param toDel the node pointer which need to be deleted
 * @return true iff item was successfully deleted
 */
bool BST::remove(TreeNode* toDel)
{
    if (!toDel)
        return false;

    // Case 1: leaf node.
    if (!toDel->getLeft() && !toDel->getRight())
    {
        if (this->root == toDel)
            this->root = NULL;
        else if (toDel->getParent()->getLeft() == toDel)
            toDel->getParent()->setLeft(NULL);
        else
            toDel->getParent()->setRight(NULL);
    }

    // Case 2: both children
    else if (toDel->getLeft() && toDel->getRight())
    {
        TreeNode* maxNode = this->maxx(toDel->getLeft());
        Shapes2D::Segment2d v = *maxNode->getSegment();
        this->remove(maxNode);
        toDel->setSegment(v);
        toDel = NULL;
    }

        // Case 3: one child
    else if (toDel->getLeft() || toDel->getRight())
    {
        TreeNode* toShift = toDel->getLeft() ? toDel->getLeft() : toDel->getRight();

        if (this->root == toDel)
            this->root = toShift;

        TreeNode* futureParent = toDel->getParent();

        if (futureParent)
        {
            if (futureParent->getLeft() == toDel)
                futureParent->setLeft(toShift);
            else if (futureParent->getRight() == toDel)
                futureParent->setRight(toShift);
        }
        else
            toShift->setParent(NULL);
    }
    return true;
}

/**
 * setting the root to another pointer
 */
void BST::setRoot(TreeNode* r) {
    this->root = r;
}

/**
 * return the tree root pointer
 */
TreeNode* BST::getRoot()
{
    return this->root;
}

/**
 * search element with segment s
 * @param s segment to look for
 * @return TreeNode pointer
 */
TreeNode* BST::searchSegment(Shapes2D::Segment2d s)
{
    if (this->root != NULL)
    {
        TreeNode* temp = this->root;
        while (temp != NULL)
        { /* search in the subtree temp */
            if (this->_le_(*temp->getSegment(), s))
            {
                if (temp->getRight() == NULL)
                {
                    return NULL;
                }
                temp = temp->getRight();
            }
            else if (this->_ge_(*temp->getSegment(), s))
            {
                if (temp->getLeft() == NULL)
                {
                    return NULL;
                }
                temp = temp->getLeft();
            }
            else
            {
                return temp;
            }
        }
    }
    return NULL;
}

/**
 * search the closest tree node to the given point
 * @param p is a point we are interset in
 * @return TreeNode pointer
 */
TreeNode* BST::searchPoint(Shapes2D::Point2d *p)
{
    if (this->root != NULL)
    {
        TreeNode* last;
        TreeNode* temp = this->root;
        while (temp != NULL)
        { /* search in the subtree temp */
            last = temp;
            if( temp->getSegment()->getSlope() == 0 )
            {
                if (p->getX() < temp->getSegment()->getUpper()->getX())
                    temp = temp->getLeft();
                else if (p->getX() > temp->getSegment()->getLower()->getX())
                    temp = temp->getRight();
                else
                    return temp;
                continue;
            }
            int pred;
            pred = temp->getSegment()->getUpper()->oriePred(temp->getSegment()->getLower(), p);

            if ( pred < 0 )
                temp = temp->getRight();
            else if ( pred > 0 )
                temp = temp->getLeft();
            else
                return temp;
        }
        return last;
    }
    return NULL;
}

/**
 * return the maximum value segment in the tree
 * @param tmp root
 * @return Segment value
 */
TreeNode* BST::maxx(TreeNode* tmp)
{
    while (tmp != NULL) /* walk on the right path */
    {
        if (tmp->getRight() == NULL)
        {
            return tmp;
        }
        tmp = tmp->getRight();
    }
}

/**
 * return the minimum value segment in the tree
 * @param tmp root
 * @return Segment value
 */
TreeNode* BST::minn(TreeNode* tmp)
{
    while (tmp != NULL)
    { /* walk on the left path */
        if (tmp->getLeft() == NULL)
        {
            return tmp;
        }
        tmp = tmp->getLeft();
    }
}

/**
 * make an in-order walk on the tree elements, etc. left-son to root to right-son.
 * @param tmp tree root
 */
void BST::walkInOrder(TreeNode* tmp)
{
    if (tmp == NULL)
    {
        return;
    }

    this->walkInOrder(tmp->getLeft());
    std::cout << tmp->getSegment()->toStr();
    this->walkInOrder(tmp->getRight());
}

/**
 * make a pre-order walk on the tree elements, etc. root to left-son to right-son.
 * @param tmp tree root
 */
void BST::walkPreOrder(TreeNode* tmp)
{
    if (tmp == NULL)
    {
        return;
    }

    std::cout << tmp->getSegment()->toStr();
    this->walkPreOrder(tmp->getLeft());
    this->walkPreOrder(tmp->getRight());
}

/**
 * make a post-order walk on the tree elements, etc. left-son to right-son to root.
 * @param tmp tree root
 */
void BST::walkPostOrder(TreeNode* tmp)
{
    if (tmp == NULL)
    {
        return;
    }

    this->walkPostOrder(tmp->getLeft());
    this->walkPostOrder(tmp->getRight());
    std::cout << tmp->getSegment()->toStr();
}


BST::~BST() {}

/**
 * this function is responsible for comparing between two given segments
 * etc. function decides which segment lies to the left, w.r.t the height parameter of the tree
 * @return true iff v lies to the left of u
 */
bool BST::_le_(Shapes2D::Segment2d v, Shapes2D::Segment2d u)
{
    Line2d *a_line = new Line2d(v.getTarget(), v.getOrigin());
    Line2d *b_line = new Line2d(u.getTarget(), u.getOrigin());
    std::pair<bool, double> a_x = a_line->getX_fromY(height.getY());
    std::pair<bool, double> b_x = b_line->getX_fromY(height.getY());

    if(a_x.first && b_x.first)
    {
        if (std::abs(a_x.second - b_x.second) <= eps)
        {
            return a_line->getX_fromY(height.getY() - 0.001).second < b_line->getX_fromY(height.getY() - 0.001).second;
        }
        return a_x.second < b_x.second;
    }
    else if (!a_x.first)
    {
        if (v.getUpper()->getX() <= b_x.second && u.getLower()->getX() >= b_x.second)
            return height.getX() < b_x.second;
        else return b_x.second > v.getLower()->getX();
    }
    else
    {
        if (u.getUpper()->getX() <= a_x.second && u.getLower()->getX() >= a_x.second)
            return height.getX() < a_x.second;
        else
            return a_x.second > u.getLower()->getX();
    }
}

/**
 * this function is responsible for comparing between two given segments
 * etc. function decides which segment lies to the right, w.r.t the height parameter of the tree
 * @return true iff v lies to the right of u
 */
bool BST::_ge_(Shapes2D::Segment2d v, Shapes2D::Segment2d u)
{
    Line2d *a_line = new Line2d(v.getTarget(), v.getOrigin());
    Line2d *b_line = new Line2d(u.getTarget(), u.getOrigin());
    std::pair<bool, double> a_x = a_line->getX_fromY(height.getY());
    std::pair<bool, double> b_x = b_line->getX_fromY(height.getY());

    if(a_x.first && b_x.first)
    {
        if (std::abs(a_x.second - b_x.second) <= eps)
        {
            return a_line->getX_fromY(height.getY() - 0.001).second > b_line->getX_fromY(height.getY() - 0.001).second;
        }
        return a_x.second > b_x.second;
    }
    else if (!a_x.first)
    {
        if (v.getUpper()->getX() <= b_x.second && u.getLower()->getX() >= b_x.second)
            return height.getX() > b_x.second;
        else
            return b_x.second < v.getLower()->getX();
    }
    else
    {
        if (u.getUpper()->getX() <= a_x.second && u.getLower()->getX() >= a_x.second)
            return height.getX() > a_x.second;
        else
            return a_x.second < u.getLower()->getX();
    }
}

void BST::setHeight(Shapes2D::Point2d p)
{
    this->height = p;
}

TreeNode *BST::getPredecessor(TreeNode * node)
{
    /* base case */
    if (root == nullptr)
    {
        return nullptr;
    }
    TreeNode* prec = nullptr;
    while (1)
    {
        // if the given key is less than the root node, visit the left subtree
        if (this->_le_(*node->getSegment(), *root->getSegment()))
            root = root->getLeft();
        // if the given key is more than the root node, visit the right subtree
        else if (this->_ge_(*node->getSegment(), *root->getSegment()))
        {
            // update predecessor to the current node before visiting
            // right subtree
            prec = root;
            root = root->getRight();
        }
        // if a node with the desired value is found, the predecessor is the maximum
        // value node in its left subtree (if any)
        else
        {
            if (root->getLeft() != NULL)
            {
                prec = this->maxx(root->getLeft());
            }
            break;
        }
        // if the key doesn't exist in the binary tree, return previous greater node
        if (root == NULL)
        {
            return prec;
        }
    }
    // return predecessor, if any
    return prec;
}

TreeNode *BST::getSuccessor(TreeNode * node) {
    // base case
    if (root == nullptr)
    {
        return nullptr;
    }
    TreeNode* succ = nullptr;
    while (1)
    {
        // if the given key is less than the root node, visit the left subtree
        if (this->_le_(*node->getSegment(), *root->getSegment()))
        {
            // update successor to the current node before visiting left subtree
            succ = root;
            root = root->getLeft();
        }
        // if the given key is more than the root node, visit the right subtree
        else if (this->_ge_(*node->getSegment(), *root->getSegment()))
        {
            root = root->getRight();
        }
        // if a node with the desired value is found, the successor is the minimum
        // value node in its right subtree (if any)
        else
        {
            if (root->getRight() != NULL)
            {
                succ = this->minn(root->getRight());
            }
            break;
        }
        // if the key doesn't exist in the binary tree, return next greater node
        if (root == NULL)
        {
            return succ;
        }
    }
    // return successor, if any
    return succ;
}