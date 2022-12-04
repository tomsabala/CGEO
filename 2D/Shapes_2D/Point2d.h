
#pragma once

#include "../Exception2D.h"
#include <vector>
#include <string>

#define eps     0.00000001

namespace Shapes2D {
    struct Point2d {
    private:
        double x, y;

    public:
        /*constructors*/
        Point2d();
        Point2d(double x, double y);
        explicit Point2d(Point2d *p) noexcept(false);

        /* getter and setter */
        double getX() const;
        double getY() const;
        void setX(double val);
        void setY(double val);
        void copyPoint(Point2d *p) noexcept(false);

        /* norm && distances methods */
        double norm() const;
        double dist(Point2d *p) const noexcept(false);
        /**
         * insert few methods of distances such as:
         * dist to segment, dist to circular i.e.
         */

        /* builtin method */
        bool _eq_(Point2d *p) const noexcept(false);
        std::string toStr() const;
        bool _lt_(Point2d& p) const;
        bool _gt_(Point2d& p) const;
        /* shifting methods */
        void rotate(double &deg, Point2d *p) noexcept(false);
        Point2d* rotate(double &deg);
        Point2d* adder(Point2d *p) const;
        Point2d* subtract(Point2d *p) const;

        /* orientation predict */
        double oriePred(Point2d *q, Point2d *r) noexcept(false);


        bool operator <(const Point2d & b) const
        {
            if (y < b.y - eps) return true;
            else if (y > b.y + eps) return false;
            else if (x < b.x - eps) return true;
            else return false;
        }
        bool operator ==(const Point2d & b) const
        {
            return std::abs(y - b.y) < eps && std::abs(x - b.x) < eps;
        }
        bool operator !=(const Point2d & b) const
        {
            return std::abs(y - b.y) > eps || std::abs(x - b.x) > eps;
        }
    };
}



