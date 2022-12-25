
#include <algorithm>
#include <iostream>
#include "Polygon.h"


/**
 * empty constructor
 * init vertices to be an empty vector
 */
Shapes2D::Polygon::Polygon() {
    this->vertices = std::vector<Point2d>();
}

/**
 * standard constructor
 * init vertices to be v
 *
 * @param v is a vector of type Point2d
 */
Shapes2D::Polygon::Polygon(const std::vector<Point2d> &v) {
    this->vertices.insert(this->vertices.begin(), v.begin(), v.end());
}

/**
 * insert new Point to polygon as the last vertex
 * @param p new Point2d object
 */
void Shapes2D::Polygon::insert(const Shapes2D::Point2d &p) {
    this->vertices.push_back(p);
}

/**
 * insert new Point to polygon in a specific index
 * @param p new Point2d object
 * @param i index value {if i >= vertices.size(), then, p is inserted as last vertex}
 */
void Shapes2D::Polygon::insert(const Shapes2D::Point2d &p, int i) {
    if (i >= this->vertices.size()) this->insert(p);
    else this->vertices.insert(this->vertices.begin() + i, p);
}

/**
 * get Point by index
 * @param i index to be picked {if i >= vertices.size(), then, last vertex is picked}
 */
Shapes2D::Point2d* Shapes2D::Polygon::getByIndex(int i) {
    if (i >= this->vertices.size()) return &this->vertices.back();
    else if (i < 0) return nullptr;
    return &this->vertices.at(i);
}

/**
 * get lowest point w.r.t lexicographic order
 */
Shapes2D::Point2d *Shapes2D::Polygon::getLexMin() {
    if (this->getSize() == 0) return nullptr;
    auto *res = (Point2d*) malloc(sizeof(Point2d));
    if (!res) {
        throw (Exception2D("malloc failed\n"));
    }
    *res = *this->getByIndex(this->getLexMin_index());
    return res;
}

/**
 * get lowest point index w.r.t lexicographic order
 */
int Shapes2D::Polygon::getLexMin_index() {
    if (this->getSize() == 0) return -1;
    int res = 0;
    for( int i=0; i<this->getSize(); i++) {
        if (this->getByIndex(i)->_lt_(*this->getByIndex(res))) {
            res = i;
        }
    }
    return res;
}

/**
 * get highest point index w.r.t lexicographic order
 */
Shapes2D::Point2d *Shapes2D::Polygon::getLexMax() {
    if (this->getSize() == 0) return nullptr;
    auto *res = (Point2d*) malloc(sizeof(Point2d));
    if (!res) {
        throw (Exception2D("malloc failed\n"));
    }
    *res = *this->getByIndex(this->getLexMax_index());
    return res;
}

/**
 * get highest point index w.r.t lexicographic order
 */
int Shapes2D::Polygon::getLexMax_index() {
    if (this->getSize() == 0) return -1;
    int res = 0;
    for(int i=0; i<this->getSize(); i++) {
        if (this->getByIndex(res)->_lt_(*this->getByIndex(i))){
            res = i;
        }
    }
    return res;
}

/**
 * get lexicographic order of all vertices
 * @return sorted vector of type Point2d
 */
std::vector<Shapes2D::Point2d> Shapes2D::Polygon::lexOrder() {
    std::vector<Shapes2D::Point2d> res(this->vertices.begin(), this->vertices.end());
    std::sort(res.begin(), res.end(), [ ]( const Point2d& p, const Point2d& q )
    {
        return p.getY() < q.getY() || (p.getY() == q.getY() && p.getX() < q.getX());
    });
    return res;
}

/**
 * get vector of edges by order
 * @return vector of type Segment2d
 */
std::vector<Shapes2D::Segment2d> Shapes2D::Polygon::getEdges() {
    std::vector<Shapes2D::Segment2d> res;
    for(int i=0; i<this->getSize(); i++) {
        Segment2d* s;
        if (i == this->getSize()-1)
            s = new Segment2d(&this->vertices.back(), &this->vertices.front());
        else
            s = new Segment2d(this->getByIndex(i), this->getByIndex(i+1));
        res.push_back(*s);
    }

    return res;
}

