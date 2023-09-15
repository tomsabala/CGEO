
#include "Segment2d.h"

using namespace Shapes2D;

/**
 * empty constructor
 * init origin as (0, 0) and target as (1, 1) by default
 */
Segment2d::Segment2d() {
    this->origin = new Point2d(0, 0);
    this->target = new Point2d(1, 1);
}

/**
* standard constructor
 * init origin as p and target as q
 * @param p, q two Point2d type objects
*/
Segment2d::Segment2d(Point2d *p, Point2d *q) : origin(p), target(q) {
    origin = (Point2d*) malloc(sizeof(Point2d));
    target = (Point2d*) malloc(sizeof(Point2d));
    if(!origin || !target)
        throw Exception2D("an error occurred\n");
    origin->setX(p->getX());
    origin->setY(p->getY());
    target->setX(q->getX());
    target->setY(q->getY());
}

Segment2d::Segment2d(Segment2d *s) :
origin(s->getOrigin()), target(s->getTarget()){}


Segment2d::Segment2d(const Segment2d *s) :
origin(s->getOrigin()), target(s->getTarget()){}

/**
 * getter and setter methods
 */
Point2d *Segment2d::getOrigin() const{
    return this->origin;
}

Point2d *Segment2d::getTarget() const{
    return this->target;
}

void Segment2d::setOrigin(Point2d *new_p) {
    this->origin = new_p;
}

void Segment2d::setTarget(Point2d *new_p) {
    this->target = new_p;
}

/**
 * return the upper point between origin and target
 * @return
 */
Point2d *Segment2d::getUpper() const{
    if(this->getOrigin()->_gt_(*this->getTarget())) return this->getOrigin();
    else return this->getTarget();
}

/**
 * return the lower point between origin and target
 * @return
 */
Point2d *Segment2d::getLower() const{
    if(this->getOrigin()->_lt_(*this->getTarget())) return this->getOrigin();
    else return this->getTarget();
}

/**
 * set upper point to new point
 * @param p new point object
 */
void Segment2d::setUpper(Point2d p) const {
    Point2d *new_point;
    new_point = (Point2d *) malloc(sizeof(Point2d));
    if(new_point == nullptr)
        throw Exception2D("an error occurred\n");

    new_point = new Point2d(p.getX(), p.getY());
    if(this->getUpper()->_eq_(this->getTarget())){
        this->target->setX(new_point->getX());
        this->target->setY(new_point->getY());
    } else {
        this->origin->setX(new_point->getX());
        this->origin->setY(new_point->getY());
    }
}

/**
 * set lower point to new point
 * @param p new point object
 */
void Segment2d::setLower(Point2d p) const {
    Point2d *new_point;
    new_point = (Point2d *) malloc(sizeof(Point2d));
    if(new_point == nullptr)
        throw Exception2D("an error occurred\n");

    new_point = new Point2d(p.getX(), p.getY());
    if(this->getLower()->_eq_(this->getTarget())){
        this->target->setX(new_point->getX());
        this->target->setY(new_point->getY());
    } else {
        this->origin->setX(new_point->getX());
        this->origin->setY(new_point->getY());
    }
}

/**
* calculate slope of segment
 * return double type value
*/
double Segment2d::getSlope() {
    if(this->origin->getX() == this->target->getX()) {
        return DBL_MAX;
    }

    double dy = this->origin->getY() - this->target->getY();
    double dx = this->origin->getX() - this->target->getX();

    return dy / dx;
}

/**
 * calculate length of segment
 * @return double type value length
 */
double Segment2d::getLength() {
    Point2d *p = this->getOrigin();
    return p->dist(this->getTarget());
}

/**
 * shift segment by p
 * @param p point type object
 */
void Segment2d::adder(Point2d *p) noexcept(false) {
    Point2d *o=this->getOrigin(), *t=this->getTarget();
    try {
        o->adder(p);
        t->adder(p);
    } catch (Exception2D &e) {
        throw e;
    }
}

/**
 * twist segment with degree deg
 * @param deg double type degree
 */
