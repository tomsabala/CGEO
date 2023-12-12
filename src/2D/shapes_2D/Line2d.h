#pragma once

#include "Point2d.h"

class Line2d {
public:
    double slope;
    Shapes2D::Point2d p;
    bool vertical;

    Line2d(double m, const Shapes2D::Point2d& point, bool is_vertical);

    __attribute__((unused)) Line2d(double m, double x, double y, bool is_vertical);
    Line2d(const Shapes2D::Point2d &point1, const Shapes2D::Point2d &point2) noexcept(false);

    double* getSlope();
    bool isVertical() const;
    bool isHorizon();

    __attribute__((unused)) double* getY_intersect() const;

    __attribute__((unused)) double* getX_intersect() const;

    __attribute__((unused)) std::pair<bool, double> getY_fromX(double x) const;
    std::pair<bool, double> getX_fromY(double y) const;
    double dist(__attribute__((unused)) const Shapes2D::Point2d &);

    Shapes2D::Point2d* line_intersection(Line2d* v);

    __attribute__((unused)) Shapes2D::Point2d * getProjection(Shapes2D::Point2d *);

    ~Line2d();
};

