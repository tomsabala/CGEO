#pragma once

#include "Point2d.h"
#include <optional>
#include <utility>

class Line2d {
public:
    double slope;
    Shapes2D::Point2d p;
    bool vertical;

    Line2d(double m, const Shapes2D::Point2d& point, bool is_vertical);
    Line2d(const Shapes2D::Point2d& point1, const Shapes2D::Point2d& point2);

    [[nodiscard]] std::optional<double> getSlope() const;
    [[nodiscard]] bool isVertical() const;
    [[nodiscard]] bool isHorizon() const;

    [[nodiscard]] std::pair<bool, double> getY_fromX(double x) const;
    [[nodiscard]] std::pair<bool, double> getX_fromY(double y) const;
    [[nodiscard]] double dist(const Shapes2D::Point2d& point) const;

    [[nodiscard]] Shapes2D::Point2d* line_intersection(const Line2d& other) const;
    [[nodiscard]] Shapes2D::Point2d* getProjection(const Shapes2D::Point2d& point) const;

    ~Line2d() = default;
};

