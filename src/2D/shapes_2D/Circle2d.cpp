
#include <valarray>
#include "Circle2d.h"
using namespace Shapes2D;
/**
 * empty constructor,
 * create a circle from radius 1, centered in (0, 0)
 */
Circle2d::Circle2d()
: r(1), c(new Point2d(0, 0)) {}

/**
 * semi-empty constructor,
 * creates a circle from radius r, centered in (0, 0)
 * @param r: a double value radius
 */
Circle2d::Circle2d(double radius)
: r(radius), c(new Point2d(0, 0)) {}

/**
 * standard constructor,
 * creates a circle with r=radius and c=center
 * @param radius: a double value radius
 * @param center: a point in 2d
 */
Circle2d::Circle2d(double radius, Point2d * center)
: r(radius), c(center) {}

/**
 * construct a circle with r=dist(p, q)/2 and center in the middle of pq segment
 * @param p, q : two points in the plane
 */
Circle2d::Circle2d(const Point2d& p, const Point2d& q)
{
    this->c = new Point2d((p.getX() + q.getX())/2, (p.getY() + q.getY())/2);
    this->r = p.dist(q) / 2;
}

/**
 * construct a circle around the triangle the these three points represents
 * @param p, q, t : three points in the plane.
 * assuming that p, q, and t don't lie on one line.
 */
Circle2d::Circle2d(const Point2d& p, const Point2d& q, const Point2d& t) {
    std::pair<double, Point2d *> vals = Circle2d::circleFrom3Points(p, q, t);

    this->c = vals.second;
    this->r = vals.first;
}

/**
 * return the circle's radius
 * @return r, value type
 */
double Circle2d::getRadius() const {return this->r;}

/**
 * set the circle radius to be radius
 * @param radius: double value radius
 */
void Circle2d::setRadius(double radius) {this->r = radius;}

/**
 * return the circle center point
 * @return a point in 2d
 */
Point2d *Circle2d::getCenter() {return this->c;}

/**
 * set's the circle's point the be centered in p.
 * @param p a 2d point in the plane
 */
void Circle2d::setCenter(Point2d *p) {this->c->setX(p->getX()); this->c->setY(p->getY());}

/**
 * checks whether two circles intersects.
 * @param circ another circle to compare to.
 * @return true iff circles are intersecting.
 */
bool Circle2d::circleIntersect(Circle2d *circ) {
    double centers_dist = this->c->dist(*circ->c);
    return centers_dist >= std::abs(this->r - circ->r) && centers_dist <= this->r + circ->r;
}

/**
 * checks whether the circle intersects with a given line
 * @param l a line in the plane
 * @return true iff circles intersect
 */
bool Circle2d::lineIntersect(Line2d *l) {
    return l->dist(this->getCenter()) <= this->r;
}

/**
 * check whether the circle intersects with a given segment
 * @param s a segment in the plane
 * @return true iff circle intersects the segment
 */
bool Circle2d::segIntersect(Segment2d *s) {

    /* we will brute force compute the intersection point if it exists
    a segment from point (x1, y1) to point (x2, y2) has a close formula (tx1 + (1-t)x2, ty1 + (1-y)y2) for 0<=t<=1
    we will find the intersections points if exits of the ray observed by the segment
    and check if we have 0<=t<=1 */

    /* we note (x1,y1),(x2,y2) == (a,b),(c,d) and circle center == (xc, yc)*/
    double a_c = s->getOrigin()->getX() - s->getTarget()->getX();
    double b_d = s->getOrigin()->getY() - s->getTarget()->getY();

    double c_xc = s->getTarget()->getX() - this->c->getX();
    double d_yc = s->getTarget()->getY() - this->c->getY();

    double bb = 4*pow(a_c * c_xc + b_d * d_yc, 2);
    double ac4 = 4*(pow(a_c, 2) + pow(b_d, 2))*
            (pow(c->getX(), 2)+pow(c->getY(), 2)+pow(s->getTarget()->getX(), 2)+pow(s->getTarget()->getY(), 2) -
            pow(r, 2) - 2*s->getTarget()->getX()*c->getX() - 2*s->getTarget()->getY()*c->getY());

    if (bb - ac4 < 0)
        return false;
    double t1 = (- 2*(a_c*c_xc + b_d*d_yc) + sqrt(bb-ac4))/(2*(pow(a_c, 2) + pow(b_d, 2)));
    double t2 = (- 2*(a_c*c_xc + b_d*d_yc) - sqrt(bb-ac4))/(2*(pow(a_c, 2) + pow(b_d, 2)));

    return (t1<=1 && 0<=t1) || (t2<=1 && 0<=t2);
}

