#include "Polygon.h"
#include <algorithm>

using namespace Shapes2D;

namespace {
    double computeEdgeSum(const std::vector<Point2d>& v) {
        double sum = 0;
        for (size_t i = 0; i < v.size(); i++) {
            const Point2d& next = (i == v.size() - 1) ? v[0] : v[i + 1];
            sum += (next.getX() - v[i].getX()) * (next.getY() + v[i].getY());
        }
        return sum;
    }
}

Polygon::Polygon() = default;

Polygon::Polygon(const std::vector<Point2d>& v) {
    if (computeEdgeSum(v) >= 0) {
        vertices.insert(vertices.begin(), v.begin(), v.end());
    } else {
        vertices.insert(vertices.end(), v.rbegin(), v.rend());
    }
}

Polygon::Polygon(const std::vector<Point2d*>& v) {
    std::vector<Point2d> tempVec;
    tempVec.reserve(v.size());
    for (auto* p : v) {
        tempVec.push_back(*p);
    }

    if (computeEdgeSum(tempVec) >= 0) {
        vertices = std::move(tempVec);
    } else {
        vertices.reserve(v.size());
        for (auto it = v.rbegin(); it != v.rend(); ++it) {
            vertices.push_back(**it);
        }
    }
}

void Polygon::insert(const Point2d& p) {
    vertices.push_back(p);
}

void Polygon::insert(const Point2d& p, int i) {
    if (i >= static_cast<int>(vertices.size())) {
        insert(p);
    } else {
        vertices.insert(vertices.begin() + i, p);
    }
}

Point2d* Polygon::getByIndex(int i) {
    if (i < 0) return nullptr;
    if (i >= static_cast<int>(vertices.size())) return &vertices.back();
    return &vertices.at(i);
}

Point2d* Polygon::getLexMin() {
    if (getSize() == 0) return nullptr;
    return new Point2d(*getByIndex(getLexMin_index()));
}

int Polygon::getLexMin_index() {
    if (getSize() == 0) return -1;
    int res = 0;
    for (int i = 1; i < getSize(); i++) {
        if (*getByIndex(i) < *getByIndex(res)) res = i;
    }
    return res;
}

Point2d* Polygon::getLexMax() {
    if (getSize() == 0) return nullptr;
    return new Point2d(*getByIndex(getLexMax_index()));
}

int Polygon::getLexMax_index() {
    if (getSize() == 0) return -1;
    int res = 0;
    for (int i = 1; i < getSize(); i++) {
        if (*getByIndex(res) < *getByIndex(i)) res = i;
    }
    return res;
}

std::vector<Point2d> Polygon::lexOrder() {
    std::vector<Point2d> res(vertices.begin(), vertices.end());
    std::sort(res.begin(), res.end(), [](const Point2d& p, const Point2d& q) {
        return p.getY() < q.getY() || (p.getY() == q.getY() && p.getX() < q.getX());
    });
    return res;
}

std::vector<Segment2d*> Polygon::getEdges() {
    std::vector<Segment2d*> res;
    res.reserve(getSize());
    for (int i = 0; i < getSize(); i++) {
        Point2d& curr = *getByIndex(i);
        Point2d& next = (i == getSize() - 1) ? vertices.front() : *getByIndex(i + 1);
        res.push_back(new Segment2d(curr, next));
    }
    return res;
}

int Polygon::getSize() {
    return static_cast<int>(vertices.size());
}

bool Polygon::isConvex() {
    int n = getSize();
    if (n <= 2) return true;

    bool sign = getByIndex(0)->oriePred(*getByIndex(1), *getByIndex(2)) > 0;
    for (int i = 0; i < n; i++) {
        bool step = getByIndex(i % n)->oriePred(*getByIndex((i + 1) % n), *getByIndex((i + 2) % n)) > 0;
        if (step != sign) return false;
    }
    return true;
}

bool Polygon::isY_Monotone() {
    int n = getSize();
    if (n == 0) return true;

    int h = getLexMax_index();
    int l = getLexMin_index();

    for (int curr = h; curr % n != l; curr++) {
        if (isInnerCusp(curr % n)) return false;
    }
    for (int curr = l; curr % n != h; curr++) {
        if (isInnerCusp(curr % n)) return false;
    }
    return true;
}

