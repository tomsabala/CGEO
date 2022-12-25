#pragma once

#include "../Shapes_2D/Polygon.h"
#include "../Shapes_2D/Triangle2d.h"

class Triangulation2D {
public:
    std::vector<Triangle2d *>
            triangulate(Shapes2D::Polygon poly);

    std::pair<Shapes2D::Polygon, Shapes2D::Polygon>
    constructPoly(Shapes2D::Polygon p,
                  std::pair<int, int> vertex_ind);

    int getDiagonal(Shapes2D::Polygon p, int v);

    int goodDiagonal(Shapes2D::Polygon poly, int v, int u);
};