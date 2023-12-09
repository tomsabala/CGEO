
#include "Line2d.h"

/**
 * empty constructor
 */
Line2d::Line2d()
    : slope(1), p(new Shapes2D::Point2d(0, 0)), vertical(false) {}

/**
 * default constructor
 * @param m slope of line
 * @param point a random point in which the line goes through
 * @param is_vertical boolean flag, for indicating whether line is vertical or not
 */
Line2d::Line2d(double m, Shapes2D::Point2d point, bool is_vertical)
    : slope(m), p(point), vertical(is_vertical){}

/**
 * constructor with out x, y coordinates
 * @param m
 * @param x
 * @param y
 * @param is_vertical
 */
Line2d::Line2d(double m, double x, double y, bool is_vertical)
    : slope(m), vertical(is_vertical) {
    p = *(new Shapes2D::Point2d(x, y));
}

/**
 * constructor with two points
 */
Line2d::Line2d(Shapes2D::Point2d *point1, Shapes2D::Point2d *point2) noexcept(false){
    if (point1 == point2)
        throw (Exception2D("two points are equal\n"));
    if (std::abs(point1->getX() - point2->getX()) <= eps){
        slope = 0;
        this->p = *point1;
        vertical = true;
    } else {
        slope = (point1->getY() - point2->getY()) / (point1->getX() - point2->getX());
        this->p = *point1;
        vertical = false;
    }
}

double *Line2d::getSlope() {
    if(vertical)
        return nullptr;
    return &slope;
}

bool Line2d::isVertical() {
    return vertical;
}

double* Line2d::getY_intersect() {
    if(vertical)
        return nullptr;
    /* allocate memory*/
    double* intersect_y =(double *) malloc(sizeof(double));
    if(intersect_y == nullptr){
        throw Exception2D("an error has occurred\n");
    }
    *intersect_y = this->p.getY() - this->slope * this->p.getX();
    return intersect_y;
}

double* Line2d::getX_intersect() {
    if(std::abs(slope) <= eps)
        return nullptr;
    /* allocate memory*/
    double* intersect_x =(double *) malloc(sizeof(double));
    if(intersect_x == nullptr){
        throw Exception2D("an error has occurred\n");
    }
    *intersect_x = (slope * this->p.getX() - this->p.getY()) / slope;
    return intersect_x;
}

Shapes2D::Point2d *Line2d::line_intersection(Line2d *u, Line2d *v) {
    double y_val, x_val;
    double *m_u = (double *) malloc(sizeof(double));
    double *m_v = (double *) malloc(sizeof(double ));
    if(m_v == nullptr || m_u == nullptr)
        throw Exception2D("an error occurred\n");

    m_u = u->getSlope();
    m_v = v->getSlope();

    if(m_u == nullptr && m_v == nullptr) return nullptr; /* both lines are vertical */
    if(m_u == nullptr){
        x_val = u->p.getX();
        y_val = *m_v * x_val + v->p.getY() - *m_v * v->p.getX();
        return new Shapes2D::Point2d(x_val, y_val);
    } else if (m_v == nullptr) {
        x_val = v->p.getX();
        y_val = *m_u * x_val + u->p.getY() - *m_u * u->p.getX();
        return new Shapes2D::Point2d(x_val, y_val);
    }else if (std::abs(m_u - m_v) <= eps) return nullptr;
    else {
        double u_a = -*m_u, u_c = -(*m_u * u->p.getX()) + u->p.getY();
        double v_a = -*m_v, v_c = -(*m_v * v->p.getX()) + v->p.getY();

        double det2lines = -*m_u + (*m_v);
        x_val = (u_c - v_c) / det2lines;
        y_val = (u_a * v_c - v_a * u_c) / det2lines;
        return new Shapes2D::Point2d(x_val, y_val);
    }
}

std::pair<bool, double> Line2d::getY_fromX(double x) {
    if(this->vertical) {
        return std::make_pair(false, 0);
    }
    else{
        return std::make_pair(true, this->slope * (x - this->p.getX()) + this->p.getY());
    }
}

std::pair<bool, double> Line2d::getX_fromY(double y) {
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
double Line2d::dist(Shapes2D::Point2d *point) {
    return 0;
}

Shapes2D::Point2d *Line2d::getProjection(Shapes2D::Point2d *point) {
    Line2d * orthogonal_l;
    if (this->getSlope() == 0)
        orthogonal_l = new Line2d(0, *point, true);
    else
        orthogonal_l = new Line2d(-1/(*this->getSlope()), *point, false);

    return Line2d::line_intersection(this, orthogonal_l);
}

bool Line2d::isHorizon() {
    return !isVertical() && *getSlope() == 0;
}
