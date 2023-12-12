#pragma once

#include "Point2d.h"
#include "Segment2d.h"

namespace Shapes2D{

    class Triangle2d {
    public:
        std::vector<Shapes2D::Point2d> vertex;

        Triangle2d(Shapes2D::Point2d p, Shapes2D::Point2d q, Shapes2D::Point2d t);
        std::vector<Shapes2D::Point2d> getVertices();
        Shapes2D::Point2d getA();
        Shapes2D::Point2d getB();
        Shapes2D::Point2d getC();
        void setA(Shapes2D::Point2d p);
        void setB(Shapes2D::Point2d p);
        void setC(Shapes2D::Point2d p);
        double area();
        bool isWide();
        static bool isWide(Shapes2D::Point2d A, Shapes2D::Point2d B, Shapes2D::Point2d C);

        ~Triangle2d() = default;
    };
}