
#include "SegmentIntersection2D.h"

std::unordered_set<std::pair<int, int>, pair_hashFunction> checked_segments;
std::unordered_set<int> included_segments;
Shapes2D::Point2d status_comp::sweep;
std::unordered_set<Shapes2D::Point2d, point_hashFunction> checked_points;
std::map<Shapes2D::Point2d, std::vector<std::pair<Shapes2D::Segment2d, int>>> Upper_end_point;
std::map<Shapes2D::Point2d, std::vector<std::pair<Shapes2D::Segment2d, int>>> Lower_end_point;

/**
 * base function. recieve a segments vector and return all intersection points
 * @param segments segments vector
 * @return points vector
 */
std::vector<Shapes2D::Point2d>
SegmentIntersection2d::solve(std::vector<Shapes2D::Segment2d> &segments)
{
    /* to be deletted */
    for(Shapes2D::Segment2d  s : segments) {
        if (s.getLower()->getY() == s.getUpper()->getY())
            throw Exception2D("invalid input\n");
    }

    std::vector<Shapes2D::Point2d> res;
    intersect(segments, &res);
    return res;
}

/**
 * find all intersection points
 * @param segments vector
 * @param intersections dynamic vector of all intersection points
 */
void
SegmentIntersection2d::intersect(std::vector<Shapes2D::Segment2d> & segments,
                                 std::vector<Shapes2D::Point2d> * intersections)
{
    /* this multimap holds the y coordinate of a point,
     * the segment this point belongs to (by the index k with in segments),
     * and whether this is the upper point or lower point in the segment
     */
    std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> events;

    /*
     * this multimap holds the point representing an event
     * and the index s, of the segment this point belongs to in segments.
     */
    std::multimap<Shapes2D::Segment2d, int, status_comp> sweep;

    /* insert upper and lower points */
    for (int k = 0; k < (int)segments.size(); ++k) {
        if(Lower_end_point.find(*segments[k].getLower()) != Lower_end_point.end())
            Lower_end_point[*segments[k].getLower()].push_back(std::make_pair(segments[k], k));
        else
            Lower_end_point[*segments[k].getLower()] = std::vector<std::pair<Shapes2D::Segment2d, int>>{std::make_pair(segments[k], k)};

        if(Upper_end_point.find(*segments[k].getUpper()) != Upper_end_point.end())
            Upper_end_point[*segments[k].getUpper()].push_back(std::make_pair(segments[k], k));
        else
            Upper_end_point[*segments[k].getUpper()] = std::vector<std::pair<Shapes2D::Segment2d, int>>{std::make_pair(segments[k], k)};

        if(checked_points.find(*segments[k].getUpper()) == checked_points.end()){
            events.insert(std::make_pair(std::make_pair(segments[k].getUpper(),SEG_START), std::make_pair(k, k)));
            checked_points.insert(*segments[k].getUpper());
        }
        if(checked_points.find(*segments[k].getLower()) == checked_points.end()){
            events.insert(std::make_pair(std::make_pair(segments[k].getLower(),SEG_END), std::make_pair(k, k)));
            checked_points.insert(*segments[k].getLower());
        }
    }

    /* start scanning the events */
    int count = 1;
    while (!events.empty()) {
        /*pick-up first event -- {reminder: multimap holds keys in sorted form}*/
        std::cout<<"iter number " << count <<'\n'; count ++;
        std::cout << "events.size is : " << events.size() << '\n';

        std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp>::iterator first = events.begin();

        std::cout << "event point is : " << first->first.first.toStr() << '\n';

        handleEventPoint(first, &events, &sweep, segments, intersections);
        events.erase(first);
        checked_points.insert(first->first.first);

        std::cout <<'\n';
        std::cout<<"sweep after event:\n";
        this->print_status(sweep);
        std::cout<<"events after event:\n";
        this->print_events(&events);
        std::cout << '\n';
    }

}

