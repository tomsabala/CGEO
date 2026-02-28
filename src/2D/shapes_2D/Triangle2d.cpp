#include "Triangle2d.h"
#include <cmath>

using namespace Shapes2D;

Triangle2d::Triangle2d(Point2d p, Point2d q, Point2d t) : vertex({p, q, t}) {}

std::vector<Point2d> Triangle2d::getVertices() { return vertex; }

Point2d Triangle2d::getA() { return vertex[0]; }
Point2d Triangle2d::getB() { return vertex[1]; }
Point2d Triangle2d::getC() { return vertex[2]; }

void Triangle2d::setA(Point2d p) { vertex[0] = p; }
void Triangle2d::setB(Point2d p) { vertex[1] = p; }
void Triangle2d::setC(Point2d p) { vertex[2] = p; }

double Triangle2d::area() {
    const Point2d& a = vertex[0];
    const Point2d& b = vertex[1];
    const Point2d& c = vertex[2];
    double val = 0.5 * (a.getX() * (b.getY() - c.getY()) +
                        b.getX() * (c.getY() - a.getY()) +
                        c.getX() * (a.getY() - b.getY()));
    return std::abs(val);
}

bool Triangle2d::isWide() {
    return isWide(vertex[0], vertex[1], vertex[2]);
}

bool Triangle2d::isWide(Point2d A, Point2d B, Point2d C) {
    auto distSquared = [](const Point2d& p, const Point2d& q) {
        double dx = p.getX() - q.getX();
        double dy = p.getY() - q.getY();
        return dx * dx + dy * dy;
    };

    double a2 = distSquared(B, C);
    double b2 = distSquared(A, C);
    double c2 = distSquared(A, B);

    return a2 > b2 + c2 || b2 > a2 + c2 || c2 > a2 + b2;
}