void Segment2d::rotate(double &deg) {
    this->getTarget()->rotate(deg, this->getOrigin());
}

/**
 * compare between given segment
 * @param s segment2d object
 * @return boolean
 */
bool Segment2d::_eq_(Segment2d *s) noexcept(false) {
    if (s == nullptr)
        throw(Exception2D("null pointer"));
    return this->getOrigin()->_eq_(s->getOrigin()) && this->getTarget()->_eq_(s->getTarget());
}

/**
 * return true if segment is less then s
 */
bool Segment2d::_lt_(Segment2d *s) noexcept(false) {
    if (s == nullptr)
        throw(Exception2D("null pointer"));
    if (this->getUpper()->getX() == s->getUpper()->getX())
        return this->getLower()->getX() < s->getLower()->getX();
    return this->getUpper()->getX() < s->getUpper()->getX();
}

/**
 * return true if segment is less then s
 */
bool Segment2d::_gt_(Segment2d *s) noexcept(false) {
    if (s == nullptr)
        throw(Exception2D("null pointer"));
    if (this->getUpper()->getX() == s->getUpper()->getX())
        return this->getLower()->getX() > s->getLower()->getX();
    return this->getUpper()->getX() > s->getUpper()->getX();
}

/**
 * copy details from given segment
 * @param s segment type object
 */
void Segment2d::copySegment(Segment2d *s) noexcept(false) {
    if (s == nullptr)
        throw (Exception2D("null pointer"));
    this->setOrigin(s->getOrigin());
    this->setTarget(s->getTarget());
}

/**
 * calculate orientation predicator between two lines
 * @param s another given segment where s.origin == this.origin
 * * otherwise throw exception
 * @return double value
 */
double Segment2d::oriePred(Segment2d *s) const noexcept(false) {
    if(s == nullptr || !s->getOrigin()->_eq_(this->getOrigin()))
        throw (Exception2D("s is either null pointer or the two segment dont collide at the origin"));
    return this->getOrigin()->oriePred(this->getTarget(), s->getTarget());
}

/**
 * calculate orientation predicator between line and other point
 * @param p given Point2d object
 * @return double value
 */
double Segment2d::oriePred(Point2d *p) const noexcept(false) {
    try {
        return this->getOrigin()->oriePred(this->getTarget(), p);
    } catch (Exception2D &e){
        throw e;
    }
}

/**
 * check if s is paralleled with current segment
 * @param s given segment object
 * @return boolean
 */
bool Segment2d::isParallel(Segment2d *s) noexcept(false) {
    if (s == nullptr)
        throw (Exception2D("null pointer"));
    return this->getSlope() == s->getSlope();
}

/**
 * check if s is vertical with current segment
 * @param s given segment object
 * @return boolean
 */
bool Segment2d::isVertical(Segment2d *s) noexcept(false) {
    if (s == nullptr)
        throw (Exception2D("null pointer"));
    if(s->getSlope() == DBL_MAX || this->getSlope() == DBL_MAX)
        return s->getSlope() == 0 || this->getSlope() == 0;
    return this->getSlope() * s->getSlope() == 1;
}

/**
 * return distance between two paralleled segments
 * @param s given segment
 * if not paralleled throw exception
 * @return boolean
 */
double Segment2d::dist(Segment2d *s) noexcept(false) {
    if(s == nullptr || this->isParallel(s))
        throw (Exception2D("s is either null pointer or not parallel with current segment"));
    if(s->getSlope() == DBL_MAX) {
        double l = this->getOrigin()->getX() - s->getOrigin()->getX();
        return l>=0 ? l : -l;
    }
    double m = this->getSlope();
    double c1 = -m*this->getOrigin()->getX() + this->getOrigin()->getY();
    double c2 = -m*s->getOrigin()->getX() + s->getOrigin()->getY();

    double abs_c1_c2 = c1>c2 ? c1-c2 : c2-c1;
    return abs_c1_c2 / sqrt(1 + pow(m, 2));
}

