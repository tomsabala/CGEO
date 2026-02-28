#include "Segment2d.h"

using namespace Shapes2D;

Segment2d::Segment2d(const Point2d &p, const Point2d &q) : origin(p), target(q) {}

Point2d Segment2d::getOrigin() const { return origin; }
Point2d Segment2d::getTarget() const { return target; }
void Segment2d::setOrigin(const Point2d& new_p) { origin = new_p; }
void Segment2d::setTarget(const Point2d& new_p) { target = new_p; }

Point2d Segment2d::getUpper() const {
    return (origin > target) ? origin : target;
}

Point2d Segment2d::getLower() const {
    return (origin < target) ? origin : target;
}

void Segment2d::setUpper(const Point2d& p) {
    if (getUpper() == target) {
        target = p;
    } else {
        origin = p;
    }
}

void Segment2d::setLower(const Point2d& p) {
    if (getLower() == target) {
        target = p;
    } else {
        origin = p;
    }
}

double Segment2d::getSlope() const {
    if (origin.getX() == target.getX()) return DBL_MAX;
    return (origin.getY() - target.getY()) / (origin.getX() - target.getX());
}

double Segment2d::getLength() const {
    return origin.dist(target);
}

void Segment2d::adder(const Point2d &p) {
    origin.adder(p);
    target.adder(p);
}

void Segment2d::rotate(double &deg) {
    target.rotate(deg, origin);
}

double Segment2d::oriePred(const Segment2d &s) const noexcept(false) {
    return origin.oriePred(target, s.getTarget());
}

double Segment2d::oriePred(const Point2d &p) const noexcept(false) {
    return origin.oriePred(target, p);
}

bool Segment2d::isParallel(const Segment2d &s) const noexcept(false) {
    return getSlope() == s.getSlope();
}

bool Segment2d::isVertical(const Segment2d &s) const noexcept(false) {
    double thisSlope = getSlope();
    double otherSlope = s.getSlope();
    if (thisSlope == DBL_MAX || otherSlope == DBL_MAX) {
        return thisSlope == 0 || otherSlope == 0;
    }
    return thisSlope * otherSlope == -1;
}

double Segment2d::dist(const Segment2d &s) const noexcept(false) {
    if (s.getSlope() == DBL_MAX) {
        return std::abs(origin.getX() - s.getOrigin().getX());
    }
    double m = getSlope();
    double c1 = -m * origin.getX() + origin.getY();
    double c2 = -m * s.getOrigin().getX() + s.getOrigin().getY();
    return std::abs(c1 - c2) / std::sqrt(1 + m * m);
}

double Segment2d::dist(const Point2d &p) const noexcept(false) {
    Line2d l(getOrigin(), getTarget());
    return l.dist(p);
}

bool Segment2d::isIntersect(const Segment2d &s) const {
    double d1 = oriePred(s.getOrigin());
    double d2 = oriePred(s.getTarget());
    double d3 = s.oriePred(origin);
    double d4 = s.oriePred(target);

    bool crossesThis = (d1 >= 0 && d2 <= 0) || (d1 <= 0 && d2 >= 0);
    bool crossesOther = (d3 >= 0 && d4 <= 0) || (d3 <= 0 && d4 >= 0);
    return crossesThis && crossesOther;
}

Point2d* Segment2d::getIntersect(const Segment2d &s) const {
    Point2d upper = getUpper();
    Point2d lower = getLower();
    Point2d s_upper = s.getUpper();
    Point2d s_lower = s.getLower();

    if (upper == s_upper || lower == s_upper) {
        return new Point2d(s_upper.getX(), s_upper.getY());
    }
    if (upper == s_lower || lower == s_lower) {
        return new Point2d(s_lower.getX(), s_lower.getY());
    }

    if (!isIntersect(s)) return nullptr;

    double s2_x = s.getTarget().getX() - s.getOrigin().getX();
    double s2_y = s.getTarget().getY() - s.getOrigin().getY();
    double s1_x = target.getX() - origin.getX();
    double s1_y = target.getY() - origin.getY();

    double denom = -s2_x * s1_y + s1_x * s2_y;
    double t = (s2_x * (origin.getY() - s.getOrigin().getY()) - s2_y * (origin.getX() - s.getOrigin().getX())) / denom;

    return new Point2d(origin.getX() + t * s1_x, origin.getY() + t * s1_y);
}

bool Segment2d::containPoint(const Point2d &p) const {
    if (std::abs(oriePred(p)) > eps) return false;
    return getUpper().getY() >= p.getY() && getLower().getY() <= p.getY();
}

std::string Segment2d::toStr() const {
    return getUpper().toStr() + " ----> " + getLower().toStr() + "\n";
}

Segment2d::~Segment2d() = default;

double Segment2d::getXfromY(const double &y) const {
    if (origin.getY() == target.getY()) {
        return (y == origin.getY()) ? origin.getX() : DBL_MAX;
    }
    double t = (y - target.getY()) / (origin.getY() - target.getY());
    return (t >= 0 && t <= 1) ? t * origin.getX() + (1 - t) * target.getX() : DBL_MAX;
}

double Segment2d::getYfromX(const double &x) const {
    if (origin.getX() == target.getX()) {
        return (x == origin.getX()) ? origin.getY() : DBL_MAX;
    }
    double t = (x - target.getX()) / (origin.getX() - target.getX());
    return (t >= 0 && t <= 1) ? t * origin.getY() + (1 - t) * target.getY() : DBL_MAX;
}

