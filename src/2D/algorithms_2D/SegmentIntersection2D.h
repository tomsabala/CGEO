#pragma once

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cfloat>
#include <unordered_set>
#include <map>
#include "../shapes_2D/Segment2d.h"
#include "../shapes_2D/Line2d.h"
#include "../../data_structures/SegmentBalancedTree.h"


namespace Algorithms2d{
    struct pair_hashFunction
    {
        size_t operator()(const std::pair<double, double> &x) const
        {
            std::hash<std::string> hash_str;
            return hash_str(std::to_string(x.first) + std::to_string(x.second));
        }
    };

    class event_comp
    {
    public:
        bool operator()(Shapes2D::Point2d * a, Shapes2D::Point2d * b) const
        {
            double a_y = a->getY(), a_x = a->getX();
            double b_y = b->getY(), b_x = b->getX();

            if (a_y > b_y + eps || std::abs(a_y - b_y) <= eps && a_x < b_x) return true;
            return false;
        }
    };

    class SegmentIntersection2d {
    public:
        SegmentIntersection2d() = default;

        static std::pair<bool, Shapes2D::Point2d *>*
        intersect(Shapes2D::Segment2d *a,
                  Shapes2D::Segment2d *b,
                  bool test);

        static void
        intersect(std::vector<Shapes2D::Segment2d *> *segments,
                  std::vector<Shapes2D::Point2d *> *intersections);

        static void
        handleEventPoint(std::multimap<Shapes2D::Point2d *, int, event_comp>::iterator e,
                         std::multimap<Shapes2D::Point2d *, int, event_comp> *events,
                         SegmentBalancedTree *status,
                         std::vector<Shapes2D::Point2d *> *intersections);

        static std::vector<Shapes2D::Segment2d *>
        findInteriorMap(std::multimap<Shapes2D::Point2d *, int, event_comp>::iterator e,
                        SegmentBalancedTree *status);

        static bool isInterior(Shapes2D::Segment2d *s, Shapes2D::Point2d *p);

        static void print_status(SegmentBalancedTree *status);

        static void print_events(std::multimap<Shapes2D::Point2d *, int, event_comp> *events);

        static std::vector<Shapes2D::Point2d *>
        solve(std::vector<Shapes2D::Segment2d *> *segments);

        static void
        handle_segments(Shapes2D::Segment2d *s, Shapes2D::Segment2d *t,
                        const Shapes2D::Point2d& p,
                        std::multimap<Shapes2D::Point2d *, int, event_comp> *events);
    };
}



