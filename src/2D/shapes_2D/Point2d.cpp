#include "Point2d.h"
#include <cmath>

using namespace Shapes2D;

Point2d::Point2d() : x(0), y(0) {}

Point2d::Point2d(double ax, double ay) : x(ax), y(ay) {}

double Point2d::getX() const { return x; }
double Point2d::getY() const { return y; }
void Point2d::setX(double val) { x = val; }
void Point2d::setY(double val) { y = val; }

double Point2d::norm() const {
    return std::sqrt(x * x + y * y);
}

double Point2d::dist(const Point2d& p) const {
    double dx = x - p.x;
    double dy = y - p.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::string Point2d::toStr() const {
    auto formatCoord = [](double val) {
        std::string s = std::to_string(val);
        return s.substr(0, s.find('.') + 3);
    };
    return "Point(" + formatCoord(x) + ", " + formatCoord(y) + ")";
}

void Point2d::rotate(double &deg) noexcept(false) {
    deg = fmod(deg, 360);
    double radians = 2 * M_PI - deg * M_PI / 180;
    double c = cos(radians);
    double s = sin(radians);
    double newX = x * c - y * s;
    double newY = x * s + y * c;
    x = newX;
    y = newY;
}

void Point2d::rotate(double &deg, const Point2d& p) noexcept(false) {
    deg = fmod(deg, 360);
    double radians = 2 * M_PI - deg * M_PI / 180;
    double c = cos(radians);
    double s = sin(radians);
    double dx = x - p.x;
    double dy = y - p.y;
    x = dx * c - dy * s + p.x;
    y = dx * s + dy * c + p.y;
}

void Point2d::subtract(const Point2d &p) noexcept(false) {
    x -= p.x;
    y -= p.y;
}

void Point2d::adder(const Point2d &p) {
    x += p.x;
    y += p.y;
}

double Point2d::oriePred(const Point2d &q, const Point2d &r) const noexcept(false) {
    return (q.x - x) * (r.y - y) - (q.y - y) * (r.x - x);
}

Point2d::~Point2d() = default;

