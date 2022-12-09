#pragma once

#include <algorithm>
#include <iostream>
#include <math.h>
#include <float.h>
#include <unordered_set>
#include <map>
#include "../Shapes_2D/Segment2d.h"
#include "../Shapes_2D/Line2d.h"


#define SEG_START       0
#define SEG_END         1
#define SEG_INTERSECT   2

struct pair_hashFunction
{
    size_t operator()(const std::pair<int, int> &x) const
    {
        std::hash<int> int_hasher;
        return int_hasher(x.first) ^ int_hasher(x.second);
    }
};

struct seg_hashFunction
{
    size_t operator()(const Shapes2D::Segment2d &seg)
    {
        std::hash<std::string> str_hasher;
        return str_hasher(std::to_string(seg.getUpper()->getX()) + std::to_string(seg.getUpper()->getY()) +
                                  std::to_string(seg.getLower()->getX()) + std::to_string(seg.getLower()->getY()));
    }
};

struct point_hashFunction
{
    size_t operator()(const Shapes2D::Point2d &x) const
    {
        std::hash<int> int_hasher;
        return int_hasher(x.getX()) ^ int_hasher(x.getY());
    }
};

class event_comp
{
public:
    bool operator()(const std::pair<Shapes2D::Point2d, int> & a, const std::pair<Shapes2D::Point2d, int> & b) const
    {
        double a_y = a.first.getY(), a_x = a.first.getX();
        double b_y = b.first.getY(), b_x = b.first.getX();

        if (a_y > b_y + eps || abs(a_y - b_y) <= eps && a_x < b_x) return true;
        return false;
//        if (a.first > b.first - 1.0e-9)
//            return true;
//        else if (a.first < b.first + 1.0e-9)
//            return false;
//        else if (a.second > b.second)
//            return true;
//        return false;
    }
};

class status_comp{
public:
    bool operator()(const Shapes2D::Segment2d a, const Shapes2D::Segment2d b) const {
        Line2d *a_line = new Line2d(a.getTarget(), a.getOrigin());
        Line2d *b_line = new Line2d(b.getTarget(), b.getOrigin());
        std::pair<bool, double> a_x = a_line->getX_fromY(sweep.getY());
        std::pair<bool, double> b_x = b_line->getX_fromY(sweep.getY());
        if(a_x.first && b_x.first){
            if (std::abs(a_x.second - b_x.second) <= eps){
                return a_line->getX_fromY(sweep.getY() - 0.001).second < b_line->getX_fromY(sweep.getY() - 0.001).second;
            }
            return a_x.second < b_x.second;
        }
        else if (!a_x.first){
            if (a.getUpper()->getX() <= b_x.second && a.getLower()->getX() >= b_x.second) {
                if (sweep.getX() < b_x.second) {
                    return 1;
                } else {
                    return 0;
                }
            } else if (b_x.second > a.getLower()->getX()) {
                return 1;
            } else {
                return 0;
            }
        }
        else {
            if (b.getUpper()->getX() <= a_x.second && b.getLower()->getX() >= a_x.second) {
                if (sweep.getX() < a_x.second) {
                    return 0;
                } else {
                    return 1;
                }
            } else if (a_x.second > b.getLower()->getX()) {
                return 0;
            } else {
                return 1;
            }
        }
    }

    static void setSweep(Shapes2D::Point2d p) {
        sweep = p;
    }

    static Shapes2D::Point2d sweep;
};

class SegmentIntersection2d {
public:
    SegmentIntersection2d() = default;

    std::pair<bool, Shapes2D::Point2d>*
    intersect(const Shapes2D::Segment2d & a,
              const Shapes2D::Segment2d & b,
              bool test);

    void
    intersect(std::vector<Shapes2D::Segment2d> & segments,
              std::vector<Shapes2D::Point2d> * intersections);

    void
    handleEventPoint(std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp>::iterator e,
                     std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> *events,
                     std::multimap<Shapes2D::Segment2d, int, status_comp> *sweep,
                     std::vector<Shapes2D::Segment2d> segments,
                     std::vector<Shapes2D::Point2d> *intersections);

    std::vector<int>
    findInteriorMap(std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp>::iterator e,
                    std::multimap<Shapes2D::Segment2d, int, status_comp> *sweep,
                    std::vector<Shapes2D::Segment2d> segments);

    bool isInterior(Shapes2D::Segment2d s, Shapes2D::Point2d p);

    void print_status(std::multimap<Shapes2D::Segment2d, int, status_comp> sweep);

    void print_events(std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> *events);

    std::vector<Shapes2D::Point2d>
    solve(std::vector<Shapes2D::Segment2d> & segments);

    bool seg_isChecked(int x, int y);

    void insert2Hash(int x, int y);

    void
    handle_segments(std::multimap<Shapes2D::Segment2d, int>::iterator *it1,
                    std::multimap<Shapes2D::Segment2d, int>::iterator *it2,
                    Shapes2D::Point2d p,
                    std::multimap<std::pair<Shapes2D::Point2d, int>, std::pair<int, int>, event_comp> *events);
};



