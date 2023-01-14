#pragma once

#include <algorithm>
#include <iostream>
#include <math.h>
#include <float.h>
#include <unordered_set>
#include <map>
#include "../Shapes_2D/Segment2d.h"
#include "../Shapes_2D/Line2d.h"
#include "../../DataStructures/SegmentBalancedTree.h"


namespace Algorithms2d{
    struct pair_hashFunction
    {
        size_t operator()(const std::pair<double, double> &x) const
        {
            std::hash<double> int_hasher;
            return int_hasher(x.first) ^ int_hasher(x.second);
        }
    };

    class event_comp
    {
    public:
        bool operator()(Shapes2D::Point2d * a, Shapes2D::Point2d * b) const
        {
            double a_y = a->getY(), a_x = a->getX();
            double b_y = b->getY(), b_x = b->getX();

            if (a_y > b_y + eps || abs(a_y - b_y) <= eps && a_x < b_x) return true;
            return false;
        }
    };

    class SegmentIntersection2d {
    public:
        SegmentIntersection2d() = default;

        std::pair<bool, Shapes2D::Point2d *>*
        intersect(const Shapes2D::Segment2d *a,
                  const Shapes2D::Segment2d *b,
                  bool test);

        void
        intersect(std::vector<Shapes2D::Segment2d *> *segments,
                  std::vector<Shapes2D::Point2d *> *intersections);

        void
        handleEventPoint(std::multimap<Shapes2D::Point2d *, int, event_comp>::iterator e,
                         std::multimap<Shapes2D::Point2d *, int, event_comp> *events,
                         SegmentBalancedTree *status,
                         std::vector<Shapes2D::Point2d *> *intersections);

        std::vector<Shapes2D::Segment2d *>
        findInteriorMap(std::multimap<Shapes2D::Point2d *, int, event_comp>::iterator e,
                        SegmentBalancedTree *status);

        bool isInterior(Shapes2D::Segment2d *s, Shapes2D::Point2d *p);

        void print_status(SegmentBalancedTree *status);

        void print_events(std::multimap<Shapes2D::Point2d *, int, event_comp> *events);

        std::vector<Shapes2D::Point2d *>
        solve(std::vector<Shapes2D::Segment2d *> *segments);

        void
        handle_segments(Shapes2D::Segment2d *s, Shapes2D::Segment2d *t,
                        Shapes2D::Point2d p,
                        std::multimap<Shapes2D::Point2d *, int, event_comp> *events);
    };
}



