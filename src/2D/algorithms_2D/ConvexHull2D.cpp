
#include <algorithm>
#include "ConvexHull2D.h"

using namespace Algorithms2d;

/**
 * the graham algorithm is an O(nlog(n)) algo. for finding the convex hull of a polygon.
 * the algorithms sorts the points by their x-axis and then eliminate points one by one from being part of the convex.
 * @param poly is a polygon in the plane xy.
 * @return subset of Points picked from the original polygon, which forms the convex hull.
 * @url https://en.wikipedia.org/wiki/Graham_scan
 */
Shapes2D::Polygon *ConvexHull::grahamConvexHull(Shapes2D::Polygon *poly) {
    int n = poly->getSize();
    /* init sorted vector, result and stack for algorithm */
    std::vector<Shapes2D::Point2d> sorted_points = sortByX(poly);
    std::stack<Shapes2D::Point2d> stack;
    std::vector<Shapes2D::Point2d> res;

    /* push first two points */
    stack.push(sorted_points[0]);
    stack.push(sorted_points[1]);

    /*
     * in each iter. while stack.size > 2 find valid turn
     * that way we can say the invariant is: in each iter. the stack is full of valid turns
     * */
    for (int i=2; i<n; i++) {
        stack.push(sorted_points[i]);
        while(stack.size()>2 && !right_turn(&stack)) {
            Shapes2D::Point2d tmp = stack.top();
            stack.pop();
            stack.top(); /* very weired .... */
            stack.pop();
            stack.push(tmp);
        }
    }

    /* copy points to res */
    while(!stack.empty()) {
        res.push_back(stack.top());
        stack.pop();
    }

    /* do the same for the lower points */
    stack.push(sorted_points[n-1]);
    stack.push(sorted_points[n-2]);
    for (int i=n-3; i>=0; i--) {
        stack.push(sorted_points[i]);
        while(stack.size()>2 && !right_turn(&stack)) {
            Shapes2D::Point2d tmp = stack.top();
            stack.pop();
            stack.top(); /* very weired .... */
            stack.pop();
            stack.push(tmp);
        }
    }

    /* copy points to res */
    while(!stack.empty()) {
        res.push_back(stack.top());
        stack.pop();
    }

    return new Shapes2D::Polygon(res);
}

/**
 * this function responsible for sorting the Points in the Polygon poly. by their x-axis.
 * @param poly Polygon type object
 * @return vector of type Point2d
 */
std::vector<Shapes2D::Point2d> ConvexHull::sortByX(Shapes2D::Polygon* poly) {
    std::vector<Shapes2D::Point2d> res = poly->getVertices();
    std::sort(res.begin(), res.end(), [ ]( const Shapes2D::Point2d& p, const Shapes2D::Point2d& q )
    {
        return p.getX() < q.getX();
    });
    return res;
}

/**
 * this function is responsible for checking if the last three Points in s are performing a right turn.
 * @param s stack of type Point2d
 * @return boolean value
 */
bool ConvexHull::right_turn(std::stack<Shapes2D::Point2d> *s) {
    /* pick three last points */
    Shapes2D::Point2d third = s->top();
    s->pop();
    Shapes2D::Point2d second = s->top();
    s->pop();
    Shapes2D::Point2d first = s->top();
    s->push(second);
    s->push(third);

    /* perform turn checking */
    return first.oriePred(second, third) < 0;
}

/**
 * the algorithm is O(nh) for finding the convex hull of a given polygon, where h is the number of vertices of the output
 * in each step the algorithm finds the next point which is belong to the convex by checking all possibilities.
 * @param poly is a polygon in the plane xy
 * @return subset of Points picked from the original polygon, which forms the convex hull.
 * @url https://en.wikipedia.org/wiki/Gift_wrapping_algorithm
 */
Shapes2D::Polygon *ConvexHull::giftWrapConvexHull(Shapes2D::Polygon poly) {
    /* init res and point candidate ptr */
    std::vector<Shapes2D::Point2d> res;
    Shapes2D::Point2d* pointOnHull = poly.getLexMin();
    Shapes2D::Point2d *endPoint;

    /*
     * in every iter we find the next point to be on the hull
     * each iter will take O(n) time
     * overall will make h iterations while h is the number of vertices on the convex hull
     * */
    do {
        res.push_back(*pointOnHull);
        endPoint = poly.getByIndex(0);
        for (int j=1; j<poly.getSize(); j++){
            if (endPoint == pointOnHull || res.back().oriePred(*endPoint, *poly.getByIndex(j)) > 0) {
                endPoint = poly.getByIndex(j);
            }
        }
        pointOnHull = endPoint;
    }while (res[0] != *endPoint);

    return new Shapes2D::Polygon(res);
}

