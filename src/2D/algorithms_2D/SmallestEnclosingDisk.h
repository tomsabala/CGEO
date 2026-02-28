#pragma once

#include "../shapes_2D/Circle2d.h"
#include <vector>

namespace Algorithms2d {
    class SmallestEnclosingDisk {
    public:
        SmallestEnclosingDisk();
        ~SmallestEnclosingDisk() = default;

        static Shapes2D::Circle2d* findDisc(std::vector<Shapes2D::Point2d>& points);

    private:
        static Shapes2D::Circle2d* findDisc_withOnePoint(std::vector<Shapes2D::Point2d>& points, int I);
        static Shapes2D::Circle2d* findDisc_withTwoPoints(std::vector<Shapes2D::Point2d>& points, int I, int J);
    };
}
