
#include "Segment2d.h"

using namespace Shapes2D;

/**
* standard constructor
 * init origin as p and target as q
 * @param p, q two Point2d type objects
*/
Segment2d::Segment2d(const Point2d &p, const Point2d &q) : origin(p), target(q) {}

/**
 * getter and setter methods
 */
Point2d Segment2d::getOrigin() const{
    return this->origin;
}

Point2d Segment2d::getTarget() const{
    return this->target;
}

void Segment2d::setOrigin(const Point2d& new_p) {
    this->origin.setX(new_p.getX());
    this->origin.setY(new_p.getY());
}

void Segment2d::setTarget(const Point2d& new_p) {
    this->target.setX(new_p.getX());
    this->target.setY(new_p.getY());
}

/**
 * return the upper point between origin and target
 * @return
 */
Point2d Segment2d::getUpper() const{
    if(this->getOrigin() > this->getTarget()) return this->getOrigin();
    else return this->getTarget();
}

/**
 * return the lower point between origin and target
 * @return
 */
Point2d Segment2d::getLower() const{
    if(this->getOrigin() < this->getTarget()) return this->getOrigin();
    else return this->getTarget();
}

/**
 * set upper point to new point
 * @param p new point object
 */
void Segment2d::setUpper(const Point2d& p) {
    Point2d *new_point;
    new_point = (Point2d *) malloc(sizeof(Point2d));

    new_point = new Point2d(p.getX(), p.getY());
    if(this->getUpper() == this->getTarget()){
        this->target.setX(new_point->getX());
        this->target.setY(new_point->getY());
    } else {
        this->origin.setX(new_point->getX());
        this->origin.setY(new_point->getY());
    }
}

/**
 * set lower point to new point
 * @param p new point object
 */
void Segment2d::setLower(const Point2d& p) {
    Point2d *new_point;
    new_point = (Point2d *) malloc(sizeof(Point2d));

    new_point = new Point2d(p.getX(), p.getY());
    if(this->getLower() == this->getTarget()) {
        this->target.setX(new_point->getX());
        this->target.setY(new_point->getY());
    } else {
        this->origin.setX(new_point->getX());
        this->origin.setY(new_point->getY());
    }
}

/**
* calculate slope of segment
 * return double type value
*/
double Segment2d::getSlope() const {
    if(this->origin.getX() == this->target.getX()) {
        return DBL_MAX;
    }

    double dy = this->origin.getY() - this->target.getY();
    double dx = this->origin.getX() - this->target.getX();

    return dy / dx;
}

/**
 * calculate length of segment
 * @return double type value length
 */
double Segment2d::getLength() const {
    return this->getOrigin().dist(this->getTarget());
}

/**
 * shift segment by p
 * @param p point type object
 */
void Segment2d::adder(const Point2d &p) const {
    this->getOrigin().adder(p);
    this->getTarget().adder(p);
}

/**
 * twist segment with degree deg
 * @param deg double type degree
 */
void Segment2d::rotate(double &deg) const {
    this->getTarget().rotate(deg, this->getOrigin());
}

/**
 * calculate orientation predicator between two lines
 * @param s another given segment where s.origin == this.origin
 * * otherwise throw exception
 * @return double value
 */
double Segment2d::oriePred(const Segment2d &s) const noexcept(false) {
    return this->getOrigin().oriePred(this->getTarget(), s.getTarget());
}

/**
 * calculate orientation predicator between line and other point
 * @param p given Point2d object
 * @return double value
 */
double Segment2d::oriePred(const Point2d &p) const noexcept(false) {
    return this->getOrigin().oriePred(this->getTarget(), p);
}

/**
 * check if s is paralleled with current segment
 * @param s given segment object
 * @return boolean
 */
bool Segment2d::isParallel(const Segment2d &s) const noexcept(false) {
    return this->getSlope() == s.getSlope();
}

/**
 * check if s is vertical with current segment
 * @param s given segment object
 * @return boolean
 */
bool Segment2d::isVertical(const Segment2d &s) const noexcept(false) {
    if(s.getSlope() == DBL_MAX || this->getSlope() == DBL_MAX)
        return s.getSlope() == 0 || this->getSlope() == 0;
    return this->getSlope() * s.getSlope() == 1;
}

/**
 * return distance between two paralleled segments
 * @param s given segment
 * if not paralleled throw exception
 * @return boolean
 */
