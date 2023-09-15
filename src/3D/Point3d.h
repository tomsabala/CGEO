
#pragma once

#include <valarray>
#define eps     0.00000001
namespace Shapes3d{
    class Point3d {
    private:
        double x, y, z;

    public:
        Point3d();
        Point3d(double, double, double);

        /* getter and setter */
        double getX() const;
        double getY() const;
        double getZ() const;
        void setX(double val);
        void setY(double val);
        void setZ(double val);
        void copyPoint(Point3d *p);

        /* norm && distances methods */
        double norm() const;
        double dist(Point3d *P) const;
        Point3d * crossProd(Point3d *P);

        bool operator ==(const Point3d& p) const
        {
            return std::abs(p.getX() - x) <= eps && std::abs(p.getY() - y) <= eps && std::abs(p.getZ() - z) <= eps;
        };

        bool operator !=(const Point3d& p) const
        {
            return std::abs(p.getX() - x) > eps || std::abs(p.getY() - y) > eps || std::abs(p.getZ() - z) > eps;
        };

    };
}