bool Polygon::isInnerCusp(int i) {
    int n = getSize();
    double prev_y = getByIndex(i == 0 ? n - 1 : i - 1)->getY();
    double next_y = getByIndex((i + 1) % n)->getY();
    double curr_y = getByIndex(i)->getY();

    return (prev_y > curr_y && next_y > curr_y) || (prev_y < curr_y && next_y < curr_y);
}

bool Polygon::anyInnerCusp(int i, bool (*func)(Point2d*, Point2d*, Point2d*)) {
    int n = getSize();
    int pred = (i == 0) ? n - 1 : i - 1;
    int succ = (i == n - 1) ? 0 : i + 1;
    return func(getByIndex(pred), getByIndex(i), getByIndex(succ));
}

std::vector<Point2d> Polygon::getVertices() {
    return vertices;
}

Point2d* Polygon::getRightMost() {
    if (getSize() == 0) return nullptr;
    return new Point2d(*getByIndex(getRightMost_index()));
}

int Polygon::getRightMost_index() {
    int res = 0;
    for (int i = 1; i < getSize(); i++) {
        if (getByIndex(res)->getX() < getByIndex(i)->getX()) res = i;
    }
    return res;
}

Point2d* Polygon::getLeftMost() {
    if (getSize() == 0) return nullptr;
    return new Point2d(*getByIndex(getLeftMost_index()));
}

int Polygon::getLeftMost_index() {
    int res = 0;
    for (int i = 1; i < getSize(); i++) {
        if (getByIndex(res)->getX() > getByIndex(i)->getX()) res = i;
    }
    return res;
}

bool Polygon::isInPoly(Point2d* p) {
    int crossings = 0;
    std::vector<Segment2d*> edges = getEdges();

    for (const Segment2d* e : edges) {
        if (e->getUpper().getY() > p->getY() && e->getLower().getY() < p->getY()) {
            if (e->getLower().oriePred(e->getUpper(), *p) > 0) {
                crossings = !crossings;
            }
        }
    }

    for (auto* e : edges) delete e;
    return crossings;
}

int Polygon::next_InnerCusp(Polygon* poly, bool upper) {
    int n = poly->getSize();

    auto upperCusp = [](Point2d* a, Point2d* b, Point2d* c) {
        return a->getY() > b->getY() && c->getY() > b->getY() && a->oriePred(*b, *c) > 0;
    };

    auto lowerCusp = [](Point2d* a, Point2d* b, Point2d* c) {
        return a->getY() < b->getY() && c->getY() < b->getY() && a->oriePred(*b, *c) > 0;
    };

    for (int i = 0; i < n; i++) {
        if (poly->anyInnerCusp(i, upper ? upperCusp : lowerCusp)) {
            return i;
        }
    }
    return -1;
}

int Polygon::leftBoundDownInnerCusp(Polygon* poly, int v) {
    int n = poly->getSize();
    double v_y = poly->getByIndex(v)->getY();

    for (int i = (v + 1) % n; i != v; i = (i + 1) % n) {
        if (poly->getByIndex(i)->getY() >= v_y) return i;
    }
    return -1;
}

int Polygon::rightBoundDownInnerCusp(Polygon* poly, int v) {
    int n = poly->getSize();
    double v_y = poly->getByIndex(v)->getY();

    for (int i = (v == 0) ? n - 1 : v - 1; i != v; i = (i == 0) ? n - 1 : i - 1) {
        if (poly->getByIndex(i)->getY() >= v_y) return i;
    }
    return -1;
}

int Polygon::leftBoundUpperInnerCusp(Polygon* poly, int v) {
    int n = poly->getSize();
    double v_y = poly->getByIndex(v)->getY();

    for (int i = (v == 0) ? n - 1 : v - 1; i != v; i = (i == 0) ? n - 1 : i - 1) {
        if (poly->getByIndex(i)->getY() <= v_y) return i;
    }
    return -1;
}

int Polygon::rightBoundUpperInnerCusp(Polygon* poly, int v) {
    int n = poly->getSize();
    double v_y = poly->getByIndex(v)->getY();

    for (int i = (v + 1) % n; i != v; i = (i + 1) % n) {
        if (poly->getByIndex(i)->getY() <= v_y) return i;
    }
    return -1;
}

