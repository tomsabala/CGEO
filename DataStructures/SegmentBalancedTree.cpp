
#include "SegmentBalancedTree.h"

void SegmentBalancedTree::insert(Shapes2D::Segment2d *s)
{
    if (search(s) != nullptr) /* keys are unique */
        return;
    root=_insert_(root, s);
}

Node * SegmentBalancedTree::_insert_(Node * head, Shapes2D::Segment2d *s)
{

    if(head==NULL) /* subtree is empty */
    {
        size++;
        Node * tmp = new Node(s);
        return tmp;
    }

    if(_le_(s, head->s)) /* s need to be inserted to left side */
        head->left = _insert_(head->left, s);

    else if(_le_(head->s, s))  /* s need to be inserted to right side */
        head->right = _insert_(head->right, s);

    /* update height of subtree */
    head->height = 1 + std::max(_height_(head->left), _height_(head->right));

    /* balance factor */
    int bal = _height_(head->left) - _height_(head->right);

    if(bal>1)
    {
        if(_le_(s, head->left->s))
            return _rightRotation_(head);
        else
        {
            head->left = _leftRotation_(head->left);
            return _rightRotation_(head);
        }
    }
    else if(bal<-1)
    {
        if(_le_(head->right->s, s))
            return _leftRotation_(head);
        else
        {
            head->right = _rightRotation_(head->right);
            return _leftRotation_(head);
        }
    }
    return head;
}


void SegmentBalancedTree::remove(Shapes2D::Segment2d *s){
    root=_remove_(root, s);
}

Node * SegmentBalancedTree::_remove_(Node * head, Shapes2D::Segment2d *s){
    if(head==NULL)  /* s not found */
        return NULL;

    if(_le_(s, head->s)) /* s is on the left side if subtree */
    {
        head->left = _remove_(head->left, s);

    }
    else if(_le_(head->s, s)) /* s is on the right side if subtree */
    {
        head->right = _remove_(head->right, s);
    }
    else
    { /* s is head->s */
        Node * r = head->right;
        if(head->right==NULL)
        {
            Node * l = head->left;
            delete(head);
            head = l;
        }
        else if(head->left==NULL)
        {
            delete(head);
            head = r;
        }
        else
        {
            while(r->left!=NULL)
                r = r->left;

            head->s = r->s;
            head->right = _remove_(head->right, r->s);
        }
    }

    if(head==NULL)
        return head;

    head->height = 1 + std::max(_height_(head->left), _height_(head->right));

    int bal = _height_(head->left) - _height_(head->right);
    if(bal>1)
    {
        if(_height_(head->left) >= _height_(head->right))
            return _rightRotation_(head);
        else
        {
            head->left = _leftRotation_(head->left);
            return _rightRotation_(head);
        }
    }
    else if(bal < -1)
    {
        if(_height_(head->right) >= _height_(head->left))
            return _leftRotation_(head);
        else
        {
            head->right = _rightRotation_(head->right);
            return _leftRotation_(head);
        }
    }
    return head;
}


Node * SegmentBalancedTree::search(Shapes2D::Segment2d *s){
    return _search_(root, s);
}

Node * SegmentBalancedTree::_search_(Node * head, Shapes2D::Segment2d *s){
    if(head == NULL)
        return NULL;

    Shapes2D::Segment2d *head_s = head->s;
    if(head_s->_eq_(s))
        return head;

    if(_le_(s, head_s))
        return _search_(head->left, s);

    else
        return _search_(head->right, s);

}

Node * SegmentBalancedTree::search_p(Shapes2D::Point2d *p)
{
    return _search_p_(root, p);
}

