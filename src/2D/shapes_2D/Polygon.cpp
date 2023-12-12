
#include <algorithm>
#include "Polygon.h"


/**
 * empty constructor
 * init vertices to be an empty vector
 */
Shapes2D::Polygon::Polygon() {
    vertices = std::vector<Point2d>();
}

/**
 * standard constructor
 * init vertices to be v
 *
 * @param v is a vector of type Point2d
 */
Shapes2D::Polygon::Polygon(const std::vector<Point2d> &v) {
    double edge_sum = 0;
    for (auto i=0; i<v.size(); i++)
    {
        auto& next = i == v.size()-1 ? v[0] : v[i+1];
        edge_sum += (next.getX() - v[i].getX()) * (next.getY() + v[i].getY());
    }
    if (edge_sum >= 0)
        vertices.insert(vertices.begin(), v.begin(), v.end());
    else
        vertices.insert(vertices.end(), v.rbegin(), v.rend());
}

Shapes2D::Polygon::Polygon(const std::vector<Point2d *> &v) {
    double edge_sum = 0;
    for (auto i=0; i<v.size(); i++)
    {
        auto& next = i == v.size()-1 ? *v[0] : *v[i+1];
        edge_sum += (next.getX() - v[i]->getX()) * (next.getY() + v[i]->getY());
    }
    if (edge_sum >= 0)
        for (auto i : v)
            vertices.push_back(*i);
    else
        for (auto i=v.size()-1; i>=0; i--)
            vertices.push_back(*v.at(i));
}

/**
 * insert new Point to polygon as the last vertex
 * @param p new Point2d object
 */
void Shapes2D::Polygon::insert(const Shapes2D::Point2d &p) {
    vertices.push_back(p);
}

/**
 * insert new Point to polygon in a specific index
 * @param p new Point2d object
 * @param i index value {if i >= vertices.size(), then, p is inserted as last vertex}
 */
void Shapes2D::Polygon::insert(const Shapes2D::Point2d &p, int i) {
    if (i >= vertices.size()) insert(p);
    else vertices.insert(vertices.begin() + i, p);
}

/**
 * get Point by index
 * @param i index to be picked {if i >= vertices.size(), then, last vertex is picked}
 */
Shapes2D::Point2d* Shapes2D::Polygon::getByIndex(int i) {
    if (i >= vertices.size()) return &vertices.back();
    else if (i < 0) return nullptr;
    return &vertices.at(i);
}

/**
 * get lowest point w.r.t lexicographic order
 */
Shapes2D::Point2d *Shapes2D::Polygon::getLexMin() {
    if (getSize() == 0) return nullptr;
    auto *res = (Point2d*) malloc(sizeof(Point2d));

    *res = *getByIndex(getLexMin_index());
    return res;
}

/**
 * get lowest point index w.r.t lexicographic order
 */
int Shapes2D::Polygon::getLexMin_index() {
    if (getSize() == 0) return -1;
    int res = 0;
    for( auto i=0; i<getSize(); i++)
        if (getByIndex(i) < getByIndex(res))
            res = i;
    return res;
}

/**
 * get highest point index w.r.t lexicographic order
 */
Shapes2D::Point2d *Shapes2D::Polygon::getLexMax() {
    if (getSize() == 0) return nullptr;
    auto *res = (Point2d*) malloc(sizeof(Point2d));

    *res = *getByIndex(getLexMax_index());
    return res;
}

/**
 * get highest point index w.r.t lexicographic order
 */
