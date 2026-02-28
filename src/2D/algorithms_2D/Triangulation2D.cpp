#include "Triangulation2D.h"

using namespace Algorithms2d;
using namespace Shapes2D;

std::vector<Triangle2d*> Triangulation2D::triangulate(Polygon* poly) {
    std::vector<Triangle2d*> res;
    std::vector<Polygon*> decomposed = Polygon::decomposeY_Monotone(poly);

    for (Polygon* sub_poly : decomposed) {
        auto sub_res = triangulate_YMonotone(sub_poly);
        res.insert(res.end(), sub_res.begin(), sub_res.end());
    }

    return res;
}

std::vector<Triangle2d*> Triangulation2D::triangulate_YMonotone(Polygon* poly) {
    std::vector<Triangle2d*> res;

    if (poly->getSize() == 3) {
        res.push_back(new Triangle2d(*poly->getByIndex(0), *poly->getByIndex(1), *poly->getByIndex(2)));
        return res;
    }

    std::stack<VertexInfo> vertex_Stack;
    VertexInfoVec sorted_vertex = sortByY(poly);

    vertex_Stack.push(sorted_vertex[0]);
    vertex_Stack.push(sorted_vertex[1]);

    for (size_t i = 2; i < sorted_vertex.size(); i++) {
        popFromStack(&res, &vertex_Stack, sorted_vertex[i]);
    }

    return res;
}

void Triangulation2D::popFromStack(std::vector<Triangle2d*>* res,
                                   std::stack<VertexInfo>* vertex_Stack,
                                   VertexInfo p) {
    bool sameRail = (p.second == vertex_Stack->top().second);

    if (sameRail) {
        while (vertex_Stack->size() >= 2) {
            VertexInfo first_pair = vertex_Stack->top(); vertex_Stack->pop();
            VertexInfo second_pair = vertex_Stack->top(); vertex_Stack->pop();

            double orientation = p.first->oriePred(*first_pair.first, *second_pair.first);
            bool validTriangle = p.second ? (orientation > 0) : (orientation < 0);

            if (validTriangle) {
                res->push_back(new Triangle2d(*p.first, *first_pair.first, *second_pair.first));
                vertex_Stack->push(second_pair);
            } else {
                vertex_Stack->push(second_pair);
                vertex_Stack->push(first_pair);
                break;
            }
        }
    } else {
        VertexInfo last_p = vertex_Stack->top();
        while (vertex_Stack->size() >= 2) {
            VertexInfo first_pair = vertex_Stack->top(); vertex_Stack->pop();
            VertexInfo second_pair = vertex_Stack->top(); vertex_Stack->pop();

            double orientation = p.first->oriePred(*first_pair.first, *second_pair.first);
            bool validTriangle = p.second ? (orientation < 0) : (orientation > 0);

            if (validTriangle) {
                res->push_back(new Triangle2d(*p.first, *first_pair.first, *second_pair.first));
                if (vertex_Stack->empty()) break;
                vertex_Stack->push(second_pair);
            } else {
                vertex_Stack->push(second_pair);
                vertex_Stack->push(first_pair);
                break;
            }
        }
        vertex_Stack->push(last_p);
    }

    vertex_Stack->push(p);
}

VertexInfoVec Triangulation2D::sortByY(Polygon* poly) {
    auto rails = findLeftRightRails(poly);
    VertexInfoVec res;

    size_t leftIdx = 0, rightIdx = 0;
    while (leftIdx < rails.first.size() && rightIdx < rails.second.size()) {
        if (rails.first[leftIdx].first->getY() > rails.second[rightIdx].first->getY()) {
            res.push_back(rails.first[leftIdx++]);
        } else {
            res.push_back(rails.second[rightIdx++]);
        }
    }

    while (leftIdx < rails.first.size()) res.push_back(rails.first[leftIdx++]);
    while (rightIdx < rails.second.size()) res.push_back(rails.second[rightIdx++]);

    return res;
}

std::pair<VertexInfoVec, VertexInfoVec> Triangulation2D::findLeftRightRails(Polygon* poly) {
    int n = poly->getSize();
    int upperIndex = 0, lowerIndex = 0;

    for (int i = 0; i < n; ++i) {
        if (poly->getByIndex(i)->getY() > poly->getByIndex(upperIndex)->getY()) upperIndex = i;
        if (poly->getByIndex(i)->getY() < poly->getByIndex(lowerIndex)->getY()) lowerIndex = i;
    }

    VertexInfoVec leftRail, rightRail;

    for (int i = upperIndex; i != lowerIndex; i = (i + 1) % n) {
        rightRail.emplace_back(poly->getByIndex(i), 1);
    }

    int startLeft = (upperIndex == 0) ? n - 1 : upperIndex - 1;
    for (int i = startLeft; i != lowerIndex; i = (i == 0) ? n - 1 : i - 1) {
        leftRail.emplace_back(poly->getByIndex(i), 0);
    }
    leftRail.emplace_back(poly->getByIndex(lowerIndex), 0);

    return {leftRail, rightRail};
}
