#include "Point3d.h"

using namespace Shapes3d;
using namespace std;

Point3d::Point3d()
:   x(0), y(0), z(0)
{

}

Point3d::Point3d(double x_val, double y_val, double z_val)
:   x(x_val), y(y_val), z(z_val)
{

}

/* getter and setter */
double Point3d::getX() const
{return x;}

double Point3d::getY() const
{return y;}

double Point3d::getZ() const
{return z;}

void Point3d::setX(double val)
{x = val;}

void Point3d::setY(double val)
{y = val;}

void Point3d::setZ(double val)
{z = val;}

void Point3d::copyPoint(Point3d *p)
{x=p->getX();y=p->getY();z=p->getZ();}

/* norm && distances methods */
double Point3d::norm() const
{
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

double Point3d::dist(Point3d *P) const
{
    return sqrt(pow(x-P->getX(), 2) + pow(y-P->getY(), 2) + pow(z-P->getZ(), 2));
}

Point3d * Point3d::crossProd(Point3d *P)
{
    double x_val = y*P->getZ() - z*P->getY();
    double y_val = -x*P->getZ() + z*P->getX();
    double z_val = x*P->getY() - y*P->getX();
    return new Point3d(x_val, y_val, z_val);
}