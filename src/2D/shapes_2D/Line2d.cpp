
#include "Line2d.h"

/**
 * default constructor
 * @param m slope of line
 * @param point a random point in which the line goes through
 * @param is_vertical boolean flag, for indicating whether line is vertical or not
 */
Line2d::Line2d(double m, const Shapes2D::Point2d& point, bool is_vertical)
    : slope(m), p(point), vertical(is_vertical){}

/**
 * constructor with out x, y coordinates
 * @param m
 * @param x
 * @param y
 * @param is_vertical
 */
__attribute__((unused)) Line2d::Line2d(double m, double x, double y, bool is_vertical)
    : slope(m), vertical(is_vertical) {
    p = *(new Shapes2D::Point2d(x, y));
}

/**
 * constructor with two points
 */
Line2d::Line2d(const Shapes2D::Point2d &point1, const Shapes2D::Point2d &point2) noexcept(false){\
    if (std::abs(point1.getX() - point2.getX()) <= eps){
        slope = 0;
        this->p = point1;
        vertical = true;
    } else {
        slope = (point1.getY() - point2.getY()) / (point1.getX() - point2.getX());
        this->p = point1;
        vertical = false;
    }
}

double *Line2d::getSlope() {
    if(vertical)
        return nullptr;
    return &slope;
}

bool Line2d::isVertical() const {
    return vertical;
}

__attribute__((unused)) double* Line2d::getY_intersect() const {
    if(vertical)
        return nullptr;
    /* allocate memory*/
    auto* intersect_y =(double *) malloc(sizeof(double));\
    *intersect_y = this->p.getY() - this->slope * this->p.getX();
    return intersect_y;
}

__attribute__((unused)) double* Line2d::getX_intersect() const {
    if(std::abs(slope) <= eps)
        return nullptr;
    /* allocate memory*/
    auto* intersect_x =(double *) malloc(sizeof(double));\
    *intersect_x = (slope * this->p.getX() - this->p.getY()) / slope;
    return intersect_x;
}

Shapes2D::Point2d *Line2d::line_intersection(Line2d *v) {
    double y_val, x_val;
    auto *m_u = this->getSlope();
    auto *m_v = v->getSlope();

    if(m_u == nullptr && m_v == nullptr) return nullptr; /* both lines are vertical */
    if(m_u == nullptr){
        x_val = this->p.getX();
        y_val = *m_v * x_val + v->p.getY() - *m_v * v->p.getX();

        return new Shapes2D::Point2d(x_val, y_val);
    } else if (m_v == nullptr) {
        x_val = v->p.getX();
        y_val = *m_u * x_val + this->p.getY() - *m_u * this->p.getX();

        return new Shapes2D::Point2d(x_val, y_val);
    }else if (std::abs(m_u - m_v) <= eps) {
        return nullptr;
    }
    else {
        double u_a = -*m_u, u_c = -(*m_u * this->p.getX()) + this->p.getY();
        double v_a = -*m_v, v_c = -(*m_v * v->p.getX()) + v->p.getY();

        double det2lines = -*m_u + (*m_v);
        x_val = (u_c - v_c) / det2lines;
        y_val = (u_a * v_c - v_a * u_c) / det2lines;

        return new Shapes2D::Point2d(x_val, y_val);
    }
}

__attribute__((unused)) std::pair<bool, double> Line2d::getY_fromX(double x) const {
    if(this->vertical) {
        return std::make_pair(false, 0);
    }
    else{
        return std::make_pair(true, this->slope * (x - this->p.getX()) + this->p.getY());
    }
}

std::pair<bool, double> Line2d::getX_fromY(double y) const {
    if(this->slope == 0 && !this->vertical){
        return std::make_pair(false, 0);
    }
    else if (this->vertical){
        return std::make_pair(true, this->p.getX());
    }
    else{
        return std::make_pair(true, (y - this->p.getY() + this->slope * this->p.getX()) / (this->slope));
    }
}

/**
 * compute the distance of a point from the line
 * @param point : a point in the plane
 * @return double value of the distance
 */
double Line2d::dist(__attribute__((unused)) const Shapes2D::Point2d &point) {
    return 0;
}

__attribute__((unused)) Shapes2D::Point2d *Line2d::getProjection(Shapes2D::Point2d *point) {
    Line2d * orthogonal_l;
    if (this->getSlope() == nullptr || *this->getSlope() == 0)
        orthogonal_l = new Line2d(0, *point, true);
    else
        orthogonal_l = new Line2d(-1/(*this->getSlope()), *point, false);

    auto* res = Line2d::line_intersection(orthogonal_l);
    delete orthogonal_l;
    return res;
}

bool Line2d::isHorizon() {
    return !isVertical() && *getSlope() == 0;
}

Line2d::~Line2d() = default;
