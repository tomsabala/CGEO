#pragma once

#include <string>
#include <cmath>

#define eps 0.00000001

namespace Shapes2D {
    struct Point2d {
    private:
        double x, y;

    public:
        Point2d();
        Point2d(double x, double y);

        double getX() const;
        double getY() const;
        void setX(double val);
        void setY(double val);

        double norm() const;
        double dist(const Point2d& p) const noexcept(false);

        std::string toStr() const;

        void rotate(double &deg, const Point2d& p) noexcept(false);
        void rotate(double &deg) noexcept(false);
        void adder(const Point2d &p);
        void subtract(const Point2d &p);

        double oriePred(const Point2d &q, const Point2d &r) const noexcept(false);

        bool operator<(const Point2d &b) const {
            if (std::abs(y - b.y) >= eps) return y < b.y - eps;
            return x < b.x - eps;
        }

        bool operator>(const Point2d &b) const {
            if (std::abs(y - b.y) >= eps) return y > b.y + eps;
            return x > b.x + eps;
        }

        bool operator==(const Point2d &b) const {
            return std::abs(y - b.y) < eps && std::abs(x - b.x) < eps;
        }

        bool operator!=(const Point2d &b) const {
            return std::abs(y - b.y) > eps || std::abs(x - b.x) > eps;
        }

        ~Point2d();
    };
}



