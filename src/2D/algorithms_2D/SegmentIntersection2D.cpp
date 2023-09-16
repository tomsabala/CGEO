
#include "SegmentIntersection2D.h"

using namespace Algorithms2d;

std::unordered_set<std::pair<double, double>, pair_hashFunction> checked_points;
std::map<std::pair<double, double>, std::vector<std::pair<Shapes2D::Segment2d*, int>>> Upper_end_point;
std::map<std::pair<double, double>, std::vector<std::pair<Shapes2D::Segment2d*, int>>> Lower_end_point;

/**
 * base function. receive a segments vector and return all intersection points
 * @param segments segments vector
 * @return points vector
 */
std::vector<Shapes2D::Point2d *>
SegmentIntersection2d::solve(std::vector<Shapes2D::Segment2d *> *segments)
{
    std::vector<Shapes2D::Point2d *> res;
    intersect(segments, &res);
    return res;
}

/**
 * find all intersection points
 * @param segments vector
 * @param intersections dynamic vector of all intersection points
 */
void
SegmentIntersection2d::intersect(std::vector<Shapes2D::Segment2d *> *segments,
                                 std::vector<Shapes2D::Point2d *> *intersections)
{
    /* this multimap holds the y coordinate of a point,
     * the segment this point belongs to (by the index k with in segments),
     * and whether this is the upper point or lower point in the segment
     */
    std::multimap<Shapes2D::Point2d *, int, event_comp> events;

    /*
     this is the segment tree that hold all segments in each point of the algorithm.
     */
    auto *status = new SegmentBalancedTree();

    /* insert upper and lower points */
    for (int k = 0; k < (int)segments->size(); ++k)
    {

        Shapes2D::Point2d *lower_point;
        Shapes2D::Point2d *upper_point;
        if ((*segments)[k]->getOrigin()->getY() != (*segments)[k]->getTarget()->getY())
        {
            lower_point = (*segments)[k]->getLower();
            upper_point = (*segments)[k]->getUpper();
        }
        else
        {
            lower_point = (*segments)[k]->getUpper();
            upper_point = (*segments)[k]->getLower();
        }
        std::pair<double, double> lower_pair = std::make_pair(lower_point->getX(), lower_point->getY());
        std::pair<double, double> upper_pair = std::make_pair(upper_point->getX(), upper_point->getY());

        if(Lower_end_point.find(lower_pair) != Lower_end_point.end())
            Lower_end_point[lower_pair].emplace_back((*segments)[k], k);
        else
            Lower_end_point[lower_pair] = std::vector<std::pair<Shapes2D::Segment2d *, int>>{std::make_pair((*segments)[k], k)};

        if(Upper_end_point.find(upper_pair) != Upper_end_point.end())
            Upper_end_point[upper_pair].emplace_back((*segments)[k], k);
        else
            Upper_end_point[upper_pair] = std::vector<std::pair<Shapes2D::Segment2d*, int>>{std::make_pair((*segments)[k], k)};

        if(checked_points.find(upper_pair) == checked_points.end()){
            events.insert(std::make_pair(upper_point, k));
            checked_points.insert(upper_pair);
        }
        if(checked_points.find(lower_pair) == checked_points.end()){
            events.insert(std::make_pair(lower_point, k));
            checked_points.insert(lower_pair);
        }
    }

    /* start scanning the events */
    while (!events.empty())
    {
        /*pick-up first event -- {reminder: multimap holds keys in sorted form}*/
        auto event = events.begin();

        status->sweepLine = event->first;
        handleEventPoint(event, &events, status, intersections);
        checked_points.insert(std::make_pair(event->first->getX(), event->first->getY()));
        events.erase(event);
    }

}

/** check whether two segments intersect */
std::pair<bool, Shapes2D::Point2d *>*
        SegmentIntersection2d::intersect(Shapes2D::Segment2d *a,
                                         Shapes2D::Segment2d *b,
                                         bool test)
{
    if (a->isIntersect(b))
    {
        if (test)
            std::cout << a->toStr() << "and" << b->toStr() << "do intersect\n";
        return new std::pair<bool, Shapes2D::Point2d *>(true, a->getIntersect(b));
    }
    if (test)
        std::cout << a->toStr() << "and" << b->toStr() << "do not intersect\n";
    return new std::pair<bool, Shapes2D::Point2d *>(false, nullptr);

}


/** handle a new event point:
 * find L(p), U(p) and C(p)
 * if | L(p) + C(p) + U(p) | > 1
 * make changes to segment tree as need, etc. delete L(p) & C(p), and insert U(p) and C(p)
 * find new event points
 * */
