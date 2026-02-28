#pragma once

#include "../shapes_2D/Polygon.h"
#include "../shapes_2D/Triangle2d.h"
#include <stack>
#include <utility>

namespace Algorithms2d {
    using VertexInfo = std::pair<Shapes2D::Point2d*, int>;
    using VertexInfoVec = std::vector<VertexInfo>;

    class Triangulation2D {
    public:
        static std::vector<Shapes2D::Triangle2d*> triangulate(Shapes2D::Polygon* poly);
        static std::vector<Shapes2D::Triangle2d*> triangulate_YMonotone(Shapes2D::Polygon* poly);
        static VertexInfoVec sortByY(Shapes2D::Polygon* poly);
        static std::pair<VertexInfoVec, VertexInfoVec> findLeftRightRails(Shapes2D::Polygon* poly);
        static void popFromStack(std::vector<Shapes2D::Triangle2d*>* res,
                                 std::stack<VertexInfo>* vertex_Stack,
                                 VertexInfo p);

        ~Triangulation2D() = default;
    };
}