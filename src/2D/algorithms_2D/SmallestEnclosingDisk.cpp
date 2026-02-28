#include "SmallestEnclosingDisk.h"
#include <random>
#include <algorithm>

using namespace Algorithms2d;
using namespace Shapes2D;

SmallestEnclosingDisk::SmallestEnclosingDisk() = default;

Circle2d* SmallestEnclosingDisk::findDisc(std::vector<Point2d>& points) {
    std::shuffle(points.begin(), points.end(), std::mt19937(std::random_device()()));

    auto* ret = new Circle2d(points.at(0), points.at(1));

    for (size_t i = 2; i < points.size(); ++i) {
        if (ret->pointContains(points.at(i)) == -1) {
            Circle2d* newCircle = findDisc_withOnePoint(points, static_cast<int>(i));
            std::swap(*ret, *newCircle);
            delete newCircle;
        }
    }

    return ret;
}

Circle2d* SmallestEnclosingDisk::findDisc_withOnePoint(std::vector<Point2d>& points, int I) {
    auto* circle = new Circle2d(points.at(0), points.at(I));

    for (int i = 1; i < I; ++i) {
        if (circle->pointContains(points.at(i)) == -1) {
            Circle2d* newCircle = findDisc_withTwoPoints(points, i, I);
            std::swap(*circle, *newCircle);
            delete newCircle;
        }
    }

    return circle;
}

Circle2d* SmallestEnclosingDisk::findDisc_withTwoPoints(std::vector<Point2d>& points, int I, int J) {
    auto* circ = new Circle2d(points.at(I), points.at(J));

    for (int i = 0; i < I; i++) {
        if (circ->pointContains(points.at(i)) == -1) {
            circ->setCircle(&points.at(I), &points.at(J), &points.at(i));
        }
    }

    return circ;
}