void
SegmentIntersection2d::handleEventPoint(std::multimap<Shapes2D::Point2d *, int, event_comp>::iterator e,
                                        std::multimap<Shapes2D::Point2d *, int, event_comp> *events,
                                        SegmentBalancedTree *status,
                                        std::vector<Shapes2D::Point2d *> * intersections) {
    Shapes2D::Point2d *p = e->first;
    std::pair<double, double> point_pair = std::make_pair(p->getX(), p->getY());

    /* C(p) is the vector of segments that have p as an interior point */
    std::vector<Shapes2D::Segment2d*> C_vector = findInteriorMap(e, status);

    /* check if point is an intersection point, etc. point belongs to more than one segment */
    if(C_vector.size() + Lower_end_point[point_pair].size() + Upper_end_point[point_pair].size() > 1)
        intersections->push_back(p);


    /* delete L(p) and C(p) */
    for (std::pair<Shapes2D::Segment2d *, int> pair : Lower_end_point[point_pair])
        status->remove(pair.first);
    for (Shapes2D::Segment2d* seg : C_vector)
        status->remove(seg);

    /* insert U(p) and C(p) */
    for (std::pair<Shapes2D::Segment2d *, int> pair : Upper_end_point[point_pair])
        status->insert(pair.first);
    for (Shapes2D::Segment2d* seg : C_vector)
        status->insert(seg);


    if(Upper_end_point[point_pair].size() + C_vector.size() == 0)
    { /* point is an end point only */

        Node *it = status->search_p(p); /* pick the closest Node in the status to the point p */

        if (it != nullptr)
        { /* it should never be null unless, the tree is empty */
            /* x coordinate of segment w.r.t to p.y */
            double it_x = it->s->getXfromY(p->getY());
            if (it_x <= p->getX())
            { /* segment is to the left of the deleted element */
                Node * right = status->getSucc(it);
                if (right != nullptr)
                    Algorithms2d::SegmentIntersection2d::handle_segments(it->s, right->s, *p, events);
            }
            else
            { /* segment is to the right of the deleted element */
                Node * left = status->getPred(it);
                if (left != nullptr)
                    Algorithms2d::SegmentIntersection2d::handle_segments(left->s, it->s, *p, events);
            }
        }
    }
    else
    {/* point is a segment intersect or start */

        /* search for best closest segment in the tree w.r.t p */
        Node *left = status->search_p(p);
        Node *right = status->search_p(p);

        /* find first segment to the left that does not contain p */
        while(left != status->minn() && left->s->containPoint(*p))
            left = status->getPred(left);

        /* find first segment to the right that does not contain p */
        while(right != status->maxx() && right->s->containPoint(*p))
            right = status->getSucc(right);

        if(!left->s->containPoint(*p))
        { /* found segment from the left that does not contain p */

            /* search for next intersection */
            Node *right2left = status->getSucc(left);
            Algorithms2d::SegmentIntersection2d::handle_segments(right2left->s, left->s, *p, events);
        }

        if(!right->s->containPoint(*p))
        { /* found segment from the right that does not contain p */

            /* search for next intersection */
            Node *left2right = status->getPred(right);
            Algorithms2d::SegmentIntersection2d::handle_segments(right->s, left2right->s, *p, events);
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
std::vector<Shapes2D::Segment2d *>
SegmentIntersection2d::findInteriorMap(std::multimap<Shapes2D::Point2d *, int, event_comp>::iterator e,
                                       SegmentBalancedTree *status)
                                       {
    Node *segment_node = status->search_p(e->first);

    if (segment_node == nullptr)
        return {};
    Shapes2D::Segment2d *segment = segment_node->s;

    bool flag;
    std::vector<Shapes2D::Segment2d *> interior_segments;

    if (Algorithms2d::SegmentIntersection2d::isInterior(segment, e->first))
        interior_segments.push_back(segment);

    for(int dir = 0; dir<=1; dir++){ /* two iteration, one for left side and one for right side */

        Node *it = segment_node; /* walk through segment tree, from it and move forward */

        if (dir == 1){
            if(it->s->_eq_(status->maxx()->s)) continue;
            else it = status->getSucc(it);
        } else {
            if(it->s->_eq_(status->minn()->s)) continue;
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
                if(it->s->_eq_(status->minn()->s)) break;
                it = status->getPred(it);
            } else {
                if(it->s->_eq_(status->maxx()->s)) break;
                else it = status->getSucc(it);
            }
        }
    }

    return interior_segments;
}


bool SegmentIntersection2d::isInterior(Shapes2D::Segment2d *s, Shapes2D::Point2d *p) {
    if(!s->containPoint(*p)) return false; /* point is not on the segment */
    return !s->getUpper()->_eq_(p) && !s->getLower()->_eq_(p); /* check that the point is truly interior */
}


void SegmentIntersection2d::handle_segments(Shapes2D::Segment2d *s, Shapes2D::Segment2d *t,
                                            const Shapes2D::Point2d& p,
                                            std::multimap<Shapes2D::Point2d*, int, event_comp> *events) {
    std::pair<bool, Shapes2D::Point2d *>* intersect_result = intersect(s, t, false); /* compute the intersection point */

    /* segment do intersect and the point haven't been discovered yet */
    if((*intersect_result).first && events->find((*intersect_result).second) == events->end()){
        /* point is still reachable with respect to the sweep line */
        if((*intersect_result).second->getY() < p.getY() || ((*intersect_result).second->getY() == p.getY() && (*intersect_result).second->getX() > p.getX())){
            events->insert(std::make_pair((*intersect_result).second, 0));
        }
    }
}

/**
 * debug functionality
 */
void
SegmentIntersection2d::print_status(SegmentBalancedTree *status)
{
    status->walkInOrder();
}

void SegmentIntersection2d::print_events(
        std::multimap<Shapes2D::Point2d *, int, event_comp> *events) {
    for(auto & event : *events){
        std::cout<<event.first->toStr() << '\n';
    }
}
