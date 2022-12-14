
#include <iostream>
#include "SmallestEnclosingDisk.h"

using namespace Algorithms2d;

/* empty default constructor */
SmallestEnclosingDisk::SmallestEnclosingDisk() {}

/**
 * we are getting a set of points in the plane,
 * and we wish to find to smallest enclosing disc surrounding these points
 * @param points : set of points in the plane
 * @return a Circle in the plane.
 */
Shapes2D::Circle2d *SmallestEnclosingDisk::findDisc(std::vector<Shapes2D::Point2d *> points) {
    std::vector<int> permutation = shuffle(points.size());

    /* init circle */
    Shapes2D::Circle2d *circle = new Shapes2D::Circle2d(points[permutation[0]],
                                                        points[permutation[1]]);


    for (int i=2; i<permutation.size(); ++i)
        if (circle->pointContains(points[permutation[i]]) == -1)
            circle = findDisc_withOnePoint(points, permutation, i);

    return circle;
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
SmallestEnclosingDisk::findDisc_withOnePoint(std::vector<Shapes2D::Point2d *> points, std::vector<int> permutation, int I) {
    std::vector<int> new_perm = shuffle(permutation, I);

    /* init circle */
    Shapes2D::Circle2d *circle = new Shapes2D::Circle2d(points[new_perm[0]],
                                                        points[permutation[I]]);

    for (int i=1; i<new_perm.size(); ++i)
        if (circle->pointContains(points[new_perm[i]]) == -1)
            circle = findDisc_withTwoPoints(points, new_perm, i, permutation[I]);

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
SmallestEnclosingDisk::findDisc_withTwoPoints(std::vector<Shapes2D::Point2d *> points,
                                              std::vector<int> permutation, int I, int J) {

    Shapes2D::Circle2d *circ = new Shapes2D::Circle2d(points[permutation[I]], points[J]);

    for (int i=0; i<I; i++)
        if (circ->pointContains(points[permutation[i]]) == -1)
            circ->setCircle(points[permutation[I]], points[J], points[permutation[i]]);

    return circ;
}

std::vector<int> SmallestEnclosingDisk::shuffle(int N) {
    int r, tmp;

    std::vector<int> res(N, 0);
    for (int i=0; i<N; i++)
        res[i] = i;

    srand((unsigned)time(NULL));
    for (int i=0; i<N; i++)
    {
        r = (rand()%(N-i)) + i;
        tmp = res[i];
        res[i] = res[r];
        res[r] = tmp;
    }

    return res;
}

std::vector<int> SmallestEnclosingDisk::shuffle(std::vector<int> permutation, int I) {
    int r, tmp;
    std::vector<int> res(I, 0);

    for (int i = 0; i <= I; ++i)
        res[i] = permutation[i];

    srand((unsigned) time(NULL));
    for (int j=0; j<I; j++) {
        r = (rand()%(I-j)) + j;
        tmp = res[j];
        res[j] = res[r];
        res[r] = tmp;
    }

    return res;
}