Node * SegmentBalancedTree::_search_p_(Node * head, Shapes2D::Point2d *p)
{
    if(head == NULL)
        return NULL;

    Shapes2D::Segment2d *head_s = head->s;
    if (head_s->containPoint(*p))
        return head;

    Line2d *v_l = new Line2d(head_s->getLower(), head_s->getUpper());
    double v_x = v_l->getX_fromY(sweepLine->getY()).second;

    Node *res;

    if (p->getX() < v_x)
    {
        res = _search_p_(head->left, p);
        if (res == NULL)
            return head;
        return res;
    }
    else
    {
        res = _search_p_(head->right, p);
        if (res == NULL)
            return head;
        return res;
    }
}

void SegmentBalancedTree::walkInOrder(){
    _walkInOrder_(root);
}

void SegmentBalancedTree::_walkInOrder_(Node * head)
{
    if (head == nullptr)
        return;
    _walkInOrder_(head->left);
    std::cout<<head->s->toStr();
    _walkInOrder_(head->right);

}

int SegmentBalancedTree::_height_(Node * head){
    if(head==NULL) return 0;
    return head->height;
}

Node * SegmentBalancedTree::_rightRotation_(Node * head)
{
    Node * new_head = head->left;
    head->left = new_head->right;
    new_head->right = head;
    head->height = 1 + std::max(_height_(head->left), _height_(head->right));
    new_head->height = 1 + std::max(_height_(new_head->left), _height_(new_head->right));
    return new_head;
}

Node * SegmentBalancedTree::_leftRotation_(Node * head)
{
    Node * new_head = head->right;
    head->right = new_head->left;
    new_head->left = head;
    head->height = 1 + std::max(_height_(head->left), _height_(head->right));
    new_head->height = 1 + std::max(_height_(new_head->left), _height_(new_head->right));
    return new_head;
}

bool SegmentBalancedTree::_le_(Shapes2D::Segment2d *v, Shapes2D::Segment2d *u) {
    Line2d *v_l = new Line2d(v->getLower(), v->getUpper());
    double v_x = (v_l->isHorizon()) ? sweepLine->getX() : v_l->getX_fromY(sweepLine->getY()).second;

    Line2d *u_l = new Line2d(u->getLower(), u->getUpper());
    double u_x = (u_l->isHorizon()) ? sweepLine->getX() : u_l->getX_fromY(sweepLine->getY()).second;

    if (std::abs(v_x - u_x) > eps)
        return v_x < u_x;

    Shapes2D::Point2d *u_lower, *v_lower;
    if (u->getLower()->getY() == u->getUpper()->getY())
        u_lower = u->getUpper();
    else
        u_lower = u->getLower();

    if (v->getLower()->getY() == v->getUpper()->getY())
        v_lower = v->getUpper();
    else
        v_lower = v->getLower();

    return sweepLine->oriePred(u_lower, v_lower) < 0;
}


Node *SegmentBalancedTree::maxx() {
    if (root == nullptr)
        return nullptr;
    Node *tmp = root;
    while(tmp->right != nullptr)
        tmp = tmp->right;
    return tmp;
}

Node *SegmentBalancedTree::minn() {
    if (root == nullptr)
        return nullptr;
    Node *tmp = root;
    while(tmp->left != nullptr)
        tmp = tmp->left;
    return tmp;
}

Node* SegmentBalancedTree::getPred(Node *x){
    if (x == minn())
        return nullptr; // in this case x has no predecessor


    std::vector<Node *> nodes;
    _items_(&nodes, root);


    for (int i=0; i<nodes.size()-1; i++)
    {
        if (nodes[i+1]->s->_eq_(x->s))
            return nodes[i];
    }


    return nullptr;
}

Node* SegmentBalancedTree::getSucc(Node *x){
    if (x == maxx())
        return nullptr; // in this case x has no predecessor


    std::vector<Node *> nodes;
    _items_(&nodes, root);

    for (int i=1; i<nodes.size(); i++)
    {
        if (nodes[i-1]->s->_eq_(x->s))
            return nodes[i];
    }

    return nullptr;
}

void SegmentBalancedTree::_items_(std::vector<Node *> *res, Node * head) {
    if (head == nullptr)
        return;

    _items_(res, head->left);
    res->push_back(head);
    _items_(res, head->right);
}