int Shapes2D::Polygon::getLexMax_index() {
    if (getSize() == 0) return -1;
    int res = 0;
    for(int i=0; i<getSize(); i++) {
        if (getByIndex(res) < getByIndex(i)){
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
    std::vector<Shapes2D::Point2d> res(vertices.begin(), vertices.end());
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
std::vector<Shapes2D::Segment2d *> Shapes2D::Polygon::getEdges() {
    std::vector<Shapes2D::Segment2d *> res;
    for(int i=0; i<getSize(); i++) {
        Segment2d* s;
        if (i == getSize()-1)
            s = new Segment2d(vertices.back(), vertices.front());
        else
            s = new Segment2d(*getByIndex(i), *getByIndex(i+1));
        res.push_back(s);
    }

    return res;
}

/**
 * @return polygon size aka number of vertices
 */
int Shapes2D::Polygon::getSize() {
    return (int)vertices.size();
}

/**
 * check whether polygon is convex
 * @return boolean value
 */
bool Shapes2D::Polygon::isConvex() {
    int n = getSize();
    if (n <= 2) return true;
    bool step, sign = getByIndex(0)->oriePred(*getByIndex(1), *getByIndex(2)) > 0;
    for(int i=0; i<n; i++) {
        step = getByIndex(i%n)->oriePred(*getByIndex((i+1)%n), *getByIndex((i+2)%n)) > 0;
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
    int n = getSize();
    if (n==0) return true;

    /* highest and lowest points indices */
    int h = getLexMax_index();
    int l = getLexMin_index();

    /* check for inner-cusps from h to l */
    int curr = h;
    while(curr % n != l) {
        if (isInnerCusp(curr%n)) return false;
        curr++;
    }

    /* check for inner cusps from l to h */
    curr = l;
    while(curr % n != h) {
        if (isInnerCusp(curr%n)) return false;
        curr++;
    }

    return true; /* no inner-cusps iff poly. is y-monotone */
}

bool Shapes2D::Polygon::isInnerCusp(int i) {
    int n = getSize();
    double prev_y = getByIndex(i == 0 ? n-1 : i-1)->getY();
    double next_y = getByIndex((i+1)%n)->getY();
    double curr_y = getByIndex(i)->getY();

    return (prev_y > curr_y && next_y > curr_y) || (prev_y < curr_y && next_y < curr_y);
}


bool Shapes2D::Polygon::anyInnerCusp(int i, bool (*func)(Point2d *, Point2d *, Point2d *))
{
    int n = getSize();

    int pred = i == 0 ? n-1 : i-1;
    int succ = i == n-1 ? 0 : i+1;

    return func(getByIndex(pred), getByIndex(i), getByIndex(succ));
}


/**
 * @return vector of all vertices
 */
std::vector<Shapes2D::Point2d> Shapes2D::Polygon::getVertices() {
    return vertices;
}

/**
 * find right most Point in the polygon
 * @return Point2d object vertex
 */
Shapes2D::Point2d *Shapes2D::Polygon::getRightMost() {
    if (getSize() == 0) return nullptr;
    auto *res = (Point2d*) malloc(sizeof(Point2d));

    *res = *getByIndex(getRightMost_index());
    return res;
}

/**
 * find right most Point index in the polygon
 * @return Point2d object vertex
 */
int Shapes2D::Polygon::getRightMost_index() {
    int res = 0;
    for(int i=1; i<getSize(); i++){
        if(getByIndex(res)->getX() < getByIndex(i)->getX())
            res = i;
    }

    return res;
}

/**
 * find left most Point in the polygon
 * @return Point2d object vertex
 */
Shapes2D::Point2d *Shapes2D::Polygon::getLeftMost() {
    if (getSize() == 0) return nullptr;
    auto *res = (Point2d*) malloc(sizeof(Point2d));

    *res = *getByIndex(getLeftMost_index());
    return res;
}

/**
 * find left most Point index in the polygon
 * @return Point2d object vertex
 */
int Shapes2D::Polygon::getLeftMost_index() {
    int res = 0;
    for(int i=1; i<getSize(); i++) {
        if(getByIndex(res)->getX() < getByIndex(i)->getX()) {
            res = i;
        }
    }
    return res;
}

/**
 * this function checks whether a given point is inside polygon
 * assuming polygon is a simple polygon
 * @param p 2d point
 * @return true iff point is in interior of polygon
 */
bool Shapes2D::Polygon::isInPoly(Shapes2D::Point2d *p) {
    int res = 0;
    std::vector<Segment2d *> edges = getEdges();

    for(const Segment2d *e : edges)
    {
        if (e->getUpper().getY() > p->getY() && e->getLower().getY() < p->getY())
        {
            if(e->getLower().oriePred(e->getUpper(), *p) > 0)
                res = !res;
        }
    }

    return res;
}

/**
 * the next following functions are the methods related to the decomposition of a polygon into
 * y-monotone polygons.
 * for each inner cusp we want to find a diagonal that is a legal diagonal, and then split the polygon accordingly
 * and make a recursive call for the both polygons
 *
 * IDEA:
 * a polygon is y-monotone iff it does not have any inner cusps
 * inner cusp is a vertex which has two adjacent vertices with y-value bigger or lower than his
 */
int Shapes2D::Polygon::next_InnerCusp(Shapes2D::Polygon *poly, bool upper)
{
    int n = poly->getSize();

    for (int i=0; i<n; i++)
    {
        if (upper)
        {
            if (poly->anyInnerCusp(i, [](Point2d *a, Point2d *b, Point2d *c) {
                if (a->getY() > b->getY() && c->getY() > b->getY())
                {
                    if (a->oriePred(*b, *c) > 0)
                        return true;
                }
                return false;
            }))
                return i;
        }
        else
        {
            if (poly->anyInnerCusp(i, [](Point2d *a, Point2d *b, Point2d *c) {
                if (a->getY() < b->getY() && c->getY() < b->getY())
                {
                    if (a->oriePred(*b, *c) > 0)
                        return true;
                }
                return false;
            }))
                return i;
        }
    }

    return -1;
}

int Shapes2D::Polygon::leftBoundDownInnerCusp(Shapes2D::Polygon *poly, int v)
{
    int n = poly->getSize();
    double v_y = poly->getByIndex(v)->getY();

    for(int i=(v+1)%n; i!=v; i=(i+1)%n)
    {
        if (poly->getByIndex(i)->getY() >= v_y)
            return i;
    }

    return -1;
}

int Shapes2D::Polygon::rightBoundDownInnerCusp(Shapes2D::Polygon *poly, int v)
{
    int n = poly->getSize();
    double v_y = poly->getByIndex(v)->getY();

    for(int i=v==0 ? n-1 : v-1; i!=v; i=i == 0 ? n-1 : i-1)
    {
        if (poly->getByIndex(i)->getY() >= v_y)
            return i;
    }

    return -1;
}

int Shapes2D::Polygon::leftBoundUpperInnerCusp(Shapes2D::Polygon *poly, int v)
{
    int n = poly->getSize();
    double v_y = poly->getByIndex(v)->getY();

    for(int i=v==0 ? n-1 : v-1; i!=v; i=i == 0 ? n-1 : i-1)
    {
        if (poly->getByIndex(i)->getY() <= v_y)
            return i;
    }

    return -1;
}

int Shapes2D::Polygon::rightBoundUpperInnerCusp(Shapes2D::Polygon *poly, int v)
{
    int n = poly->getSize();
    double v_y = poly->getByIndex(v)->getY();

    for(int i=(v+1)%n; i!=v; i=(i+1)%n)
    {
        if (poly->getByIndex(i)->getY() <= v_y)
            return i;
    }

    return -1;
}

int Shapes2D::Polygon::findDiagonalFromUpperInnerCusp(Shapes2D::Polygon *poly, int innerCusp)
{
    int n = poly->getSize();
    int leftBoundVertex = leftBoundUpperInnerCusp(poly, innerCusp);
    int rightBoundVertex = rightBoundUpperInnerCusp(poly, innerCusp);

    Shapes2D::Point2d *left_point = poly->getByIndex(leftBoundVertex);
    Shapes2D::Point2d *right_point = poly->getByIndex(rightBoundVertex);

    int u = -1;

    for (int i=rightBoundVertex; i!=leftBoundVertex; i=(i+1)%n)
    {
        Shapes2D::Point2d *p = poly->getByIndex(i);
        if(p->getX() >= left_point->getX() && p->getX() <= right_point->getX())
        {
            if (poly->anyInnerCusp(i, [](Point2d *a, Point2d *b, Point2d *c) {
                if (a->getY() < b->getY() && c->getY() < b->getY())
                {
                    if (a->oriePred(*b, *c) > 0)
                        return true;
                }
                return false;
            }))
                return i;
            if (u == -1 || poly->getByIndex(u)->getY() < p->getY())
            {
                u = i;
                continue;
            }
        }
    }
    return u==-1 ? leftBoundVertex : u;
}

int Shapes2D::Polygon::findDiagonalFromDownInnerCusp(Shapes2D::Polygon *poly, int innerCusp)
{
    int n = poly->getSize();
    int leftBoundVertex = leftBoundDownInnerCusp(poly, innerCusp);
    int rightBoundVertex = rightBoundDownInnerCusp(poly, innerCusp);

    Shapes2D::Point2d *left_point = poly->getByIndex(leftBoundVertex);
    Shapes2D::Point2d *right_point = poly->getByIndex(rightBoundVertex);

    int u = -1;

    for (int i=leftBoundVertex; i!=rightBoundVertex; i=(i+1)%n)
    {
        Shapes2D::Point2d *p = poly->getByIndex(i);
        if(p->getX() >= left_point->getX() && p->getX() <= right_point->getX())
        {
            if (poly->anyInnerCusp(i, [](Point2d *a, Point2d *b, Point2d *c) {
                if (a->getY() > b->getY() && c->getY() > b->getY())
                {
                    if (a->oriePred(*b, *c) > 0)
                        return true;
                }
                return false;
            }))
                return i;
            if (u == -1 || poly->getByIndex(u)->getY() > p->getY())
            {
                u = i;
                continue;
            }
        }
    }

    return u==-1 ? rightBoundVertex : u;
}

std::vector<Shapes2D::Polygon *> Shapes2D::Polygon::decomposeY_Monotone(Shapes2D::Polygon *poly) {
    std::vector<Shapes2D::Polygon *> res;

    int n = poly->getSize();

    int downInnerCusp = next_InnerCusp(poly, false);
    if (downInnerCusp != -1)
    {
        int u = findDiagonalFromDownInnerCusp(poly, downInnerCusp);

        Shapes2D::Polygon *poly1, *poly2;
        std::vector<Shapes2D::Point2d *> poly1_points, poly2_points;

        for(int i=downInnerCusp; i!=u;  i = (i + 1) % n)
        {
            poly1_points.push_back(poly->getByIndex(i));
        }
        poly1_points.push_back(poly->getByIndex(u));

        for(int i=u; i!=downInnerCusp;  i = (i + 1) % n)
        {
            poly2_points.push_back(poly->getByIndex(i));
        }
        poly2_points.push_back(poly->getByIndex(downInnerCusp));

        poly1 = new Shapes2D::Polygon(poly1_points);
        poly2 = new Shapes2D::Polygon(poly2_points);

        std::vector<Polygon *> left_poly_dec = decomposeY_Monotone(poly1);
        std::vector<Polygon *> right_poly_dec = decomposeY_Monotone(poly2);

        res.insert(res.end(), left_poly_dec.begin(), left_poly_dec.end());
        res.insert(res.end(), right_poly_dec.begin(), right_poly_dec.end());

        return res;
    }

    int upperInnerCusp = next_InnerCusp(poly, true);
    if (upperInnerCusp != -1)
    {
        int u = findDiagonalFromUpperInnerCusp(poly, upperInnerCusp);

        Shapes2D::Polygon *poly1, *poly2;
        std::vector<Shapes2D::Point2d *> poly1_points, poly2_points;

        for(int i=upperInnerCusp; i!=u;  i = (i + 1) % n)
        {
            poly1_points.push_back(poly->getByIndex(i));
        }
        poly1_points.push_back(poly->getByIndex(u));

        for(int i=u; i!=upperInnerCusp;  i = (i + 1) % n)
        {
            poly2_points.push_back(poly->getByIndex(i));
        }
        poly2_points.push_back(poly->getByIndex(upperInnerCusp));

        poly1 = new Shapes2D::Polygon(poly1_points);
        poly2 = new Shapes2D::Polygon(poly2_points);

        std::vector<Polygon *> left_poly_dec = decomposeY_Monotone(poly1);
        std::vector<Polygon *> right_poly_dec = decomposeY_Monotone(poly2);

        res.insert(res.end(), left_poly_dec.begin(), left_poly_dec.end());
        res.insert(res.end(), right_poly_dec.begin(), right_poly_dec.end());

        return res;
    }

    res.push_back(poly);
    return res;
}

Shapes2D::Polygon::~Polygon() = default;

void Shapes2D::Polygon::splice(int pos, Polygon &other, int first, int last) {
    const auto& pos_it = vertices.begin()+pos;
    const auto& begin = other.vertices.begin()+first;
    const auto& end = other.vertices.begin()+last;

    vertices.insert(pos_it, begin, end);
}
