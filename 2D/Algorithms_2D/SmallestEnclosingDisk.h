#pragma once

#include "../Shapes_2D/Circle2d.h"
#include "../Shapes_2D/Triangle2d.h"
#include <vector>


namespace Algorithms2d{
    class SmallestEnclosingDisk {
    public:
        SmallestEnclosingDisk();

        Shapes2D::Circle2d *
        findDisc(std::vector<Shapes2D::Point2d *>);

    private:
        Shapes2D::Circle2d *
        findDisc_withOnePoint(std::vector<Shapes2D::Point2d *>, std::vector<int>, int);

        Shapes2D::Circle2d *
        findDisc_withTwoPoints(std::vector<Shapes2D::Point2d *>, std::vector<int>, int, int);

        std::vector<int>
        shuffle(int );

        std::vector<int>
        shuffle(std::vector<int>, int);

        bool
        checkIfValid(Shapes2D::Circle2d *, std::vector<Shapes2D::Point2d *>, std::vector<int>, int );

        Shapes2D::Circle2d*
        findSmallestCircle(Shapes2D::Circle2d *, Shapes2D::Circle2d *, Shapes2D::Circle2d *);

    };
}
