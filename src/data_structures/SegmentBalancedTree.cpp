
#include "SegmentBalancedTree.h"

void SegmentBalancedTree::insert(const Shapes2D::Segment2d &s) {
    if (search(s) != nullptr) {
        return;
    }
    root = _insert_(root, s);
}

Node *SegmentBalancedTree::_insert_(Node *head, const Shapes2D::Segment2d &s) {
    if (head == nullptr) {
        size++;
        return new Node(s);
    }

    if (_le_(s, head->s)) {
        head->left = _insert_(head->left, s);
    } else if (_le_(head->s, s)) {
        head->right = _insert_(head->right, s);
    }

    head->height = 1 + std::max(_height_(head->left), _height_(head->right));

    int bal = _height_(head->left) - _height_(head->right);

    if (bal > 1) {
        if (_le_(s, head->left->s)) {
            return _rightRotation_(head);
        }
        head->left = _leftRotation_(head->left);
        return _rightRotation_(head);
    }

    if (bal < -1) {
        if (_le_(head->right->s, s)) {
            return _leftRotation_(head);
        }
        head->right = _rightRotation_(head->right);
        return _leftRotation_(head);
    }

    return head;
}


void SegmentBalancedTree::remove(const Shapes2D::Segment2d &s) {
    root = _remove_(root, s);
}

Node *SegmentBalancedTree::_remove_(Node *head, const Shapes2D::Segment2d &s) {
    if (head == nullptr) {
        return nullptr;
    }

    if (_le_(s, head->s)) {
        head->left = _remove_(head->left, s);
    } else if (_le_(head->s, s)) {
        head->right = _remove_(head->right, s);
    } else {
        if (head->right == nullptr) {
            Node *l = head->left;
            delete head;
            return l;
        }
        if (head->left == nullptr) {
            Node *r = head->right;
            delete head;
            return r;
        }
        Node *successor = head->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        head->s = successor->s;
        head->right = _remove_(head->right, successor->s);
    }

    if (head == nullptr) {
        return head;
    }

    head->height = 1 + std::max(_height_(head->left), _height_(head->right));

    int bal = _height_(head->left) - _height_(head->right);

    if (bal > 1) {
        if (_height_(head->left) >= _height_(head->right)) {
            return _rightRotation_(head);
        }
        head->left = _leftRotation_(head->left);
        return _rightRotation_(head);
    }

    if (bal < -1) {
        if (_height_(head->right) >= _height_(head->left)) {
            return _leftRotation_(head);
        }
        head->right = _rightRotation_(head->right);
        return _leftRotation_(head);
    }

    return head;
}


Node *SegmentBalancedTree::search(const Shapes2D::Segment2d &s) {
    return _search_(root, s);
}

Node *SegmentBalancedTree::_search_(Node *head, const Shapes2D::Segment2d &s) {
    if (head == nullptr) {
        return nullptr;
    }

    if (head->s == s) {
        return head;
    }

    if (_le_(s, head->s)) {
        return _search_(head->left, s);
    }
    return _search_(head->right, s);
}

Node *SegmentBalancedTree::search_p(const Shapes2D::Point2d &p) {
    return _search_p_(root, p);
}

Node * SegmentBalancedTree::_search_p_(Node * head, const Shapes2D::Point2d &p)
{
    if (head == nullptr) {
        return nullptr;
    }

    Shapes2D::Segment2d head_s = head->s;
    if (head_s.containPoint(p)) {
        return head;
    }

    Line2d v_l(head_s.getLower(), head_s.getUpper());
    double v_x = v_l.getX_fromY(sweepLine->getY()).second;

    Node *res;

    if (p.getX() < v_x) {
        res = _search_p_(head->left, p);
        return res != nullptr ? res : head;
    } else {
        res = _search_p_(head->right, p);
        return res != nullptr ? res : head;
    }
}

void SegmentBalancedTree::walkInOrder() {
    _walkInOrder_(root);
}

void SegmentBalancedTree::_walkInOrder_(Node *head) {
    if (head == nullptr) return;
    _walkInOrder_(head->left);
    std::cout << head->s.toStr();
    _walkInOrder_(head->right);
}

int SegmentBalancedTree::_height_(Node *head) {
    return (head == nullptr) ? 0 : head->height;
}

Node *SegmentBalancedTree::_rightRotation_(Node *head) {
    Node *new_head = head->left;
    head->left = new_head->right;
    new_head->right = head;
    head->height = 1 + std::max(_height_(head->left), _height_(head->right));
    new_head->height = 1 + std::max(_height_(new_head->left), _height_(new_head->right));
    return new_head;
}

Node *SegmentBalancedTree::_leftRotation_(Node *head) {
    Node *new_head = head->right;
    head->right = new_head->left;
    new_head->left = head;
    head->height = 1 + std::max(_height_(head->left), _height_(head->right));
    new_head->height = 1 + std::max(_height_(new_head->left), _height_(new_head->right));
    return new_head;
}

bool SegmentBalancedTree::_le_(const Shapes2D::Segment2d& v, const Shapes2D::Segment2d& u) const {
    Line2d v_l(v.getLower(), v.getUpper());
    double v_x = v_l.isHorizon() ? sweepLine->getX() : v_l.getX_fromY(sweepLine->getY()).second;

    Line2d u_l(u.getLower(), u.getUpper());
    double u_x = u_l.isHorizon() ? sweepLine->getX() : u_l.getX_fromY(sweepLine->getY()).second;

    if (std::abs(v_x - u_x) > eps) {
        return v_x < u_x;
    }

    Shapes2D::Point2d u_lower = (u.getLower().getY() == u.getUpper().getY()) ? u.getUpper() : u.getLower();
    Shapes2D::Point2d v_lower = (v.getLower().getY() == v.getUpper().getY()) ? v.getUpper() : v.getLower();

    return sweepLine->oriePred(u_lower, v_lower) < 0;
}


Node *SegmentBalancedTree::maxx() const {
    if (root == nullptr) return nullptr;
    Node *tmp = root;
    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    return tmp;
}

Node *SegmentBalancedTree::minn() const {
    if (root == nullptr) return nullptr;
    Node *tmp = root;
    while (tmp->left != nullptr) {
        tmp = tmp->left;
    }
    return tmp;
}

Node *SegmentBalancedTree::getPred(Node *x) {
    if (x == minn()) return nullptr;

    std::vector<Node *> nodes;
    _items_(&nodes, root);

    for (size_t i = 0; i < nodes.size() - 1; i++) {
        if (nodes[i + 1]->s == x->s) {
            return nodes[i];
        }
    }
    return nullptr;
}

Node *SegmentBalancedTree::getSucc(Node *x) {
    if (x == maxx()) return nullptr;

    std::vector<Node *> nodes;
    _items_(&nodes, root);

    for (size_t i = 1; i < nodes.size(); i++) {
        if (nodes[i - 1]->s == x->s) {
            return nodes[i];
        }
    }
    return nullptr;
}

void SegmentBalancedTree::_items_(std::vector<Node *> *res, Node *head) {
    if (head == nullptr) return;
    _items_(res, head->left);
    res->push_back(head);
    _items_(res, head->right);
}

SegmentBalancedTree::SegmentBalancedTree()
    : root(nullptr), size(0), sweepLine(new Shapes2D::Point2d(DBL_MAX, DBL_MAX)) {}

SegmentBalancedTree::~SegmentBalancedTree() {
    _deleteTree_(root);
    delete sweepLine;
}

void SegmentBalancedTree::_deleteTree_(Node *node) {
    if (node == nullptr) return;
    _deleteTree_(node->left);
    _deleteTree_(node->right);
    delete node;
}