int Polygon::findDiagonalFromUpperInnerCusp(Polygon* poly, int innerCusp) {
    int n = poly->getSize();
    int leftBound = leftBoundUpperInnerCusp(poly, innerCusp);
    int rightBound = rightBoundUpperInnerCusp(poly, innerCusp);

    Point2d* left_point = poly->getByIndex(leftBound);
    Point2d* right_point = poly->getByIndex(rightBound);

    auto lowerCusp = [](Point2d* a, Point2d* b, Point2d* c) {
        return a->getY() < b->getY() && c->getY() < b->getY() && a->oriePred(*b, *c) > 0;
    };

    int u = -1;
    for (int i = rightBound; i != leftBound; i = (i + 1) % n) {
        Point2d* p = poly->getByIndex(i);
        if (p->getX() >= left_point->getX() && p->getX() <= right_point->getX()) {
            if (poly->anyInnerCusp(i, lowerCusp)) return i;
            if (u == -1 || poly->getByIndex(u)->getY() < p->getY()) u = i;
        }
    }
    return (u == -1) ? leftBound : u;
}

int Polygon::findDiagonalFromDownInnerCusp(Polygon* poly, int innerCusp) {
    int n = poly->getSize();
    int leftBound = leftBoundDownInnerCusp(poly, innerCusp);
    int rightBound = rightBoundDownInnerCusp(poly, innerCusp);

    Point2d* left_point = poly->getByIndex(leftBound);
    Point2d* right_point = poly->getByIndex(rightBound);

    auto upperCusp = [](Point2d* a, Point2d* b, Point2d* c) {
        return a->getY() > b->getY() && c->getY() > b->getY() && a->oriePred(*b, *c) > 0;
    };

    int u = -1;
    for (int i = leftBound; i != rightBound; i = (i + 1) % n) {
        Point2d* p = poly->getByIndex(i);
        if (p->getX() >= left_point->getX() && p->getX() <= right_point->getX()) {
            if (poly->anyInnerCusp(i, upperCusp)) return i;
            if (u == -1 || poly->getByIndex(u)->getY() > p->getY()) u = i;
        }
    }
    return (u == -1) ? rightBound : u;
}

namespace {
    void splitPolygonAt(Polygon* poly, int cusp, int u, std::vector<Polygon*>& result) {
        int n = poly->getSize();
        std::vector<Point2d*> poly1_points, poly2_points;

        for (int i = cusp; i != u; i = (i + 1) % n) {
            poly1_points.push_back(poly->getByIndex(i));
        }
        poly1_points.push_back(poly->getByIndex(u));

        for (int i = u; i != cusp; i = (i + 1) % n) {
            poly2_points.push_back(poly->getByIndex(i));
        }
        poly2_points.push_back(poly->getByIndex(cusp));

        auto* poly1 = new Polygon(poly1_points);
        auto* poly2 = new Polygon(poly2_points);

        auto left = Polygon::decomposeY_Monotone(poly1);
        auto right = Polygon::decomposeY_Monotone(poly2);

        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
    }
}

std::vector<Polygon*> Polygon::decomposeY_Monotone(Polygon* poly) {
    std::vector<Polygon*> res;

    int downCusp = next_InnerCusp(poly, false);
    if (downCusp != -1) {
        int u = findDiagonalFromDownInnerCusp(poly, downCusp);
        splitPolygonAt(poly, downCusp, u, res);
        return res;
    }

    int upperCusp = next_InnerCusp(poly, true);
    if (upperCusp != -1) {
        int u = findDiagonalFromUpperInnerCusp(poly, upperCusp);
        splitPolygonAt(poly, upperCusp, u, res);
        return res;
    }

    res.push_back(poly);
    return res;
}

Polygon::~Polygon() = default;

void Polygon::splice(int pos, Polygon& other, int first, int last) {
    auto pos_it = vertices.begin() + pos;
    auto begin_it = other.vertices.begin() + first;
    auto end_it = other.vertices.begin() + last;
    vertices.insert(pos_it, begin_it, end_it);
}
