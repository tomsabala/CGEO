
int main() {}

#include "Point2d.h"
#include <cmath>

using namespace Shapes2D;

/**
 * empty constructor
 * init x, y as (0, 0)
 */
Point2d::Point2d() : x(0), y(0) {}

/**
 * standard constructor
 * init x, y as (ax, ay)
 *
 * @param ax, ay double type values
 */
Point2d::Point2d(double ax, double ay) : x(ax) , y(ay) {}

/**
 * Point2d using constructor
 * init x, y as (p.x, p.y)
 * @param p point2d type object
 */
Point2d::Point2d(Point2d *p) {
    if(p== nullptr)
        throw(Exception2D("null pointer"));
    this->x = p->getX();
    this->y = p->getY();
}

/**
 * getter and setter
 * get & set for each coordinate
 * including copy data from other point2d type object
 */
double Point2d::getX() const {
    return this->x;
}

double Point2d::getY() const{
    return this->y;
}

void Point2d::setX(double val) {
    this->x = val;
}

void Point2d::setY(double val) {
    this->y = val;
}

void Point2d::copyPoint(Point2d *p) {
    if(p == nullptr)
        throw (Exception2D("null pointer"));
    this->x = p->getX();
    this->y = p->getY();
}

/**
 * point's norm l2 calculation
 * @return double value sqrt(x^2 + y^2)
 */
double Point2d::norm() const {
    double ax = this->getX(), ay = this->getY();
    return std::sqrt(pow(ax, 2) + pow(ay, 2));
}

/**
 * points distance to other point2d value object
 *
 * @param p point2d type object
 * @return double value sqrt((x1-x2)^2 + (y1-y2)^2)
 */
double Point2d::dist(Shapes2D::Point2d *p) const {
    if(p== nullptr)
        throw(Exception2D("null pointer"));

    double ax = this->getX(), ay = this->getY();
    double bx = p->getX(), by = p->getY();

    return std::sqrt(pow(ax-bx, 2) + pow(ay-by, 2));
}

/**
 * compare between other point type value
 * @param p Point2d type object
 * @return boolean value
 */
bool Point2d::_eq_(Point2d *p) const noexcept(false) {
    if(p == nullptr)
        throw(Exception2D("null pointer"));

    return std::abs(this->getX() - p->getX()) <= eps && std::abs(this->getY() - p->getY()) <= eps;
}

/**
 * return string representation of point
 * @return string
 */
std::string Point2d::toStr() const {
    std::string r = "Point(";
    std::string ret_x = std::to_string(this->getX());
    ret_x = ret_x.substr(0, ret_x.find('.')+3);
    r += ret_x;
    r += ", ";
    std::string ret_y = std::to_string(this->getY());
    ret_y = ret_y.substr(0, ret_y.find('.')+3);
    r += ret_y;
    r += ")";
    return r;
}

/**
 * rotate point's param. by deg. degrees
 * assuming 0 <= deg < 360, function applies deg %= 360
 * @param deg a double value degree
 */
void Point2d::rotate(double &deg, Point2d *p) noexcept(false) {
    if(p == nullptr)
        throw (Exception2D("null pointer"));
    deg = fmod(deg, 360);

    /* compute cos and sin */
    double c = cos(2 * M_PI - deg * M_PI / 180);
    double s = sin(2 * M_PI - deg * M_PI / 180);

    /* translate point to origin */
    this->setX(this->getX() - p->getX());
    this->setY(this->getY() - p->getY());

    /* twist with deg. degrees */
    double newX = this->getX() * c - this->getY() * s;
    double newY = this->getX() * s + this->getY() * c;

    /* add pivot back and set new point */
    this->setX(newX + p->getX());
    this->setY(newY + p->getY());
}

/**
 * return point rotated by deg. degrees
 * assuming 0 <= deg < 360, function applies deg %= 360
 * @param deg @param deg a double value degree
 * @return Point2d type object
 */
Point2d* Point2d::rotate(double &deg) {
    auto* p = new Point2d(this);
    p->rotate(deg, new Point2d(0, 0));
    return p;
}

/**
 * create Point2d object after adding and subtracting values of p from this
 * @param p Point2d type value
 * @return Point2d pointer
 */
Point2d* Point2d::subtract(Point2d *p) const noexcept(false){
    if(p == nullptr)
        throw (Exception2D("null pointer"));
    return new Point2d(this->getX() - p->getX(), this->getY() - p->getY());
}
Point2d* Point2d::adder(Point2d *p) const {
    if(p == nullptr)
        throw (Exception2D("null pointer"));
    return new Point2d(this->getX() + p->getX(), this->getY() + p->getY());
}

/**
 * calculate the orientation between this, p, and q
 * @param p Point2d type object
 * @param q Point2d type object
 * @return double parameter
 */
double Point2d::oriePred(Point2d *q, Point2d *r) noexcept(false) {
    if(q == nullptr || r == nullptr)
        throw (Exception2D("null pointer"));
    Point2d* pq = q->subtract(this);
    Point2d* pr = r->subtract(this);

    return pq->getX()*pr->getY() - pq->getY()*pr->getX();
}

bool Point2d::_lt_(Point2d &p) const {
    return this->getY()<p.getY()-eps || (std::abs(this->getY() - p.getY()) <= eps && this->getX() < p.getX());
}

bool Point2d::_gt_(Point2d &p) const {
    return this->getY()>p.getY()+eps || (std::abs(this->getY() - p.getY()) <= eps && this->getX() > p.getX());
}

Point2d::~Point2d() {}

