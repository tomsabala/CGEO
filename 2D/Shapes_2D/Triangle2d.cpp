
#include "Triangle2d.h"

Triangle2d::Triangle2d(Shapes2D::Point2d p, Shapes2D::Point2d q, Shapes2D::Point2d t) :
    vertex(std::vector<Shapes2D::Point2d>{p, q, t}) {}


std::vector<Shapes2D::Point2d> Triangle2d::getVertices()
{
    return this->vertex;
}