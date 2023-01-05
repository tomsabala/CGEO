#pragma once

#include "../Shapes_2D/Polygon.h"
#include "../Shapes_2D/Triangle2d.h"
#include <stack>

namespace Algorithms2d{
    class Triangulation2D {
    public:
        std::vector<Triangle2d *>
        triangulate(Shapes2D::Polygon *poly);

        std::vector<Triangle2d *>
        triangulate_YMonotone(Shapes2D::Polygon *poly);

        std::vector<std::pair<Shapes2D::Point2d *, int>>
        sortByY(Shapes2D::Polygon *poly);

        std::pair<std::vector<std::pair<Shapes2D::Point2d *, int>>, std::vector<std::pair<Shapes2D::Point2d *, int>>>
        findLeftRightRails(Shapes2D::Polygon *poly);

        void
        popFromStack(std::vector<Triangle2d *> * res,
                     std::stack<std::pair<Shapes2D::Point2d *, int>> *vertex_Stack,
                     std::pair<Shapes2D::Point2d *, int> p);
    };
}