
#include <random>
#include "SegmentIntersection2D.h"

using namespace Algorithms2d;

using segmentsVector = std::vector<Shapes2D::Segment2d >;
using pointsVector = std::vector<Shapes2D::Point2d>;
using Point = Shapes2D::Point2d;
using Segment = Shapes2D::Segment2d;

std::unordered_set<std::pair<double, double>, pair_hashFunction> checked_points;
std::map<std::pair<double, double>, std::vector<std::pair<Segment , int>>> Upper_end_point;
std::map<std::pair<double, double>, std::vector<std::pair<Segment , int>>> Lower_end_point;

/**
 * find all intersection points
 * @param segments vector
 * @param intersections dynamic vector of all intersection points
 */

/** check whether two segments intersect */
void
SegmentIntersection2d::intersect(std::pair<bool, Point *> * intersectionPair,
                                 Segment & a,
                                 Segment& b,
                                 bool test)
{
    if (a.isIntersect(b))
    {
        if (test)
            std::cout << a.toStr() << "and " << b.toStr() << "do intersect\n";
        Point * intersection = a.getIntersect(b);
        intersectionPair->first = true;
        intersectionPair->second = intersection;
        return;
    }
    if (test)
        std::cout << a.toStr() << "and" << b.toStr() << "do not intersect\n";
    intersectionPair->first = false;
    intersectionPair->second = nullptr;
}


/** handle a new event point:
 * find L(p), U(p) and C(p)
 * if | L(p) + C(p) + U(p) | > 1
 * make changes to segment tree as need, etc. delete L(p) & C(p), and insert U(p) and C(p)
 * find new event points
 * */
void
SegmentIntersection2d::handleEventPoint(std::multimap<Point, int, event_comp>::iterator e,
                                        std::multimap<Point, int, event_comp> *events,
                                        SegmentBalancedTree *status,
                                        pointsVector *intersections) {
    Point p = e->first;
    auto point_pair = std::make_pair(p.getX(), p.getY());

    /* C(p) is the vector of segments that have p as an interior point */
    segmentsVector C_vector = findInteriorMap(e, status);


    /* check if point is an intersection point, etc. point belongs to more than one segment */
    if(C_vector.size() + Lower_end_point[point_pair].size() + Upper_end_point[point_pair].size() > 1)
        intersections->push_back(p);


    /* delete L(p) and C(p) */
    for (const auto& pair : Lower_end_point[point_pair])
        status->remove(pair.first);
    for (const auto& seg : C_vector)
        status->remove(seg);

    /* insert U(p) and C(p) */
    for (const auto& pair : Upper_end_point[point_pair])
        status->insert(pair.first);
    for (const auto& seg : C_vector)
        status->insert(seg);


    if(Upper_end_point[point_pair].size() + C_vector.size() == 0)
    { /* point is an end point only */

        auto *it = status->search_p(p); /* pick the closest Node in the status to the point p */

        if (it != nullptr)
        { /* it should never be null unless, the tree is empty */
            /* x coordinate of segment w.r.t to p.y */
            double it_x = it->s.getXfromY(p.getY());
            if (it_x <= p.getX())
            { /* segment is to the left of the deleted element */
                auto * right = status->getSucc(it);
                if (right != nullptr)
                    Algorithms2d::SegmentIntersection2d::handle_segments(it->s, right->s, p, events);
            }
            else
            { /* segment is to the right of the deleted element */
                auto * left = status->getPred(it);
                if (left != nullptr)
                    Algorithms2d::SegmentIntersection2d::handle_segments(left->s, it->s, p, events);
            }
        }
    }
    else
    {/* point is a segment intersect or start */

        /* search for best closest segment in the tree w.r.t p */
        auto *left = status->search_p(p);
        auto *right = status->search_p(p);

        /* find first segment to the left that does not contain p */
        while(left != status->minn() && left->s.containPoint(p)) {
            left = status->getPred(left);
        }

        /* find first segment to the right that does not contain p */
        while(right != status->maxx() && right->s.containPoint(p)) {
            right = status->getSucc(right);
        }

        if(!left->s.containPoint(p))
        { /* found segment from the left that does not contain p */

            /* search for next intersection */
            auto *right2left = status->getSucc(left);
            Algorithms2d::SegmentIntersection2d::handle_segments(right2left->s, left->s, p, events);
        }

        if(!right->s.containPoint(p))
        { /* found segment from the right that does not contain p */

            /* search for next intersection */
            auto *left2right = status->getPred(right);
            Algorithms2d::SegmentIntersection2d::handle_segments(right->s, left2right->s, p, events);
        }
    }
}



/**
 * find all segments that has p (e.first.first) as an interior point
 * @param e event type iterator
 * @param sweep segment tree
 * @param segments segments vector
 * @return vector<int>, all indices of segments that has answer the indicator
 */
