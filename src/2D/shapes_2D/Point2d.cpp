

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
double Point2d::dist(const Shapes2D::Point2d& p) const {
    double ax = this->getX(), ay = this->getY();
    double bx = p.getX(), by = p.getY();

    return std::sqrt(pow(ax-bx, 2) + pow(ay-by, 2));
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
 * rotate point's param. by deg. degrees around the origin
 * assuming 0 <= deg < 360, function applies deg %= 360
 * @param deg a double value degree
 */
void Point2d::rotate(double &deg) noexcept(false) {
    deg = fmod(deg, 360);

    /* compute cos and sin */
    double c = cos(2 * M_PI - deg * M_PI / 180);
    double s = sin(2 * M_PI - deg * M_PI / 180);

    /* twist with deg. degrees */
    this->setX(this->getX() * c - this->getY() * s);
    this->setY(this->getX() * s + this->getY() * c);
}

/**
 * rotate point's param. by deg. degrees around p
 * assuming 0 <= deg < 360, function applies deg %= 360
 * @param deg a double value degree
 * @param p a pivot point to rotate around
 */
void Point2d::rotate(double &deg, const Point2d& p) noexcept(false) {
    deg = fmod(deg, 360);

    /* compute cos and sin */
    double c = cos(2 * M_PI - deg * M_PI / 180);
    double s = sin(2 * M_PI - deg * M_PI / 180);

    /* translate point to origin */
    this->setX(this->getX() - p.getX());
    this->setY(this->getY() - p.getY());

    /* twist with deg. degrees */
    double newX = this->getX() * c - this->getY() * s;
    double newY = this->getX() * s + this->getY() * c;

    /* add pivot back and set new point */
    this->setX(newX + p.getX());
    this->setY(newY + p.getY());
}

/**
 * create Point2d object after adding and subtracting values of p from this
 * @param p Point2d type value
 * @return Point2d pointer
 */
void Point2d::subtract(const Point2d &p) noexcept(false){
    this->setX(getX() - p.getX());
    this->setY(getY() - p.getY());
}
void Point2d::adder(const Point2d &p) {
    this->setX(getX() + p.getX());
    this->setY(getY() + p.getY());
}

/**
 * calculate the orientation between this, p, and q
 * @param p Point2d type object
 * @param q Point2d type object
 * @return double parameter
 */
double Point2d::oriePred(const Point2d &q, const Point2d &r) const noexcept(false) {
    double pq_x = q.getX() - this->getX();
    double pq_y = q.getY() - this->getY();
    double pr_x = r.getX() - this->getX();
    double pr_y = r.getY() - this->getY();

    return pq_x*pr_y - pq_y*pr_x;
}

Point2d::~Point2d() = default;

