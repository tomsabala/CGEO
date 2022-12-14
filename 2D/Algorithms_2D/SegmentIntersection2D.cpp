
#include "SegmentIntersection2D.h"

using namespace Algorithms2d;

std::unordered_set<int> included_segments;
std::unordered_set<std::pair<double, double>, pair_hashFunction> checked_points;
std::map<std::pair<double, double>, std::vector<std::pair<Shapes2D::Segment2d, int>>> Upper_end_point;
std::map<std::pair<double, double>, std::vector<std::pair<Shapes2D::Segment2d, int>>> Lower_end_point;

/**
 * base function. receive a segments vector and return all intersection points
 * @param segments segments vector
 * @return points vector
 */
std::vector<Shapes2D::Point2d *>
SegmentIntersection2d::solve(std::vector<Shapes2D::Segment2d> *segments)
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
SegmentIntersection2d::intersect(std::vector<Shapes2D::Segment2d> *segments,
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
    BST *status = new BST();

    /* insert upper and lower points */
    for (int k = 0; k < (int)segments->size(); ++k) {
        Shapes2D::Point2d *lower_point = (*segments)[k].getLower();
        Shapes2D::Point2d *upper_point = (*segments)[k].getUpper();
        std::pair<double, double> lower_pair = std::make_pair(lower_point->getX(), lower_point->getY());
        std::pair<double, double> upper_pair = std::make_pair(upper_point->getX(), upper_point->getY());

        if(Lower_end_point.find(lower_pair) != Lower_end_point.end())
            Lower_end_point[lower_pair].push_back(std::make_pair((*segments)[k], k));
        else
            Lower_end_point[lower_pair] = std::vector<std::pair<Shapes2D::Segment2d, int>>{std::make_pair((*segments)[k], k)};

        if(Upper_end_point.find(upper_pair) != Upper_end_point.end())
            Upper_end_point[upper_pair].push_back(std::make_pair((*segments)[k], k));
        else
            Upper_end_point[upper_pair] = std::vector<std::pair<Shapes2D::Segment2d, int>>{std::make_pair((*segments)[k], k)};

        if(checked_points.find(upper_pair) == checked_points.end()){
            events.insert(std::make_pair((*segments)[k].getUpper(), k));
            checked_points.insert(upper_pair);
        }
        if(checked_points.find(lower_pair) == checked_points.end()){
            events.insert(std::make_pair((*segments)[k].getLower(), k));
            checked_points.insert(lower_pair);
        }
    }

    /* start scanning the events */
    int count = 1;
    while (!events.empty()) {
        /*pick-up first event -- {reminder: multimap holds keys in sorted form}*/
        std::cout<<"iter number " << count <<'\n'; count ++;
        std::cout << "events.size is : " << events.size() << '\n';

        std::multimap<Shapes2D::Point2d *, int, event_comp>::iterator event = events.begin();

        std::cout << "event point is : " << event->first->toStr() << '\n';
        status->setHeight(*event->first);
        handleEventPoint(event, &events, status, intersections);
        checked_points.insert(std::make_pair(event->first->getX(), event->first->getY()));
        events.erase(event);

        std::cout <<'\n';
        std::cout<<"sweep after event:\n";
        this->print_status(status);
        std::cout<<"events after event:\n";
        this->print_events(&events);
        std::cout << '\n';
        if (count>14)
            break;
    }

}

