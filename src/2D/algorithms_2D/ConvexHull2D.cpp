#include "ConvexHull2D.h"
#include <algorithm>

using namespace Algorithms2d;
using namespace Shapes2D;

namespace {
    void processHullHalf(std::stack<Point2d>& stack, std::vector<Point2d>& res,
                         const std::function<bool(std::stack<Point2d>*)>& rightTurn) {
        while (stack.size() > 2 && !rightTurn(&stack)) {
            Point2d tmp = stack.top();
            stack.pop();
            stack.pop();
            stack.push(tmp);
        }
    }
}

Polygon* ConvexHull::grahamConvexHull(Polygon* poly) {
    int n = poly->getSize();
    std::vector<Point2d> sorted_points = sortByX(poly);
    std::stack<Point2d> stack;
    std::vector<Point2d> res;

    stack.push(sorted_points[0]);
    stack.push(sorted_points[1]);

    for (int i = 2; i < n; i++) {
        stack.push(sorted_points[i]);
        while (stack.size() > 2 && !right_turn(&stack)) {
            Point2d tmp = stack.top();
            stack.pop();
            stack.pop();
            stack.push(tmp);
        }
    }

    while (!stack.empty()) {
        res.push_back(stack.top());
        stack.pop();
    }

    stack.push(sorted_points[n - 1]);
    stack.push(sorted_points[n - 2]);
    for (int i = n - 3; i >= 0; i--) {
        stack.push(sorted_points[i]);
        while (stack.size() > 2 && !right_turn(&stack)) {
            Point2d tmp = stack.top();
            stack.pop();
            stack.pop();
            stack.push(tmp);
        }
    }

    while (!stack.empty()) {
        res.push_back(stack.top());
        stack.pop();
    }

    return new Polygon(res);
}

std::vector<Point2d> ConvexHull::sortByX(Polygon* poly) {
    std::vector<Point2d> res = poly->getVertices();
    std::sort(res.begin(), res.end(), [](const Point2d& p, const Point2d& q) {
        return p.getX() < q.getX();
    });
    return res;
}

bool ConvexHull::right_turn(std::stack<Point2d>* s) {
    Point2d third = s->top(); s->pop();
    Point2d second = s->top(); s->pop();
    Point2d first = s->top();
    s->push(second);
    s->push(third);
    return first.oriePred(second, third) < 0;
}

Polygon* ConvexHull::giftWrapConvexHull(Polygon poly) {
    std::vector<Point2d> res;
    Point2d* pointOnHull = poly.getLexMin();
    Point2d* endPoint;

    do {
        res.push_back(*pointOnHull);
        endPoint = poly.getByIndex(0);
        for (int j = 1; j < poly.getSize(); j++) {
            if (endPoint == pointOnHull || res.back().oriePred(*endPoint, *poly.getByIndex(j)) > 0) {
                endPoint = poly.getByIndex(j);
            }
        }
        pointOnHull = endPoint;
    } while (res[0] != *endPoint);

    return new Polygon(res);
}

Polygon* ConvexHull::divideAndConquerConvexHull(Polygon poly) {
    std::vector<Point2d> points = sortByX(&poly);
    return divideAndConquer_rec(points, 0, static_cast<int>(points.size()) - 1);
}

Polygon* ConvexHull::divideAndConquer_rec(const std::vector<Point2d>& points, int i, int j) {
    if (j - i <= 3) {
        return new Polygon(points);
    }

    Polygon* left_p = divideAndConquer_rec(points, i, (i + j) / 2);
    Polygon* right_p = divideAndConquer_rec(points, 1 + (i + j) / 2, j);

    std::vector<int> indices = merge(left_p, right_p);
    std::vector<Point2d> res;

    res.push_back(*left_p->getByIndex(indices[0]));

    int index = indices[1];
    while (index % right_p->getSize() != indices[2]) {
        res.push_back(*right_p->getByIndex(index));
        index++;
    }

    res.push_back(*right_p->getByIndex(indices[2]));
    index = indices[3];
    while (index % left_p->getSize() != indices[0]) {
        res.push_back(*left_p->getByIndex(index));
        index++;
    }

    return new Polygon(res);
}

std::vector<int> ConvexHull::merge(Polygon* left_poly, Polygon* right_poly) {
    int up_left = 0, up_right = 0, down_right = 0, down_left = 0;
    int left_ind = left_poly->getRightMost_index();
    int right_ind = right_poly->getLeftMost_index();

    bool done = false;
    while (!done) {
        int res = merge_inv(left_poly, right_poly, left_ind, right_ind);
        if (res == 0) {
            up_left = left_ind;
            up_right = right_ind;
            done = true;
        } else if (res == 1) {
            left_ind = (left_ind - 1) % left_poly->getSize();
        } else {
            right_ind = (right_ind + 1) % right_poly->getSize();
        }
    }

    done = false;
    while (!done) {
        int res = merge_inv(left_poly, right_poly, left_ind, right_ind);
        if (res == 0) {
            up_left = left_ind;
            up_right = right_ind;
            done = true;
        } else if (res == 1) {
            left_ind = (left_ind + 1) % left_poly->getSize();
        } else {
            right_ind = (right_ind - 1) % right_poly->getSize();
        }
    }

    return {up_left, up_right, down_right, down_left};
}

int ConvexHull::merge_inv(Polygon* left_poly, Polygon* right_poly, int l, int r) {
    int n_left = left_poly->getSize();
    int n_right = right_poly->getSize();

    Point2d* left_up = left_poly->getByIndex((l - 1) % n_left);
    Point2d* left_down = left_poly->getByIndex((l + 1) % n_left);
    Point2d* right_up = right_poly->getByIndex((r - 1) % n_right);
    Point2d* right_down = right_poly->getByIndex((r + 1) % n_right);
    Point2d* left = left_poly->getByIndex(l % n_left);
    Point2d* right = right_poly->getByIndex(r % n_right);

    if (left_up->oriePred(*left, *right) > 0 && left_down->oriePred(*left, *right) < 0) return 1;
    if (right_up->oriePred(*right, *left) < 0 && right_down->oriePred(*right, *left) > 0) return -1;
    return 0;
}