/**
 * the algorithm is O(nlog(n)) for finding the convex hull of a given polygon.
 * the algorithm, in his idea, is similar to merge-sort.
 * we first divide the polygon into two subset of polygon, compute the convex hull of each one,
 * and then merge the two convex polygons into one.
 * the splitting is occurring until the number of vertices on the input is s.t. the convex hull can be computed with O(1).
 * @param poly is a polygon in the xy plane
 * @return subset of Points picked from the original polygon, which forms the convex hull.
 * @url https://www.geeksforgeeks.org/convex-hull-using-divide-and-conquer-algorithm/
 */
Shapes2D::Polygon *ConvexHull::divideAndConquerConvexHull(Shapes2D::Polygon poly) {
    auto *res = (Shapes2D::Polygon *) malloc(sizeof (Shapes2D::Polygon));

    std::vector<Shapes2D::Point2d> points = sortByX(&poly);
    res = this->divideAndConquer_rec(points, 0, (int)points.size()-1);
    return res;
}

Shapes2D::Polygon *ConvexHull::divideAndConquer_rec(const std::vector<Shapes2D::Point2d>& points, int i, int j) {
    if (j - i <= 3) {
        return new Shapes2D::Polygon(points);
    }
    Shapes2D::Polygon *left_p = divideAndConquer_rec(points, i, (i+j)/2);
    Shapes2D::Polygon *right_p = divideAndConquer_rec(points, 1+(i+j)/2, j);

    std::vector<int> indices = merge(left_p, right_p);
    std::vector<Shapes2D::Point2d> res;

    res.push_back(*left_p->getByIndex(indices[0]));

    int index = indices[1];
    while(index%right_p->getSize() != indices[2]){
        res.push_back(*right_p->getByIndex(index));
        index++;
    }

    res.push_back(*right_p->getByIndex(indices[2]));
    index = indices[3];
    while(index%left_p->getSize() != indices[0]){
        res.push_back(*left_p->getByIndex(index));
        index++;
    }

    return new Shapes2D::Polygon(res);
}

std::vector<int> ConvexHull::merge(Shapes2D::Polygon *left_poly, Shapes2D::Polygon *right_poly) {
    int up_left, up_right, down_left, down_right;

    int left_ind = left_poly->getRightMost_index();
    int right_ind = right_poly->getLeftMost_index();

    bool done = false;
    while(!done) {
        int res = merge_inv(left_poly, right_poly, left_ind, right_ind);
        if(res == 0){
            up_left = left_ind;
            up_right = right_ind;
            done = true;
        }
        if(res == 1) {
            left_ind = (left_ind-1)%left_poly->getSize();
        }
        if(res == -1) {
            right_ind = (right_ind+1)%right_poly->getSize();
        }
    }

    done = false;
    while(!done) {
        int res = merge_inv(left_poly, right_poly, left_ind, right_ind);
        if(res == 0){
            up_left = left_ind;
            up_right = right_ind;
            done = true;
        }
        if(res == 1) {
            left_ind = (left_ind+1)%left_poly->getSize();
        }
        if(res == -1) {
            right_ind = (right_ind-1)%right_poly->getSize();
        }
    }

    std::vector<int> res{up_left, up_right, down_right, down_left};
    return res;
}

/**
 * merge algorithm invariant
 * @param left_poly left side convex polygon
 * @param right_poly right side convex polygon
 * @param l int of the right most point in the left poly
 * @param r int of the left most point in the right poly
 * @return int value
 */
int ConvexHull::merge_inv(Shapes2D::Polygon *left_poly, Shapes2D::Polygon *right_poly, int l, int r) {
    int n_left = left_poly->getSize();
    int n_right = right_poly->getSize();
    Shapes2D::Point2d *left_up = left_poly->getByIndex((l-1)%n_left);
    Shapes2D::Point2d *left_down = left_poly->getByIndex((l+1)%n_left);
    Shapes2D::Point2d *right_up = right_poly->getByIndex((r-1)%n_right);
    Shapes2D::Point2d *right_down = right_poly->getByIndex((r+1)%n_right);
    Shapes2D::Point2d *left = left_poly->getByIndex(l%n_left);
    Shapes2D::Point2d *right = right_poly->getByIndex(r%n_right);

    if (left_up->oriePred(*left, *right) > 0 && left_down->oriePred(*left, *right) < 0)
        return 1;
    if (right_up->oriePred(*right, *left) < 0 && right_down->oriePred(*right, *left) > 0)
        return -1;
    return 0;

}