/** check whether two segments intersect */
std::pair<bool, Shapes2D::Point2d *>*
        SegmentIntersection2d::intersect(const Shapes2D::Segment2d *a,
                                         const Shapes2D::Segment2d *b,
                                         bool test)
{
    Shapes2D::Point2d *ret = new Shapes2D::Point2d( 0, 0); /* return output */
    Line2d *A, *B; /* two line objects reflected from a & b */

    std::cout<<"start the intersect test: for\n";
    std::cout<<"A is "<< a->toStr();
    std::cout<<" B is "<<b->toStr()<<'\n';

    /* build lines */
    A = new Line2d(a->getUpper(), a->getLower());
    B = new Line2d(b->getUpper(), b->getLower());

    /* find expected intersection point */
    Shapes2D::Point2d * intersectPoint = Line2d::line_intersection(A, B);
    if(intersectPoint == nullptr){ /* check point is not null, etc. intersection point des exist */
        return new std::pair<bool, Shapes2D::Point2d *>(false, ret);
    }

    /* set return point value */
    ret->setX(intersectPoint->getX());
    ret->setY(intersectPoint->getY());

    if(test){ /* a debugging line */
        std::cout<<"test result is "<<ret->toStr()<<'\n';
    }

    /* tests, etc. check if point does lies on the two segments */
    if(ret->getY() <= a->getUpper()->getY() && ret->getY() >= a->getLower()->getY() && ret->getY() <= b->getUpper()->getY() && ret->getY() >= b->getLower()->getY())
        return new std::pair<bool, Shapes2D::Point2d *>(true, ret);

    /* test failed, intersection point is not on the segments */
    return new std::pair<bool, Shapes2D::Point2d *>(false, ret);
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
                                        BST *status,
                                        std::vector<Shapes2D::Point2d *> * intersections) {
    std::cout << "<><><><> inside handle event point <><><><><>\n";
    Shapes2D::Point2d *p = e->first;
    std::pair<double, double> point_pair = std::make_pair(p->getX(), p->getY());
    std::vector<Shapes2D::Segment2d> C_vector = findInteriorMap(e, status); /* C(p) */


    std::cout << C_vector.size() << " " << Lower_end_point[point_pair].size() << " " << Upper_end_point[point_pair].size() << '\n';
    /* check if point is an intersection point, etc. point belongs to more than one segment */
    if(C_vector.size() + Lower_end_point[point_pair].size() + Upper_end_point[point_pair].size() > 1)
    {
        intersections->push_back(p);
    }

    std::cout << "1111111111\n";
    print_status(status);

    /* delete L(p) and C(p) */
    for (std::pair<Shapes2D::Segment2d, int> pair : Lower_end_point[point_pair]) {
        status->removeSegment(pair.first);
        included_segments.erase(pair.second);
    }
    for (Shapes2D::Segment2d seg : C_vector) {
        status->removeSegment(seg);
//        included_segments.erase(seg);
        std::cout << "2222222222\n";
        print_status(status);
    }


    /* insert U(p) and C(p) */
    for (std::pair<Shapes2D::Segment2d, int> pair : Upper_end_point[point_pair]) {
        if(included_segments.find(pair.second) != included_segments.end()) continue;

        status->insertSegment(&pair.first);
        included_segments.insert(pair.second);
    }
    for (Shapes2D::Segment2d seg : C_vector) {
//        if(included_segments.find(seg_index) != included_segments.end()) continue;

        status->insertSegment(&seg);
//        included_segments.insert(seg_index);
    }

    std::cout << "333333333333\n";
    print_status(status);

    if(Upper_end_point[point_pair].size() + C_vector.size() == 0) { /* point is an end point only */

        std::cout<<"point is segment end \n";

        TreeNode *it = status->searchPoint(p); /* add functionality */

        if (it != NULL && !it->getSegment()->_eq_(status->minn(status->getRoot())->getSegment()) && !it->getSegment()->_eq_(status->maxx(status->getRoot())->getSegment())) {
            TreeNode *left = status->getPredecessor(it);
            TreeNode *right = status->getSuccessor(it);

            this->handle_segments(left->getSegment(), right->getSegment(), *p, events);
        }
    }
    else {
        std::cout << "point is segment start or intersection\n";
        TreeNode *left = status->searchPoint(p);
        TreeNode *right = status->searchPoint(p);

        while(left != status->minn(status->getRoot()) && left->getSegment()->containPoint(*p)) {
            left = status->getPredecessor(left);
        }

        while(right != status->maxx(status->getRoot()) && right->getSegment()->containPoint(*p)){
            right = status->getSuccessor(right);
        }

        if(!left->getSegment()->containPoint(*p)) {
            TreeNode *right2left = status->getSuccessor(left);
            this->handle_segments(right2left->getSegment(), left->getSegment(), *p, events);
        }

        if(!right->getSegment()->containPoint(*p)) {
            TreeNode *left2right = status->getPredecessor(right);
            this->handle_segments(right->getSegment(), left2right->getSegment(), *p, events);
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
std::vector<Shapes2D::Segment2d>
SegmentIntersection2d::findInteriorMap(std::multimap<Shapes2D::Point2d *, int, event_comp>::iterator e,
                                       BST *status)
                                       {

    std::cout << "<><><><><> inside interior mapping function <><><><><> \n";

    TreeNode *segment_node = status->searchPoint(e->first);
    if (segment_node == NULL)
        return std::vector<Shapes2D::Segment2d>();
    Shapes2D::Segment2d *segment = segment_node->getSegment();
    std::cout << "relative segment in the status for the point is :\n" << segment->toStr();

    bool flag;
    std::vector<Shapes2D::Segment2d> interior_segments;

    if (this->isInterior(*segment, *e->first))
        interior_segments.push_back(*segment);

    for(int dir = 0; dir<=1; dir++){ /* two iteration, one for left side and one for right side */
        TreeNode *it = status->searchSegment(*segment); /* walk through segment tree, from it and move forward */
        if (dir == 1){
            if(it->getSegment()->_eq_(status->maxx(status->getRoot())->getSegment())) continue;
            else it = status->getSuccessor(it);
        } else {
            if(it->getSegment()->_eq_(status->minn(status->getRoot())->getSegment())) continue;
            else it = status->getPredecessor(it);
        }

        flag = true;
        while(flag) {
            if(!this->isInterior(*it->getSegment(), *e->first)){
                flag = false;
            } else {
                interior_segments.push_back(*it->getSegment());
            }

            if(dir == 0){
                if(it->getSegment()->_eq_(status->minn(status->getRoot())->getSegment())) break;
                it = status->getPredecessor(it);
            } else {
                if(it->getSegment()->_eq_(status->maxx(status->getRoot())->getSegment())) break;
                else it = status->getSuccessor(it);
            }
        }
    }

    return interior_segments;
}


bool SegmentIntersection2d::isInterior(Shapes2D::Segment2d s, Shapes2D::Point2d p) {
    if(!s.containPoint(p)) return false; /* point is not on the segment */
    return !s.getUpper()->_eq_(&p) && !s.getLower()->_eq_(&p); /* check that the point is truly interior */
}


void SegmentIntersection2d::handle_segments(Shapes2D::Segment2d *s, Shapes2D::Segment2d *t,
                                            Shapes2D::Point2d p,
                                            std::multimap<Shapes2D::Point2d*, int, event_comp> *events) {
    std::pair<bool, Shapes2D::Point2d *>* intersect_result = intersect(s, t, true); /* compute the intersection point */

    /* segment do intersect and the point haven't been discovered yet */
    if((*intersect_result).first && checked_points.find(std::make_pair((*intersect_result).second->getX(), (*intersect_result).second->getY())) == checked_points.end()){
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
SegmentIntersection2d::print_status(BST *status)
{
    status->walkInOrder(status->getRoot());
}

void SegmentIntersection2d::print_events(
        std::multimap<Shapes2D::Point2d *, int, event_comp> *events) {
    for(auto it = events->begin(); it != events->end(); it++){
        std::cout<<it->first->toStr() << '\n';
    }
}
