#include "Line2d.h"
#include <cmath>

Line2d::Line2d(double m, const Shapes2D::Point2d& point, bool is_vertical)
    : slope(m), p(point), vertical(is_vertical) {}

Line2d::Line2d(const Shapes2D::Point2d& point1, const Shapes2D::Point2d& point2) {
    p = point1;
    if (std::abs(point1.getX() - point2.getX()) <= eps) {
        slope = 0;
        vertical = true;
    } else {
        slope = (point1.getY() - point2.getY()) / (point1.getX() - point2.getX());
        vertical = false;
    }
}

std::optional<double> Line2d::getSlope() const {
    return vertical ? std::nullopt : std::optional<double>(slope);
}

bool Line2d::isVertical() const { return vertical; }

bool Line2d::isHorizon() const {
    return !vertical && std::abs(slope) <= eps;
}

std::pair<bool, double> Line2d::getY_fromX(double x) const {
    if (vertical) return {false, 0};
    return {true, slope * (x - p.getX()) + p.getY()};
}

std::pair<bool, double> Line2d::getX_fromY(double y) const {
    if (vertical) return {true, p.getX()};
    if (std::abs(slope) <= eps) return {false, 0};
    return {true, (y - p.getY() + slope * p.getX()) / slope};
}

double Line2d::dist(const Shapes2D::Point2d& point) const {
    if (vertical) return std::abs(point.getX() - p.getX());
    double a = slope;
    double b = -1;
    double c = p.getY() - slope * p.getX();
    return std::abs(a * point.getX() + b * point.getY() + c) / std::sqrt(a * a + b * b);
}

Shapes2D::Point2d* Line2d::line_intersection(const Line2d& other) const {
    auto m_u = getSlope();
    auto m_v = other.getSlope();

    // Both lines are vertical - no intersection
    if (!m_u.has_value() && !m_v.has_value()) return nullptr;

    // This line is vertical
    if (!m_u.has_value()) {
        double x_val = p.getX();
        double y_val = *m_v * x_val + other.p.getY() - *m_v * other.p.getX();
        return new Shapes2D::Point2d(x_val, y_val);
    }

    // Other line is vertical
    if (!m_v.has_value()) {
        double x_val = other.p.getX();
        double y_val = *m_u * x_val + p.getY() - *m_u * p.getX();
        return new Shapes2D::Point2d(x_val, y_val);
    }

    // Parallel lines - no intersection
    if (std::abs(*m_u - *m_v) <= eps) return nullptr;

    double u_a = -*m_u;
    double u_c = -(*m_u * p.getX()) + p.getY();
    double v_a = -*m_v;
    double v_c = -(*m_v * other.p.getX()) + other.p.getY();

    double det2lines = -*m_u + *m_v;
    double x_val = (u_c - v_c) / det2lines;
    double y_val = (u_a * v_c - v_a * u_c) / det2lines;

    return new Shapes2D::Point2d(x_val, y_val);
}

Shapes2D::Point2d* Line2d::getProjection(const Shapes2D::Point2d& point) const {
    auto slopeOpt = getSlope();
    bool hasNonZeroSlope = slopeOpt.has_value() && std::abs(*slopeOpt) > eps;
    Line2d orthogonal = hasNonZeroSlope
        ? Line2d(-1.0 / *slopeOpt, point, false)
        : Line2d(0, point, true);
    return line_intersection(orthogonal);
}
