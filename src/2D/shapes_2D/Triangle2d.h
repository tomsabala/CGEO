#pragma once

#include "Point2d.h"
#include <vector>

namespace Shapes2D {
    class Triangle2d {
    public:
        std::vector<Point2d> vertex;

        Triangle2d(Point2d p, Point2d q, Point2d t);

        std::vector<Point2d> getVertices();
        Point2d getA();
        Point2d getB();
        Point2d getC();
        void setA(Point2d p);
        void setB(Point2d p);
        void setC(Point2d p);

        double area();
        bool isWide();
        static bool isWide(Point2d A, Point2d B, Point2d C);

        ~Triangle2d() = default;
    };
}