/**
 * @return polygon size aka number of vertices
 */
int Shapes2D::Polygon::getSize() {
    return (int)this->vertices.size();
}

/**
 * check whether polygon is convex
 * @return boolean value
 */
bool Shapes2D::Polygon::isConvex() {
    int n = this->getSize();
    if (n <= 2) return true;
    bool step, sign = this->getByIndex(0)->oriePred(this->getByIndex(1), this->getByIndex(2)) > 0;
    for(int i=0; i<n; i++) {
        step = this->getByIndex(i%n)->oriePred(this->getByIndex((i+1)%n), this->getByIndex((i+2)%n)) > 0;
        if (step != sign) {
            return false;
        }
    }
    return true;
}

/**
 * check whether polygon is y-monotone
 * @return boolean value
 */
bool Shapes2D::Polygon::isY_Monotone() {
    int n = this->getSize();
    if (n==0) return true;

    /* highest and lowest points indices */
    int h = this->getLexMax_index();
    int l = this->getLexMin_index();

    /* check for inner-cusps from h to l */
    int curr = h;
    while(curr % n != l) {
        if (this->isInnerCusp(curr%n)) return false;
        curr++;
    }

    /* check for inner cusps from l to h */
    curr = l;
    while(curr % n != h) {
        if (this->isInnerCusp(curr%n)) return false;
        curr++;
    }

    return true; /* no inner-cusps iff poly. is y-monotone */
}

bool Shapes2D::Polygon::isInnerCusp(int i) {
    int n = this->getSize();
    double prev_y = this->getByIndex((i-1)%n)->getY();
    double next_y = this->getByIndex((i+1)%n)->getY();
    double curr_y = this->getByIndex(i)->getY();

    return (prev_y > curr_y && next_y > curr_y) || (prev_y < curr_y && next_y < curr_y);
}

/**
 * @return vector of all vertices
 */
std::vector<Shapes2D::Point2d> Shapes2D::Polygon::getVertices() {
    return this->vertices;
}

/**
 * find right most Point in the polygon
 * @return Point2d object vertex
 */
Shapes2D::Point2d *Shapes2D::Polygon::getRightMost() {
    if (this->getSize() == 0) return nullptr;
    auto *res = (Point2d*) malloc(sizeof(Point2d));
    if (!res) {
        throw (Exception2D("malloc failed\n"));
    }
    *res = *this->getByIndex(this->getRightMost_index());
    return res;
}

/**
 * find right most Point index in the polygon
 * @return Point2d object vertex
 */
int Shapes2D::Polygon::getRightMost_index() {
    int res = 0;
    for(int i=1; i<this->getSize(); i++){
        if(this->getByIndex(res)->getX() < this->getByIndex(i)->getX())
            res = i;
    }

    return res;
}

/**
 * find left most Point in the polygon
 * @return Point2d object vertex
 */
Shapes2D::Point2d *Shapes2D::Polygon::getLeftMost() {
    if (this->getSize() == 0) return nullptr;
    auto *res = (Point2d*) malloc(sizeof(Point2d));
    if (!res) {
        throw (Exception2D("malloc failed\n"));
    }
    *res = *this->getByIndex(this->getLeftMost_index());
    return res;
}

/**
 * find left most Point index in the polygon
 * @return Point2d object vertex
 */
int Shapes2D::Polygon::getLeftMost_index() {
    int res = 0;
    for(int i=1; i<this->getSize(); i++) {
        if(this->getByIndex(res)->getX() < this->getByIndex(i)->getX()) {
            res = i;
        }
    }
    return res;
}

bool Shapes2D::Polygon::isInPoly(Shapes2D::Point2d *p) {
    int res = 0;
    std::vector<Segment2d> edges = this->getEdges();

    for(Segment2d e : edges)
    {
        if (e.getUpper()->getY() > p->getY() && e.getLower()->getY() < p->getY())
        {
            if(e.getLower()->oriePred(e.getUpper(), p) > 0)
                res = !res;
        }
    }

    return res;
}





