
#include "SegmentIntersection2D.h"

std::unordered_set<std::pair<int, int>, seg_hashFunction> checked_segments;
Shapes2D::Point2d status_comp::sweep;
std::unordered_set<Shapes2D::Point2d, point_hashFunction> checked_points;

/** check whether two segments intersect
 *
 * */
std::pair<bool, Shapes2D::Point2d>
        SegmentIntersection2d::intersect(const Shapes2D::Segment2d & a,
                                         const Shapes2D::Segment2d & b,
                                         bool test)
{
    Shapes2D::Point2d ret( 0, 0);
    std::cout<<"start the intersect test: for\n";
    std::cout<<"A is "<< a.toStr();
    std::cout<<" B is "<<b.toStr()<<'\n';
    Line2d *A = new Line2d(a.getUpper(), a.getLower());
    Line2d *B = new Line2d(b.getUpper(), b.getLower());

    Shapes2D::Point2d * intersectPoint = Line2d::line_intersection(A, B);
    if(intersectPoint == nullptr){
        return std::make_pair(false, ret);
    }

    ret.setX(intersectPoint->getX());
    ret.setY(intersectPoint->getY());

    if(test){
        std::cout<<"test result is "<<ret.toStr()<<'\n';
    }

    /* tests */
    if(ret.getY() <= a.getUpper()->getY() && ret.getY() >= a.getLower()->getY() && ret.getY() <= b.getUpper()->getY() && ret.getY() >= b.getLower()->getY())
        return std::make_pair(true, ret);

    /* test failed, intersection point is not on the segments */
    return std::make_pair(false, ret);
}

//void SegmentIntersection2d::intersect(int a, int b, Shapes2D::Point2d & I, std::vector<Shapes2D::Segment2d> & segments, std::multimap<Shapes2D::Point2d, int> & sweep, std::multimap<std::pair<double,int>, int, event_comp> & events) {
//    //remove event of ending of old segment
//    {
//        int rem_end_events[2];
//        rem_end_events[0] = a;
//        rem_end_events[1] = b;
//        for (int k = 0; k < 2; ++k)
//        {
//            std::pair< std::multimap<std::pair<double,int>, int, event_less>::iterator, std::multimap<std::pair<double,int>, int, event_less>::iterator> del = events.equal_range(std::make_pair(segments[rem_end_events[k]].getLower()->getY(),SEG_END)); //get all events at position of the end
//            bool flag = false;
//            for (std::multimap<std::pair<double,int>, int,event_less>::iterator it = del.first; it != del.second; ++it) //search over all events
//            {
//                if (it->first.second == SEG_END && it->second == rem_end_events[k]) //event is end of segment and segment matches current
//                {
//                    events.erase(it); //remove that segment
//                    flag = true;
//                    break; //do not expect anymore
//                }
//            }
////            if (!flag) std::cout << "Cannot find proper ending event for segment" << std::endl;
//        }
//    }
//    //add new segment with intersection point up to end
//    segments.push_back(Shapes2D::Segment2d(&I, segments[a].getLower()));
//    //add event of starting of new segment
//    events.insert(std::make_pair(std::make_pair(I.getY(),SEG_START), (int)segments.size() - 1));
//    //add event of ending of new segment
//    events.insert(std::make_pair(std::make_pair(segments.back().getLower()->getY(),SEG_END),(int)segments.size() - 1));
//    //change ending point for current segment
//    segments[a].setLower(&I);
//    //add event of ending of old segment
//    events.insert(std::make_pair(std::make_pair(I.getY(),SEG_END), a));
//    //add new segment with intersection point up to end
//    segments.push_back(Shapes2D::Segment2d(&I, segments[b].getLower()));
//    //add event of starting of new segment
//    events.insert(std::make_pair(std::make_pair(I.getY(),SEG_START), (int)segments.size() - 1));
//    //add event of ending of new segment
//    events.insert(std::make_pair(std::make_pair(segments.back().getLower()->getY(),SEG_END), (int)segments.size() - 1));
//    //change ending point for current segment
//    segments[b].setLower(&I);
//    //add event of ending of old segment
//    events.insert(std::make_pair(std::make_pair(I.getY(),SEG_END), b));
//}