double Segment2d::dist(const Segment2d &s) const noexcept(false) {
    if(s.getSlope() == DBL_MAX) {
        double l = this->getOrigin().getX() - s.getOrigin().getX();
        return l>=0 ? l : -l;
    }
    double m = this->getSlope();
    double c1 = -m*this->getOrigin().getX() + this->getOrigin().getY();
    double c2 = -m*s.getOrigin().getX() + s.getOrigin().getY();

    double abs_c1_c2 = c1>c2 ? c1-c2 : c2-c1;
    return abs_c1_c2 / sqrt(1 + pow(m, 2));
}

/**
 * calculate distance between segment and another point
 * @param p Point2d object
 * @return double value
 */
double Segment2d::dist(const Point2d &p) const noexcept(false) {
    auto *l = new Line2d(this->getOrigin(), this->getTarget());
    return l->dist(p);
}

/**
 * check is segment is intersect with s
 * @param s another given segment
 * @return boolean
 */
bool Segment2d::isIntersect(const Segment2d &s) const {
    if(this->oriePred(s.getOrigin()) >= 0 && this->oriePred(s.getTarget()) <= 0){
        if(s.oriePred(this->getOrigin()) >= 0 && s.oriePred(this->getTarget()) <= 0)
            return true;
        if(s.oriePred(this->getOrigin()) <= 0 && s.oriePred(this->getTarget()) >= 0)
            return true;
        return false;
    }

    if(this->oriePred(s.getOrigin()) <= 0 && this->oriePred(s.getTarget()) >= 0) {
        if(s.oriePred(this->getOrigin()) >= 0 && s.oriePred(this->getTarget()) <= 0)
            return true;
        if(s.oriePred(this->getOrigin()) <= 0 && s.oriePred(this->getTarget()) >= 0)
            return true;
        return false;
    }
    return false;
}

Point2d * Segment2d::getIntersect(const Segment2d &s) const {
    auto * res = new Point2d();
    if (this->getUpper() == s.getUpper() || this->getLower() == s.getUpper()) {
        res->setY(s.getUpper().getY());
        res->setX(s.getUpper().getX());

        return res;
    }
    if (this->getUpper() == s.getLower() || this->getLower() == s.getLower()) {
        res->setY(s.getLower().getY());
        res->setX(s.getLower().getX());

        return res;
    }

    if(this->isIntersect(s))
    {
        double s2_x = s.getTarget().getX() - s.getOrigin().getX();
        double s2_y = s.getTarget().getY() - s.getOrigin().getY();
        double s1_x = this->getTarget().getX() - this->getOrigin().getX();
        double s1_y = this->getTarget().getY() - this->getOrigin().getY();


        double t = ( s2_x * (this->getOrigin().getY() - s.getOrigin().getY()) - s2_y * (this->getOrigin().getX() - s.getOrigin().getX())) / (-s2_x * s1_y + s1_x * s2_y);

        res->setX(this->getOrigin().getX() + t * s1_x );
        res->setY(this->getOrigin().getY() + t * s1_y);

        return res;
    }

    delete res;
    return nullptr;
}

/**
 * function checks if segment contains point
 * @return boolean value
 */
bool Segment2d::containPoint(const Point2d &p) const {
    if(std::abs(this->oriePred(p)) <= eps) {
        return this->getUpper().getY() >= p.getY() && this->getLower().getY() <= p.getY();
    }
    return false;
}

std::string Segment2d::toStr() const{
    std::string res = this->getUpper().toStr() + " ----> " + this->getLower().toStr() + "\n";
    return res;
}

Segment2d::~Segment2d() = default;

double Segment2d::getXfromY(const double &y) const {
    if (this->getOrigin().getY() == this->getTarget().getY())
    {
        if (y == this->getOrigin().getY())
            return this->getOrigin().getX();

        return DBL_MAX;
    }

    double t = (y - this->getTarget().getY()) / (this->getOrigin().getY() - this->getTarget().getY());
    if (0 <= t && t <= 1)
        return t*this->getOrigin().getX() + (1-t)*this->getTarget().getX();
    return DBL_MAX;
}


double Segment2d::getYfromX(const double &x) const {
    if (this->getOrigin().getX() == this->getTarget().getX())
    {
        if (x == this->getOrigin().getX())
            return this->getOrigin().getY();

        return DBL_MAX;
    }

    double t = (x - this->getTarget().getX()) / (this->getOrigin().getX() - this->getTarget().getX());
    if (0 <= t && t <= 1)
        return t*this->getOrigin().getY() + (1-t)*this->getTarget().getY();
    return DBL_MAX;
}


