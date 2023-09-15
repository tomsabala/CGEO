
#pragma once
#include "Point3d.h"

namespace Shapes3d{
    class Face3d {
    private:
        std::pair<Point3d *, int> p, q, t;
        void swap(std::pair<Point3d *, int> *x, std::pair<Point3d *, int> *y);


    public:
        Face3d();
        Face3d(Point3d P, Point3d Q, Point3d T);

        /* getter and setter */
        Point3d * getByIndex(int i);
        void setByIndex(int i, Point3d *P);
        void twist();

        bool isDegenerated();
        int areaSign(Point3d *P);

    };
}

