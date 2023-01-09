
#include "SmallestEnclisingDisk.h"

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
    if (points.size() == 3)
        return new Shapes2D::Circle2d(points[0], points[1], points[2]);

    std::vector<int> permutation = shuffle(points.size());

    /* init circle */
    Shapes2D::Circle2d *circle = new Shapes2D::Circle2d(points[permutation[0]],
                                                        points[permutation[1]],
                                                        points[permutation[2]]);

    for (int i=4; i<permutation.size(); ++i)
    {
        Shapes2D::Point2d *curr_point = points[permutation[i]];
        if (circle->pointContains(curr_point))
            continue;
        circle = findDisc_withOnePoint(points, permutation, i);
    }

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
    std::vector<int> new_perm = shuffle(permutation, I-1);

    /* init circle */
    Shapes2D::Circle2d *circle = new Shapes2D::Circle2d(points[new_perm[0]],
                                                        points[new_perm[1]],
                                                        points[I]);

    for (int i=3; i<new_perm.size(); ++i)
    {
        Shapes2D::Point2d *curr_point = points[new_perm[i]];
        if (circle->pointContains(curr_point))
            continue;
        circle = findDisc_withTwoPoints(points, new_perm, i, I);
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
SmallestEnclosingDisk::findDisc_withTwoPoints(std::vector<Shapes2D::Point2d *> points, std::vector<int> permutation, int I, int J) {
    std::vector<int> new_perm = shuffle(permutation, I-1);

    /* init circle */
    Shapes2D::Circle2d *circle = new Shapes2D::Circle2d(points[new_perm[0]],
                                                        points[new_perm[I]],
                                                        points[J]);

    for (int i=3; i<new_perm.size(); ++i)
    {
        Shapes2D::Point2d *curr_point = points[new_perm[i]];
        if (circle->pointContains(curr_point))
            continue;
        circle = new Shapes2D::Circle2d(points[I], points[J], curr_point);
    }

    return circle;
}

std::vector<int> SmallestEnclosingDisk::shuffle(int N) {
    std::vector<int> res(N, 0);
    for (int i=0; i<N; ++i)
    {
        res[i] = i;
    }
    srand((unsigned)time(NULL));
    for (int i=0; i<N; i++)
    {
        int r = (rand()%(N-i)) + i;
        res[i] = r;
        res[r] = i;
    }

    return res;
}

std::vector<int> SmallestEnclosingDisk::shuffle(std::vector<int> permutation, int I) {
    std::vector<int> res(I, 0);
    for (int i = 0; i <= I; ++i) {
        res[i] = permutation[i];
    }
    srand((unsigned) time(NULL));
    for (int i = 0; i <= I; i++) {
        int r = (rand() % (I - i)) + i;
        int tmp = res[i];
        res[i] = r;
        res[r] = tmp;
    }

    return res;
}

