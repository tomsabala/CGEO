#pragma once

#include "../shapes_2D/Polygon.h"
#include "../shapes_2D/Triangle2d.h"
#include <stack>

namespace Algorithms2d{
    class Triangulation2D {
    public:
        static std::vector<Shapes2D::Triangle2d *>
        triangulate(Shapes2D::Polygon *poly);

        static std::vector<Shapes2D::Triangle2d *>
        triangulate_YMonotone(Shapes2D::Polygon *poly);

        static std::vector<std::pair<Shapes2D::Point2d *, int>>
        sortByY(Shapes2D::Polygon *poly);

        static std::pair<std::vector<std::pair<Shapes2D::Point2d *, int>>, std::vector<std::pair<Shapes2D::Point2d *, int>>>
        findLeftRightRails(Shapes2D::Polygon *poly);

        static void
        popFromStack(std::vector<Shapes2D::Triangle2d *> * res,
                     std::stack<std::pair<Shapes2D::Point2d *, int>> *vertex_Stack,
                     std::pair<Shapes2D::Point2d *, int> p);

        ~Triangulation2D()=default;
    };
}