void
SegmentIntersection2d::handleEventPoint(std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp>::iterator e,
                                        std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> *events,
                                        std::multimap<Shapes2D::Segment2d, int, status_comp> *sweep,
                                        std::vector<Shapes2D::Segment2d> segments,
                                        std::vector<Shapes2D::Point2d> * intersections) {
    int t = e->first.second, s = e->second.first;
//    std::vector<int> C_vector = findInteriorMap(e, sweep, segments);
    std::cout<<"the point is : " << e->first.first.toStr() << " \n";
    if (t == SEG_START) {
        std::cout<<"point is segment start \n";
        //check if there is a line with same position
        status_comp::setSweep(e->first.first);
        std::multimap<Shapes2D::Segment2d, int>::iterator ins = sweep->insert(std::make_pair(segments[s], s));
        std::cout<<"sweep after insertion:\n";
        print_it(*sweep);
        std::multimap<Shapes2D::Segment2d, int>::reverse_iterator last_element = sweep->rbegin();
        if(sweep->size() > 1 && ins->second == sweep->begin()->second && ins->second != last_element->second)
        {
            std::cout<<"check1\n";
            std::multimap<Shapes2D::Segment2d, int>::iterator iter = ins;
            iter ++;
            this->handle_segments(ins, iter, events, intersections);
        }
        else if(sweep->size() > 1 && ins->second == last_element->second && ins->second != sweep->begin()->second)
        {
            std::cout<<"check2\n";
            std::multimap<Shapes2D::Segment2d, int>::iterator iter = ins;
            iter --;
            this->handle_segments(ins, iter, events, intersections);
        }
        else if(sweep->size() > 1)
        {
            std::cout<<"check3\n";
            std::multimap<Shapes2D::Segment2d, int>::iterator iter1 = ins;
            std::multimap<Shapes2D::Segment2d, int>::iterator iter2 = ins;
            iter1 --; iter2 ++;
            this->handle_segments(ins, iter1, events, intersections);
            this->handle_segments(ins, iter2, events, intersections);
        }
    }
    else if (t == SEG_END)
    {
        std::cout<<"point is segment end \n";
        std::multimap<Shapes2D::Segment2d, int>::iterator ins = sweep->find(segments[s]);
        std::multimap<Shapes2D::Segment2d, int>::reverse_iterator last_element = sweep->rbegin();
        if (ins == sweep->begin() || ins->second == last_element->second) sweep->erase(segments[s]);
        else{
            std::multimap<Shapes2D::Segment2d, int>::iterator left = ins; left --;
            std::multimap<Shapes2D::Segment2d, int>::iterator right = ins; right ++;
            this->handle_segments(left, right, events, intersections);
            sweep->erase(segments[s]);
        }
    }
    else {
        std::cout<<"point is segment intersect \n";
        segments[s].toStr();
        int z = e->second.second;
        segments[z].toStr();
        std::cout << "sweep before deletion\n";
        this->print_it(*sweep);
        std::multimap<Shapes2D::Segment2d, int>::iterator left = sweep->find(segments[s]);
        std::multimap<Shapes2D::Segment2d, int>::iterator right = sweep->find(segments[z]);
        if (sweep->size() <= 2){
            sweep->clear();
        }else {
            std::cout<<right->first.toStr();
            std::cout<<left->first.toStr();
            sweep->erase(left);
            sweep->erase(right);
        }
        std::cout<< "sweep after deletion\n";
        this->print_it(*sweep);
        status_comp::setSweep(e->first.first);
        sweep->insert(std::make_pair(segments[s], s));
        std::cout << "sweep after first insertion\n";
        this->print_it(*sweep);
        sweep->insert(std::make_pair(segments[z], z));
        std::cout << "sweep after insertion\n";
        this->print_it(*sweep);
        right = sweep->find(segments[s]);
        left = sweep->find(segments[z]);
        std::cout << left->second <<" "<<right->second<<'\n';
        std::cout << s << " " << z << '\n';
        if(right->second != sweep->begin()->second){
            std::multimap<Shapes2D::Segment2d, int>::iterator left2right = right;
            left2right --;
            this->handle_segments(left2right, right, events, intersections);
        }
        if(right->second != sweep->rbegin()->second){
            std::multimap<Shapes2D::Segment2d, int>::iterator right2right = right;
            right2right ++;
            this->handle_segments(right2right, right, events, intersections);
        }
        if(left->second != sweep->rbegin()->second){
            std::multimap<Shapes2D::Segment2d, int>::iterator right2left = left;
            right2left ++;
            this->handle_segments(left, right2left, events, intersections);
        }
        if(left->second != sweep->begin()->second){
            std::multimap<Shapes2D::Segment2d, int>::iterator left2left = left;
            left2left --;
            this->handle_segments(left, left2left, events, intersections);
        }
    }
}

