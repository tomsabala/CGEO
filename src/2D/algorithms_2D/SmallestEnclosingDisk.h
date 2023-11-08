#pragma once

#include "../shapes_2D/Circle2d.h"
#include "../shapes_2D/Triangle2d.h"
#include <vector>


namespace Algorithms2d{
    class SmallestEnclosingDisk {
    public:
        SmallestEnclosingDisk();

        static Shapes2D::Circle2d *
        findDisc(std::vector<Shapes2D::Point2d >& );

    private:
        static Shapes2D::Circle2d *
        findDisc_withOnePoint(std::vector<Shapes2D::Point2d >& , int);

        static Shapes2D::Circle2d *
        findDisc_withTwoPoints(std::vector<Shapes2D::Point2d >& , int, int);
    };
}