/** check whether two segments intersect */
std::pair<bool, Shapes2D::Point2d>*
        SegmentIntersection2d::intersect(const Shapes2D::Segment2d & a,
                                         const Shapes2D::Segment2d & b,
                                         bool test)
{
    Shapes2D::Point2d ret( 0, 0); /* return output */
    Line2d *A, *B; /* two line objects reflected from a & b */

    std::cout<<"start the intersect test: for\n";
    std::cout<<"A is "<< a.toStr();
    std::cout<<" B is "<<b.toStr()<<'\n';

    /* build lines */
    A = new Line2d(a.getUpper(), a.getLower());
    B = new Line2d(b.getUpper(), b.getLower());

    /* find expected intersection point */
    Shapes2D::Point2d * intersectPoint = Line2d::line_intersection(A, B);
    if(intersectPoint == nullptr){ /* check point is not null, etc. intersection point des exist */
        return new std::pair<bool, Shapes2D::Point2d>(false, ret);
    }

    /* set return point value */
    ret.setX(intersectPoint->getX());
    ret.setY(intersectPoint->getY());

    if(test){ /* a debugging line */
        std::cout<<"test result is "<<ret.toStr()<<'\n';
    }

    /* tests, etc. check if point does lies on the two segments */
    if(ret.getY() <= a.getUpper()->getY() && ret.getY() >= a.getLower()->getY() && ret.getY() <= b.getUpper()->getY() && ret.getY() >= b.getLower()->getY())
        return new std::pair<bool, Shapes2D::Point2d>(true, ret);

    /* test failed, intersection point is not on the segments */
    return new std::pair<bool, Shapes2D::Point2d>(false, ret);
}


/** handle a new event point:
 * find L(p), U(p) and C(p)
 * if | L(p) + C(p) + U(p) | > 1
 * make changes to segment tree as need, etc. delete L(p) & C(p), and insert U(p) and C(p)
 * find new event points
 * */
