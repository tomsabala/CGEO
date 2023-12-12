
#pragma once

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

        /* getter and setter */
        double getX() const;
        double getY() const;
        void setX(double val);
        void setY(double val);

        /* norm && distances methods */
        double norm() const;
        double dist(const Point2d& p) const noexcept(false);
        /**
         * insert few methods of distances such as:
         * dist to segment, dist to circular i.e.
         */

        /* builtin method */
        std::string toStr() const;

        /* shifting methods */
        void rotate(double &deg, const Point2d& p) noexcept(false);
        void rotate(double &deg) noexcept(false);
        void adder(const Point2d &p) ;
        void subtract(const Point2d &p);

        /* orientation predict */
        double oriePred(const Point2d &q, const Point2d &r) const noexcept(false);


        bool operator <(const Point2d & b) const
        {
            if (std::abs(y-b.y) >= eps)
                return y < b.y-eps;
            return x < b.x - eps;
        }
        bool operator >(const Point2d & b) const
        {
            if (std::abs(y - b.y) >= eps)
                return y > b.y+eps;
            return x > b.x+eps;
        }
        bool operator ==(const Point2d & b) const
        {
            return std::abs(y - b.y) < eps && std::abs(x - b.x) < eps;
        }
        bool operator !=(const Point2d & b) const
        {
            return std::abs(y - b.y) > eps || std::abs(x - b.x) > eps;
        }

        ~Point2d();
    };
}



