#pragma once

#include "Point2d.h"
#include "Segment2d.h"
#include <vector>

namespace Shapes2D{
    struct Polygon {
    private:
        std::vector<Point2d> vertices;
    public:
        /* constructors */
        Polygon();
        explicit Polygon(const std::vector<Point2d>& v);

        /* getter and setter */
        void insert(const Point2d &p);
        void insert(const Point2d &p, int i);
        Point2d* getByIndex(int i);
        Point2d* getLexMin();
        int getLexMin_index();
        Point2d* getLexMax();
        int getLexMax_index();
        std::vector<Point2d> lexOrder();
        std::vector<Segment2d> getEdges();
        std::vector<Point2d> getVertices();
        int getSize();
        Point2d* getRightMost();
        Point2d* getLeftMost();
        int getRightMost_index();
        int getLeftMost_index();

        /* different */
        bool isConvex();
        bool isY_Monotone();
        bool isInnerCusp(int i);

    };
}
