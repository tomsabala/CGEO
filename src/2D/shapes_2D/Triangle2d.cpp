
#include <iostream>
#include "Triangle2d.h"

using namespace Shapes2D;

Triangle2d::Triangle2d(Point2d p, Point2d q, Point2d t) :
    vertex(std::vector<Point2d>{p, q, t}) {}


std::vector<Point2d> Triangle2d::getVertices()
{
    return this->vertex;
}

Shapes2D::Point2d Triangle2d::getA()
{
    return this->vertex[0];
}
Shapes2D::Point2d Triangle2d::getB()
{
    return this->vertex[1];
}
Shapes2D::Point2d Triangle2d::getC()
{
    return this->vertex[2];
}
void Triangle2d::setA(Shapes2D::Point2d p)
{
    this->vertex[0]=p;
}
void Triangle2d::setB(Shapes2D::Point2d p)
{
    this->vertex[1]=p;
}
void Triangle2d::setC(Shapes2D::Point2d p)
{
    this->vertex[2]=p;
}


double Triangle2d::area()
{
    double a = 0.5 * (getA().getX()*(getB().getY() - getC().getY()) + getB().getX()*(getC().getY() - getA().getY()) + getC().getX()*(getA().getY() - getB().getY()));

    return std::abs(a);
}

/**
 * check if one of the triangle's angles is more then 90 degrees
 * @return true iff the triangle is wide
 */
bool Triangle2d::isWide() {
    return Triangle2d::isWide(this->getA(), this->getB(), this->getC());
}

bool Triangle2d::isWide(Shapes2D::Point2d A, Shapes2D::Point2d B, Shapes2D::Point2d C) {
    auto distance = [](Point2d p, Point2d q)
    {
        return pow(p.getX() - q.getX(), 2) + pow(p.getY() - q.getY(), 2);
    };

    /* imp taken from https://www.geeksforgeeks.org/find-angles-given-triangle/ */
    double a2 = distance(B, C);
    double b2 = distance(A, C);
    double c2 = distance(A, B);

    double a = sqrt(a2);
    double b = sqrt(b2);
    double c = sqrt(c2);

    double alpha = acos((b2 + c2 - a2)/(2*b*c));
    double beta = acos((a2 + c2 - b2)/(2*a*c));
    double gamma = acos((a2 + b2 - c2)/(2*a*b));
    alpha = alpha * 180 / M_PI;
    beta = beta * 180 / M_PI;
    gamma = gamma * 180 / M_PI;

    return alpha>90 || beta>90 || gamma>90;
}
