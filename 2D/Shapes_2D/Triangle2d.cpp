
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