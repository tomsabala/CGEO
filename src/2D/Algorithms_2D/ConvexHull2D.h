#ifndef CGEO_CONVEXHULL2D_H
#define CGEO_CONVEXHULL2D_H

#include <stack>
#include "../Shapes_2D/Point2d.h"
#include "../Shapes_2D/Segment2d.h"
#include "../Shapes_2D/Polygon.h"

namespace Algorithms2d{
    struct ConvexHull {
    public:
        ConvexHull()= default;;

        Shapes2D::Polygon* grahamConvexHull(Shapes2D::Polygon poly);
        Shapes2D::Polygon* giftWrapConvexHull(Shapes2D::Polygon poly);
        Shapes2D::Polygon* divideAndConquerConvexHull(Shapes2D::Polygon poly);

    private:
        static std::vector<Shapes2D::Point2d> sortByX(Shapes2D::Polygon* poly);
        static bool right_turn(std::stack<Shapes2D::Point2d> *s);
        Shapes2D::Polygon* divideAndConquer_rec(std::vector<Shapes2D::Point2d> points, int i, int j);
        std::vector<int> merge(Shapes2D::Polygon *left_poly, Shapes2D::Polygon *right_poly);
        int merge_inv(Shapes2D::Polygon *left_poly, Shapes2D::Polygon *right_poly, int l, int r);
    };
}


#endif //CGEO_CONVEXHULL2D_H