void
SegmentIntersection2d::handleEventPoint(std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp>::iterator e,
                                        std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> *events,
                                        std::multimap<Shapes2D::Segment2d, int, status_comp> *sweep,
                                        std::vector<Shapes2D::Segment2d> segments,
                                        std::vector<Shapes2D::Point2d> * intersections) {
    int s = e->second.first; /* segment index and point type */

    Shapes2D::Point2d p = e->first.first;

    status_comp::setSweep(p);
    if(included_segments.find(s) == included_segments.end()){
        sweep->insert(std::make_pair(segments[s], s));
        included_segments.insert(s);
    }

    std::vector<int> C_vector = findInteriorMap(e, sweep, segments); /* C(p) */
    std::cout<<C_vector.size() <<'\n';
    /* check if point is an intersection point, etc. point belongs to more than one segment */
    if(C_vector.size() + Lower_end_point[p].size() + Upper_end_point[p].size() > 1)
        intersections->push_back(p);

    std::cout << "sweep before erasing : \n";
    this->print_status(*sweep);

    /* delete L(p) and C(p) */
    for (std::pair<Shapes2D::Segment2d, int> pair : Lower_end_point[p]) {
        if (pair.second == s) continue;
        sweep->erase(pair.first);
        included_segments.erase(pair.second);
    }
    for (int seg_index : C_vector) {
        std::cout<<seg_index << " ";
        sweep->erase(segments[seg_index]);
        included_segments.erase(seg_index);
    }

    std::cout << "sweep after erasing : \n";
    this->print_status(*sweep);

    /* insert U(p) and C(p) */
    for (std::pair<Shapes2D::Segment2d, int> pair : Upper_end_point[p]) {
        if(pair.second == s) continue;
        if(included_segments.find(pair.second) != included_segments.end()) continue;

        sweep->insert(std::make_pair(pair.first, pair.second));
        included_segments.insert(pair.second);
    }
    for (int seg_index : C_vector) {
        if(included_segments.find(seg_index) != included_segments.end()) continue;

        sweep->insert(std::make_pair(segments[seg_index], seg_index));
        included_segments.insert(seg_index);
    }

    std::cout << "sweep after inserting : \n";
    this->print_status(*sweep);

    if(Upper_end_point[p].size() + C_vector.size() == 0) { /* point is an end point only */

        std::cout<<"point is segment end \n";

        std::multimap<Shapes2D::Segment2d, int>::iterator ins = sweep->find(segments[s]);
        if (ins->second != sweep->begin()->second && ins->second != sweep->rbegin()->second) {
            std::multimap<Shapes2D::Segment2d, int>::iterator left = ins; left --;
            std::multimap<Shapes2D::Segment2d, int>::iterator right = ins; right ++;


//            std::cout << "checking the two following segments : \n";
//            std::cout << left->first.toStr();
//            std::cout << right->first.toStr();
//            if(this->seg_isChecked(left->second, right->second))
//                return ;
//            std::pair<bool, Shapes2D::Point2d>* I = intersect(left->first, right->first, true);
//            if((*I).first && checked_points.find((*I).second) == checked_points.end()){
//                if((*I).second.getY() < p.getY() || ((*I).second.getY() == p.getY() && (*I).second.getX() > p.getX())){
//                    this->insert2Hash(right->second, left->second);
//                    events->insert(std::make_pair(std::make_pair((*I).second, SEG_INTERSECT), std::make_pair(left->second, right->second)));
//                }
//            }
            this->handle_segments(&left, &right, p, events);
        }

        sweep->erase(segments[s]);
    }
    else {
        std::cout << "point is segment start or intersection\n";
        std::multimap<Shapes2D::Segment2d, int>::iterator left = sweep->find(segments[s]);
        if (left == sweep->end()) left --;
        std::multimap<Shapes2D::Segment2d, int>::iterator right = sweep->find(segments[s]);
        if (right == sweep->end()) right --;

        std::cout << "ins points to : " << left->first.toStr();
        std::cout << "searching for the left side\n";
        while(left->second != sweep->begin()->second && left->first.containPoint(p)) {
            std::cout << left->first.toStr() << '\n';
            left --;
        }
        std::cout << "searching for the right side\n";
        while(right->second != sweep->rbegin()->second && right->first.containPoint(p)){
            std::cout << right->first.toStr() << '\n';
            right ++;
        }

        if(!left->first.containPoint(p)) {
            std::multimap<Shapes2D::Segment2d, int>::iterator left2left = left; left2left++;

//            std::cout << "checking the two following segments : \n";
//            std::cout << left->first.toStr();
//            std::cout << left2left->first.toStr();
//            if(this->seg_isChecked(left->second, left2left->second))
//                return ;
//            std::pair<bool, Shapes2D::Point2d>* I = intersect(left->first, left2left->first, true);
//            if((*I).first && checked_points.find((*I).second) == checked_points.end()){
//                if((*I).second.getY() < p.getY() || ((*I).second.getY() == p.getY() && (*I).second.getX() > p.getX())){
//                    this->insert2Hash(left2left->second, left->second);
//                    events->insert(std::make_pair(std::make_pair((*I).second, SEG_INTERSECT), std::make_pair(left->second, left2left->second)));
//                }
//            }

            this->handle_segments(&left2left, &left, p, events);
        }
        if(!right->first.containPoint(p)) {
            std::multimap<Shapes2D::Segment2d, int>::iterator right2right = right; right2right--;

            this->handle_segments(&right, &right2right, p, events);
        }
    }

    for (std::pair<Shapes2D::Segment2d, int> pair : Lower_end_point[p]) {
        sweep->erase(pair.first);
        included_segments.erase(pair.second);
    }
}



/**
 * find all segments that has p (e.first.first) as an interior point
 * @param e event type iterator
 * @param sweep segment tree
 * @param segments segments vector
 * @return vector<int>, all indices of segments that has answer the indicator
 */
