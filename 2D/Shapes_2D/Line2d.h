#pragma once

#include "Point2d.h"

class Line2d {
public:
    double slope;
    Shapes2D::Point2d p;
    bool vertical;

    Line2d();
    Line2d(double m, Shapes2D::Point2d point, bool is_vertical);
    Line2d(double m, double x, double y, bool is_vertical);
    Line2d(Shapes2D::Point2d* point1, Shapes2D::Point2d* point2) noexcept(false);

    double* getSlope();
    bool isVertical();
    double* getY_intersect();
    double* getX_intersect();
    std::pair<bool, double> getY_fromX(double x);
    std::pair<bool, double> getX_fromY(double y);
    double dist(Shapes2D::Point2d *);

    static Shapes2D::Point2d* line_intersection(Line2d* u, Line2d* v);
};