/**
 * calculate distance between segment and another point
 * @param p Point2d object
 * @return double value
 */
double Segment2d::dist(Point2d *p) noexcept(false) {
    if (p == nullptr)
        throw (Exception2D("null pointer"));

    Line2d *l = new Line2d(this->getOrigin(), this->getTarget());

    return l->dist(p);
}

/**
 * check is segment is intersect with s
 * @param s another given segment
 * @return boolean
 */
bool Segment2d::isIntersect(Segment2d *s) {
    if (s == nullptr)
        throw (Exception2D("null pointer"));
    if(this->oriePred(s->getOrigin()) >= 0 && this->oriePred(s->getTarget()) <= 0){
        if(s->oriePred(this->getOrigin()) >= 0 && s->oriePred(this->getTarget()) <= 0)
            return true;
        if(s->oriePred(this->getOrigin()) <= 0 && s->oriePred(this->getTarget()) >= 0)
            return true;
        return false;
    }

    if(this->oriePred(s->getOrigin()) <= 0 && this->oriePred(s->getTarget()) >= 0) {
        if(s->oriePred(this->getOrigin()) >= 0 && s->oriePred(this->getTarget()) <= 0)
            return true;
        if(s->oriePred(this->getOrigin()) <= 0 && s->oriePred(this->getTarget()) >= 0)
            return true;
        return false;
    }
    return false;
}

Point2d *Segment2d::getIntersect(Segment2d *s) {
    if (this->getUpper()->_eq_(s->getUpper()) || this->getLower()->_eq_(s->getUpper()))
        return s->getUpper();
    if (this->getUpper()->_eq_(s->getLower()) || this->getLower()->_eq_(s->getLower()))
        return s->getLower();

    if(this->isIntersect(s))
    {
        double s2_x = s->getTarget()->getX() - s->getOrigin()->getX();
        double s2_y = s->getTarget()->getY() - s->getOrigin()->getY();
        double s1_x = this->getTarget()->getX() - this->getOrigin()->getX();
        double s1_y = this->getTarget()->getY() - this->getOrigin()->getY();


        double t = ( s2_x * (this->getOrigin()->getY() - s->getOrigin()->getY()) - s2_y * (this->getOrigin()->getX() - s->getOrigin()->getX())) / (-s2_x * s1_y + s1_x * s2_y);

        return new Point2d(this->getOrigin()->getX() + t * s1_x, this->getOrigin()->getY() + t * s1_y);

    }
    return nullptr;
}

/**
 * function checks if segment contains point
 * @return boolean value
 */
bool Segment2d::containPoint(Point2d p) const {
    if(std::abs(this->oriePred(&p)) <= eps) {
        return this->getUpper()->getY() >= p.getY() && this->getLower()->getY() <= p.getY();
    }
    return false;
}

std::string Segment2d::toStr() const{
    std::string res = this->getUpper()->toStr() + " ----> " + this->getLower()->toStr() + "\n";
    return res;
}

Segment2d::~Segment2d() {
    delete this->origin;
    delete this->target;
}

double Segment2d::getXfromY(double y) {
    if (this->getOrigin()->getY() == this->getTarget()->getY())
    {
        if (y == this->getOrigin()->getY())
            return this->getOrigin()->getX();

        return DBL_MAX;
    }

    double t = (y - this->getTarget()->getY()) / (this->getOrigin()->getY() - this->getTarget()->getY());
    if (0 <= t && t <= 1)
        return t*this->getOrigin()->getX() + (1-t)*this->getTarget()->getX();
    return DBL_MAX;
}


double Segment2d::getYfromX(double x) {
    if (this->getOrigin()->getX() == this->getTarget()->getX())
    {
        if (x == this->getOrigin()->getX())
            return this->getOrigin()->getY();

        return DBL_MAX;
    }

    double t = (x - this->getTarget()->getX()) / (this->getOrigin()->getX() - this->getTarget()->getX());
    if (0 <= t && t <= 1)
        return t*this->getOrigin()->getY() + (1-t)*this->getTarget()->getY();
    return DBL_MAX;
}


