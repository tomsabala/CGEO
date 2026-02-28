#include "Circle2d.h"
#include <cmath>
#include <algorithm>

using namespace Shapes2D;

Circle2d::Circle2d() : r(1), c(new Point2d(0, 0)) {}

Circle2d::Circle2d(double radius) : r(radius), c(new Point2d(0, 0)) {}

Circle2d::Circle2d(double radius, Point2d* center) : r(radius), c(center) {}

Circle2d::Circle2d(const Point2d& p, const Point2d& q) {
    c = new Point2d((p.getX() + q.getX()) / 2, (p.getY() + q.getY()) / 2);
    r = p.dist(q) / 2;
}

Circle2d::Circle2d(const Point2d& p, const Point2d& q, const Point2d& t) {
    auto vals = circleFrom3Points(p, q, t);
    r = vals.first;
    c = vals.second;
}

double Circle2d::getRadius() const { return r; }
void Circle2d::setRadius(double radius) { r = radius; }
Point2d* Circle2d::getCenter() { return c; }

void Circle2d::setCenter(Point2d* p) {
    c->setX(p->getX());
    c->setY(p->getY());
}

bool Circle2d::circleIntersect(Circle2d* circ) {
    double centers_dist = c->dist(*circ->c);
    return centers_dist >= std::abs(r - circ->r) && centers_dist <= r + circ->r;
}

bool Circle2d::lineIntersect(Line2d* l) {
    return l->dist(*getCenter()) <= r;
}

bool Circle2d::segIntersect(Segment2d* s) {
    double a_c = s->getOrigin().getX() - s->getTarget().getX();
    double b_d = s->getOrigin().getY() - s->getTarget().getY();
    double c_xc = s->getTarget().getX() - c->getX();
    double d_yc = s->getTarget().getY() - c->getY();

    double bb = 4 * std::pow(a_c * c_xc + b_d * d_yc, 2);
    double ac4 = 4 * (std::pow(a_c, 2) + std::pow(b_d, 2)) *
        (std::pow(c->getX(), 2) + std::pow(c->getY(), 2) +
         std::pow(s->getTarget().getX(), 2) + std::pow(s->getTarget().getY(), 2) -
         std::pow(r, 2) - 2 * s->getTarget().getX() * c->getX() - 2 * s->getTarget().getY() * c->getY());

    if (bb - ac4 < 0) return false;

    double denom = 2 * (std::pow(a_c, 2) + std::pow(b_d, 2));
    double sqrtDisc = std::sqrt(bb - ac4);
    double t1 = (-2 * (a_c * c_xc + b_d * d_yc) + sqrtDisc) / denom;
    double t2 = (-2 * (a_c * c_xc + b_d * d_yc) - sqrtDisc) / denom;

    return (t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1);
}

bool Circle2d::polyIntersect(Polygon* poly) {
    auto edges = poly->getEdges();
    return std::any_of(edges.begin(), edges.end(),
        [this](Segment2d* s) { return segIntersect(s); });
}

int Circle2d::pointContains(const Point2d& p) {
    double d = c->dist(p);
    if (d > r) return -1;
    if (d == r) return 0;
    return 1;
}

int Circle2d::segmentContains(Segment2d* s) {
    if (segIntersect(s)) return 0;
    if (pointContains(s->getTarget()) == 1 && pointContains(s->getOrigin()) == 1) return 1;
    return -1;
}

int Circle2d::circleContains(Circle2d* circ) {
    if (circleIntersect(circ)) return 0;
    if (c->dist(*circ->c) + circ->r <= r) return 1;
    return -1;
}

int Circle2d::polyContains(Polygon* poly) {
    bool allInside = true;
    for (Segment2d* s : poly->getEdges()) {
        if (segIntersect(s)) return 0;
        allInside = allInside && (segmentContains(s) == 1);
    }
    return allInside ? 1 : -1;
}

void Circle2d::setCircle(Point2d* p, Point2d* q, Point2d* t) {
    auto val = circleFrom3Points(*p, *q, *t);
    delete c;
    c = val.second;
    r = val.first;
}

std::pair<double, Point2d*> Circle2d::circleFrom3Points(const Point2d& p, const Point2d& q, const Point2d& t) {
    Point2d mid1((p.getX() + q.getX()) / 2, (p.getY() + q.getY()) / 2);
    Point2d mid2((p.getX() + t.getX()) / 2, (p.getY() + t.getY()) / 2);

    Line2d* l1;
    Line2d* l2;

    if (p.getY() == q.getY()) {
        l1 = new Line2d(0, mid1, true);
    } else {
        double slope1 = (p.getY() - q.getY()) / (p.getX() - q.getX());
        l1 = new Line2d(-1 / slope1, mid1, false);
    }

    if (p.getY() == t.getY()) {
        l2 = new Line2d(0, mid2, true);
    } else {
        double slope2 = (p.getY() - t.getY()) / (p.getX() - t.getX());
        l2 = new Line2d(-1 / slope2, mid2, false);
    }

    Point2d* center = l1->line_intersection(l2);
    double radius = center->dist(p);

    delete l1;
    delete l2;

    return {radius, center};
}

Circle2d::~Circle2d() {
    delete c;
}