std::vector<int>
SegmentIntersection2d::findInteriorMap(std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp>::iterator e,
                                       std::multimap<Shapes2D::Segment2d, int, status_comp> *sweep,
                                       std::vector<Shapes2D::Segment2d> segments)
                                       {
    int segment_index = e->second.first;
    Shapes2D::Segment2d segment = segments[segment_index];
    std::multimap<Shapes2D::Segment2d, int>::iterator it;
    bool flag;
    std::vector<int> interior_segments;

    if (this->isInterior(segment, e->first.first))
        interior_segments.push_back(segment_index);

    for(int dir = 0; dir<=1; dir++){ /* two iteration, one for left side and one for right side */
        it = sweep->find(segment); /* walk through segment tree, from it and move forward */

        if(it == sweep->end()) continue;

        if (dir == 1){
            if(it->second == sweep->rbegin()->second) continue;
            else it ++;
        } else {
            if(it->second == sweep->begin()->second) continue;
            else it --;
        }

        flag = true;
        while(flag) {
            int curr_segment_index = it->second;

            Shapes2D::Segment2d curr_segment = segments[curr_segment_index];

            if(!this->isInterior(curr_segment, e->first.first)){
                flag = false;
            } else {
                interior_segments.push_back(curr_segment_index);
            }

            if(dir == 0){
                if(it->second == sweep->begin()->second) flag = false;
                it --;
            } else {
                if(it->second == sweep->rbegin()->second) flag = false;
                it ++;
            }

        }
    }

    return interior_segments;
}


bool SegmentIntersection2d::isInterior(Shapes2D::Segment2d s, Shapes2D::Point2d p) {
    if(!s.containPoint(p)) return false; /* point is not on the segment */
    return !s.getUpper()->_eq_(&p) && !s.getLower()->_eq_(&p); /* check that the point is truly interior */
}



bool
SegmentIntersection2d::seg_isChecked(int x, int y)
{
    if (checked_segments.find(std::make_pair(x, y)) != checked_segments.end())
        return true;
    if (checked_segments.find(std::make_pair(y, x)) != checked_segments.end())
        return true;
    return false;
}

void SegmentIntersection2d::insert2Hash(int x, int y) {
    checked_segments.insert(std::make_pair(x, y));
    checked_segments.insert(std::make_pair(y, x));
}

void SegmentIntersection2d::handle_segments(std::multimap<Shapes2D::Segment2d, int>::iterator *it1,
                                            std::multimap<Shapes2D::Segment2d, int>::iterator *it2,
                                            Shapes2D::Point2d p,
                                            std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> *events) {
    std::cout << "checking the two following segments : \n";
    std::cout << (*it1)->first.toStr();
    std::cout << (*it2)->first.toStr();
    if(this->seg_isChecked((*it1)->second, (*it2)->second))
        return ;
    std::pair<bool, Shapes2D::Point2d>* I = intersect((*it1)->first, (*it2)->first, true);
    if((*I).first && checked_points.find((*I).second) == checked_points.end()){
        if((*I).second.getY() < p.getY() || ((*I).second.getY() == p.getY() && (*I).second.getX() > p.getX())){
            this->insert2Hash((*it1)->second, (*it2)->second);
            events->insert(std::make_pair(std::make_pair((*I).second, SEG_INTERSECT), std::make_pair((*it1)->second, (*it2)->second)));
        }
    }
}



/**
 * debug functionality
 */
void
SegmentIntersection2d::print_status(std::multimap<Shapes2D::Segment2d, int, status_comp> sweep)
{
    for(auto it = sweep.begin(); it != sweep.end(); it++){
        std::cout<<it->first.getUpper()->toStr()<< "----->" <<it->first.getLower()->toStr()<< "  " <<" segment number : " << it->second<<'\n';
    }
}

void SegmentIntersection2d::print_events(
        std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> *events) {
    for(auto it = events->begin(); it != events->end(); it++){
        std::cout<<it->first.first.toStr() << '\n';
    }
}
