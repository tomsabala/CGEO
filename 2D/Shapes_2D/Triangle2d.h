#pragma once

#include "Point2d.h"

class Triangle2d {
public:
    std::vector<Shapes2D::Point2d> vertex;

    Triangle2d(Shapes2D::Point2d p, Shapes2D::Point2d q, Shapes2D::Point2d t);
    std::vector<Shapes2D::Point2d> getVertices();
};