//find all intersection points
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
        events.insert(std::make_pair(std::make_pair(segments[k].getUpper(),SEG_START), std::make_pair(k, k)));
        events.insert(std::make_pair(std::make_pair(segments[k].getLower(),SEG_END), std::make_pair(k, k)));
    }

    /* start scanning the events */
    int count = 1;
    while (!events.empty()) {
        /*pick-up first event -- {reminder: multimap holds keys in sorted form}*/
        std::cout<<"iter number " << count <<'\n'; count ++;
        std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp>::iterator first = events.begin();
        if(checked_points.find(first->first.first) != checked_points.end()){
            intersections->push_back(first->first.first);
        }
        handleEventPoint(first, &events, &sweep, segments, intersections);
        events.erase(first);
        checked_points.insert(first->first.first);
        std::cout<<"sweep after event:\n";
        this->print_it(sweep);
    }

}



std::vector<int>
SegmentIntersection2d::findInteriorMap(std::multimap<std::pair<Shapes2D::Point2d, int>, int, event_comp>::iterator e,
                                       std::multimap<Shapes2D::Segment2d, int, status_comp> sweep,
                                       std::vector<Shapes2D::Segment2d> segments)
                                       {
    int segment_index = e->second;
    Shapes2D::Segment2d segment = segments[segment_index];
    std::multimap<Shapes2D::Segment2d, int>::iterator it = sweep.find(segment);

    std::vector<int> interior_segments;
    bool flag = true;

    while(flag) {
        int curr_segment_index = it->second;
        Shapes2D::Segment2d curr_segment = segments[curr_segment_index];
        if(!curr_segment.containPoint(e->first.first)){
            flag = false;
        } else {
            interior_segments.push_back(curr_segment_index);
        }
        it --;
        if(it == sweep.begin()) flag = false;
    }


    it = sweep.find(segment);
    flag = true;
    while(flag) {
        int curr_segment_index = it->second;
        Shapes2D::Segment2d curr_segment = segments[curr_segment_index];
        if(!curr_segment.containPoint(e->first.first)){
            flag = false;
        } else {
            interior_segments.push_back(curr_segment_index);
        }
        it ++;
        if(it == sweep.end()) flag = false;
    }
    return interior_segments;
}


void
SegmentIntersection2d::print_it(std::multimap<Shapes2D::Segment2d, int, status_comp> sweep)
{
    for(auto it = sweep.begin(); it != sweep.end(); it++){
        std::cout<<it->first.getUpper()->toStr()<< "----->" <<it->first.getLower()->toStr()<< "  " <<" segment number : " << it->second<<'\n';
    }
}


std::vector<Shapes2D::Point2d>
SegmentIntersection2d::solve(std::vector<Shapes2D::Segment2d> &segments)
{
    for(Shapes2D::Segment2d  s : segments) {
        if (s.getLower()->getY() == s.getUpper()->getY())
            throw Exception2D("in valid input\n");
    }

    std::vector<Shapes2D::Point2d> res;
    intersect(segments, &res);
    return res;
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

void SegmentIntersection2d::handle_segments(std::multimap<Shapes2D::Segment2d, int>::iterator it1,
                                            std::multimap<Shapes2D::Segment2d, int>::iterator it2,
                                            std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> *events,
                                            std::vector<Shapes2D::Point2d> * intersections) {
    if(!this->seg_isChecked(it1->second, it2->second)){
        std::pair<bool, Shapes2D::Point2d> I = intersect(it1->first, it2->first, true);
        if(I.first){
            this->insert2Hash(it1->second, it2->second);
            intersections->push_back(I.second);
            events->insert(std::make_pair(std::make_pair(I.second, SEG_INTERSECT), std::make_pair(it1->second, it2->second)));
        }
    }
}