segmentsVector
SegmentIntersection2d::findInteriorMap(std::multimap<Point, int, event_comp>::iterator e,
                                       SegmentBalancedTree *status)
                                       {
    auto *segment_node = status->search_p(e->first);

    if (segment_node == nullptr)
        return {};
    auto segment = segment_node->s;

    bool flag;
    segmentsVector interior_segments;

    if (Algorithms2d::SegmentIntersection2d::isInterior(segment, e->first))
        interior_segments.push_back(segment);

    for(int dir = 0; dir<=1; dir++){ /* two iteration, one for left side and one for right side */

        auto *it = segment_node; /* walk through segment tree, from it and move forward */

        if (dir == 1){
            if(it->s == status->maxx()->s) continue;
            else it = status->getSucc(it);
        } else {
            if(it->s == status->minn()->s) continue;
            else it = status->getPred(it);
        }

        flag = true;
        while(flag) {
            if(!Algorithms2d::SegmentIntersection2d::isInterior(it->s, e->first)){
                flag = false;
            } else {
                interior_segments.push_back(it->s);
            }

            if(dir == 0){
                if(it->s == status->minn()->s) break;
                it = status->getPred(it);
            } else {
                if(it->s == status->maxx()->s) break;
                else it = status->getSucc(it);
            }
        }
    }

    return interior_segments;
}


bool SegmentIntersection2d::isInterior(const Segment & s, const Point & p) {
    if(!s.containPoint(p)) return false; /* point is not on the segment */
    return s.getUpper() != p && s.getLower() != p; /* check that the point is truly interior */
}


void SegmentIntersection2d::handle_segments( Segment & s,  Segment & t,
                                            const Point & p,
                                            std::multimap<Point , int, event_comp> *events) {

    auto * intersect_result = new std::pair<bool, Point *>();
    intersect(intersect_result, s, t, false); /* compute the intersection point */

    /* segment do intersect and the point haven't been discovered yet */
    if(intersect_result->first && events->find(*intersect_result->second) == events->end()){
        /* point is still reachable with respect to the sweep line */
        if(intersect_result->second->getY() < p.getY() || (intersect_result->second->getY() == p.getY() && intersect_result->second->getX() > p.getX())){
            events->insert(std::make_pair(*intersect_result->second, 0));
        }
    }

    delete intersect_result;
}

/**
 * debug functionality
 */
__attribute__((unused)) void
SegmentIntersection2d::print_status(SegmentBalancedTree *status)
{
    status->walkInOrder();
}

__attribute__((unused)) void
SegmentIntersection2d::print_events(
        std::multimap<Point , int, event_comp> *events) {
    for(auto & event : *events){
        std::cout<<event.first.toStr() << '\n';
    }
}

/**
 * base function. receive a segments vector and return all intersection points
 * @param segments segments vector
 * @return points vector
 */
pointsVector *
        SegmentIntersection2d::solve(segmentsVector & segments) {
    auto *res = new pointsVector ();
    intersect(segments, res);
    return res;
}

void SegmentIntersection2d::intersect(segmentsVector &segments,
                                      pointsVector *intersections) {
/* this multimap holds the y coordinate of a point,
     * the segment this point belongs to (by the index k with in segments),
     * and whether this is the upper point or lower point in the segment
     */
    auto *events = new std::multimap<Point , int, event_comp>();

    /*
     this is the segment tree that hold all segments in each point of the algorithm.
     */
    auto *status = new SegmentBalancedTree();

    /* insert upper and lower points */
    for (int k = 0; k < segments.size(); ++k)
    {
        Point lower_point;
        Point upper_point;
        if (segments[k].getOrigin().getY() != segments[k].getTarget().getY())
        {
            lower_point = segments[k].getLower();
            upper_point = segments[k].getUpper();
        }
        else
        {
            lower_point = segments[k].getUpper();
            upper_point = segments[k].getLower();
        }
        auto lower_pair = std::make_pair(lower_point.getX(), lower_point.getY());
        auto upper_pair = std::make_pair(upper_point.getX(), upper_point.getY());

        if(Lower_end_point.find(lower_pair) != Lower_end_point.end())
            Lower_end_point[lower_pair].emplace_back(segments[k], k);
        else
            Lower_end_point[lower_pair] = std::vector<std::pair<Segment , int>>{std::make_pair(segments[k], k)};

        if(Upper_end_point.find(upper_pair) != Upper_end_point.end())
            Upper_end_point[upper_pair].emplace_back(segments[k], k);
        else
            Upper_end_point[upper_pair] = std::vector<std::pair<Segment , int>>{std::make_pair(segments[k], k)};

        if(checked_points.find(upper_pair) == checked_points.end()){
            events->insert(std::make_pair(upper_point, k));
            checked_points.insert(upper_pair);
        }
        if(checked_points.find(lower_pair) == checked_points.end()){
            events->insert(std::make_pair(lower_point, k));
            checked_points.insert(lower_pair);
        }
    }

    /* start scanning the events */
    while (!events->empty())
    {
        /*pick-up first event -- {reminder: multimap holds keys in sorted form}*/
        auto event = events->begin();

        status->sweepLine->setY(event->first.getY());
        status->sweepLine->setX(event->first.getX());

        handleEventPoint(event, events, status, intersections);
        checked_points.insert(std::make_pair(event->first.getX(), event->first.getY()));
        events->erase(event);
    }

    delete events;
}

