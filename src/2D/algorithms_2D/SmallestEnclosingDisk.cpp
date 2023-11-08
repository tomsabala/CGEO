
#include <random>
#include <algorithm>
#include "SmallestEnclosingDisk.h"

using namespace Algorithms2d;

/* empty default constructor */
SmallestEnclosingDisk::SmallestEnclosingDisk() = default;

/**
 * we are getting a set of points in the plane,
 * and we wish to find to smallest enclosing disc surrounding these points
 * @param points : set of points in the plane
 * @return a Circle in the plane.
 */
Shapes2D::Circle2d *SmallestEnclosingDisk::findDisc(std::vector<Shapes2D::Point2d >& points)
{

    std::shuffle(points.begin(), points.end(), std::mt19937(std::random_device()()));

    /* init ret */
    auto *ret = new Shapes2D::Circle2d(points.at(0),
                                       points.at(1));


    for (int i=2; i<points.size(); ++i)
        if (ret->pointContains(&points.at(i)) == -1)
        {
            std::swap(*ret, *findDisc_withOnePoint(points, i));
        }

    return ret;
}

/**
 * * find smallest enclosing disc of a subset of points in `points`
 * such that points[permutation[I]] is strictly on its sphere.
 * @param points a set of points in the plane
 * @param permutation a subset of points indices to be included in the disc
 * @param I : point to be strictly added to the circle
 * @return a circle that includes all points with indices in permutation
 */
Shapes2D::Circle2d *
SmallestEnclosingDisk::findDisc_withOnePoint(std::vector<Shapes2D::Point2d >& points, int I)
{

    /* init circle */
    auto *circle = new Shapes2D::Circle2d(points.at(0),
                                                        points.at(I));

    for (int i=1; i<I; ++i)
        if (circle->pointContains(&points.at(i)) == -1)
        {
            std::swap(*circle, *findDisc_withTwoPoints(points, i, I));
         }


    return circle;
}

/**
 * find smallest enclosing disc of a subset of points in `points`
 * such that points[permutation[I]] and points[permutation[J]] are strictly on its sphere.
 * @param points a set of points in the plane
 * @param permutation a subset of points indices to be included in the disc
 * @param I, J : two point to be strictly added to the circle.
 * @return a circle that includes all points with indices in permutation
 */
Shapes2D::Circle2d *
SmallestEnclosingDisk::findDisc_withTwoPoints(std::vector<Shapes2D::Point2d >& points,
                                              int I, int J) {

    auto *circ = new Shapes2D::Circle2d(points.at(I), points.at(J));

    for (int i=0; i<I; i++)
        if (circ->pointContains(&points.at(i)) == -1)
            circ->setCircle(&points.at(I), &points.at(J), &points.at(i));

    return circ;
}
