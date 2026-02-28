#include "SegmentIntersection2D.h"
#include <iostream>

using namespace Algorithms2d;
using namespace Shapes2D;

using segmentsVector = std::vector<Segment2d>;
using pointsVector = std::vector<Point2d>;
using SegmentIndexPair = std::pair<Segment2d, int>;
using CoordPair = std::pair<double, double>;

namespace {
    std::unordered_set<CoordPair, pair_hashFunction> checked_points;
    std::map<CoordPair, std::vector<SegmentIndexPair>> Upper_end_point;
    std::map<CoordPair, std::vector<SegmentIndexPair>> Lower_end_point;
}

void SegmentIntersection2d::intersect(std::pair<bool, Point2d*>* intersectionPair,
                                      Segment2d& a, Segment2d& b, bool test) {
    if (a.isIntersect(b)) {
        if (test) std::cout << a.toStr() << "and " << b.toStr() << "do intersect\n";
        intersectionPair->first = true;
        intersectionPair->second = a.getIntersect(b);
    } else {
        if (test) std::cout << a.toStr() << "and" << b.toStr() << "do not intersect\n";
        intersectionPair->first = false;
        intersectionPair->second = nullptr;
    }
}


void SegmentIntersection2d::handleEventPoint(EventMap::iterator e, EventMap* events,
                                             SegmentBalancedTree* status,
                                             pointsVector* intersections) {
    Point2d p = e->first;
    CoordPair point_pair = {p.getX(), p.getY()};

    segmentsVector C_vector = findInteriorMap(e, status);

    size_t totalCount = C_vector.size() + Lower_end_point[point_pair].size() + Upper_end_point[point_pair].size();
    if (totalCount > 1) {
        intersections->push_back(p);
    }

    for (const auto& pair : Lower_end_point[point_pair]) status->remove(pair.first);
    for (const auto& seg : C_vector) status->remove(seg);

    for (const auto& pair : Upper_end_point[point_pair]) status->insert(pair.first);
    for (const auto& seg : C_vector) status->insert(seg);

    if (Upper_end_point[point_pair].empty() && C_vector.empty()) {
        auto* it = status->search_p(p);
        if (it != nullptr) {
            double it_x = it->s.getXfromY(p.getY());
            if (it_x <= p.getX()) {
                auto* right = status->getSucc(it);
                if (right != nullptr) handle_segments(it->s, right->s, p, events);
            } else {
                auto* left = status->getPred(it);
                if (left != nullptr) handle_segments(left->s, it->s, p, events);
            }
        }
    } else {
        auto* left = status->search_p(p);
        auto* right = status->search_p(p);

        while (left != status->minn() && left->s.containPoint(p)) {
            left = status->getPred(left);
        }

        while (right != status->maxx() && right->s.containPoint(p)) {
            right = status->getSucc(right);
        }

        if (!left->s.containPoint(p)) {
            auto* right2left = status->getSucc(left);
            handle_segments(right2left->s, left->s, p, events);
        }

        if (!right->s.containPoint(p)) {
            auto* left2right = status->getPred(right);
            handle_segments(right->s, left2right->s, p, events);
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
    // Clear global state from previous calls to ensure correct behavior
    checked_points.clear();
    Upper_end_point.clear();
    Lower_end_point.clear();

    auto *events = new std::multimap<Point, int, event_comp>();
    auto *status = new SegmentBalancedTree();

    // Insert upper and lower points
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

