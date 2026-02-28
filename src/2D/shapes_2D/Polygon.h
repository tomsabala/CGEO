#pragma once

#include "Point2d.h"
#include "Segment2d.h"
#include <vector>

namespace Shapes2D {
    struct Polygon {
    private:
        std::vector<Point2d> vertices;

        static int next_InnerCusp(Polygon* poly, bool upper);
        static int rightBoundUpperInnerCusp(Polygon* poly, int v);
        static int leftBoundUpperInnerCusp(Polygon* poly, int v);
        static int rightBoundDownInnerCusp(Polygon* poly, int v);
        static int leftBoundDownInnerCusp(Polygon* poly, int v);
        static int findDiagonalFromUpperInnerCusp(Polygon* poly, int innerCusp);
        static int findDiagonalFromDownInnerCusp(Polygon* poly, int innerCusp);

    public:
        Polygon();
        explicit Polygon(const std::vector<Point2d>& v);
        explicit Polygon(const std::vector<Point2d*>& v);

        void insert(const Point2d& p);
        void insert(const Point2d& p, int i);
        Point2d* getByIndex(int i);
        Point2d* getLexMin();
        int getLexMin_index();
        Point2d* getLexMax();
        int getLexMax_index();
        std::vector<Point2d> lexOrder();
        std::vector<Segment2d*> getEdges();
        std::vector<Point2d> getVertices();
        int getSize();
        Point2d* getRightMost();
        Point2d* getLeftMost();
        int getRightMost_index();
        int getLeftMost_index();
        void splice(int pos, Polygon& other, int first, int last);

        bool isConvex();
        bool isY_Monotone();
        bool isInnerCusp(int i);
        bool anyInnerCusp(int i, bool (*func)(Point2d*, Point2d*, Point2d*));
        bool isInPoly(Point2d* p);
        static std::vector<Polygon*> decomposeY_Monotone(Polygon* poly);

        ~Polygon();
    };
}