/**
 * check whether the circle intersects with a given polygon
 * @param poly a polygon in the plane
 * @return true iff circle intersects the polygon
 */
bool Circle2d::polyIntersect(Polygon *poly) {
    /* the minimum complexity is O(n), as by start we need to read the polygon data */
    return std::any_of(poly->getEdges().begin(), poly->getEdges().end(), [this](Segment2d *s) {return this->segIntersect(s);});
}

/**
 * checks if a point is on the circle, outside from the circle or inside
 * @param p a point in the plane
 * @return 1 if the point is inside the circle, 0 if the point is on the circle or -1 otherwise
 */
int Circle2d::pointContains(Point2d *p) {
    double d = this->c->dist(*p);
    if (d > this->r) return -1;
    if (d == this->r) return 0;
    return 1;
}

/**
 * checks if a segment is on the circle, outside from the circle or inside
 * @param s a segment in the plane
 * @return 1 if the segment is inside the circle, 0 if the segment is on the circle or -1 otherwise
 */
int Circle2d::segmentContains(Segment2d *s) {
    if (this->segIntersect(s))
        return 0;
    if (this->pointContains(s->getTarget()) == 1 && this->pointContains(s->getOrigin()) == 1)
        return 1;
    return -1;
}

/**
 * checks if a circle is on the circle, outside from the circle or inside
 * @param circ a circle in the plane
 * @return 1 if the circle is inside the circle, 0 if the circle is on the circle or -1 otherwise
 */
int Circle2d::circleContains(Circle2d *circ) {
    if (this->circleIntersect(circ))
        return 0;
    if (this->c->dist(*circ->c) + circ->r <= this->r)
        return 1;
    return -1;
}

/**
 * checks if a poly is on the circle, outside from the circle or inside
 * @param poly a polygon in the plane
 * @return 1 if the poly is inside the circle, 0 if the poly is on the circle or -1 otherwise
 */
int Circle2d::polyContains(Polygon *poly) {
    bool flag = true;
    for (Segment2d *s : poly->getEdges())
    {
        if (this->segIntersect(s))
            return 0;
        flag = this->segmentContains(s);
    }
    return flag ? 1 : -1;
}

/**
 * this function works with the same flow as the 3-points constructor,
 * only the function don't create a new circle object, but overwrite an existing circle properties.
 * @param p, q, t : 3 points in the plane
 */
void Circle2d::setCircle(Point2d *p, Point2d *q, Point2d *t) {
    std::pair<double, Point2d *> val = Circle2d::circleFrom3Points(*p, *q, *t);

    delete this->c;

    this->c = val.second;
    this->r = val.first;
}

/**
 * this function finds the properties of a circle that goes through a 3 points in the plane.
 * @param p, q, t : 3 points in the plane
 */
std::pair<double, Point2d *> Circle2d::circleFrom3Points(const Point2d& p, const Point2d& q, const Point2d& t) {
    /* we need to build the orthogonal lines passing through the middle of two edges of the triangle */
    Line2d *l1, *l2;
    /* line 1: between p and q construction */

    auto *mid_point1 = new Point2d((p.getX() + q.getX()) / 2, (p.getY() + q.getY()) / 2);
    if (p.getY() == q.getY())
        l1 = new Line2d(0, *mid_point1, true);
    else
        l1 = new Line2d(-1/( (p.getY() - q.getY()) / (p.getX() - q.getX())), *mid_point1, false);

    auto *mid_point2 = new Point2d((p.getX() + t.getX()) / 2, (p.getY() + t.getY()) / 2);
    if (p.getY() == t.getY())
        l2 = new Line2d(0, *mid_point2, true);
    else
        l2 = new Line2d(-1/( (p.getY() - t.getY()) / (p.getX() - t.getX())), *mid_point2, false);


    Point2d *center = Line2d::line_intersection(l1, l2);
    double radius = center->dist(p);

    delete mid_point1;
    delete mid_point2;
    delete l1;
    delete l2;

    return std::make_pair(radius, center);
}

Circle2d::~Circle2d()
{
    delete this->c;
}

