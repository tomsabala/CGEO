#pragma once

#include <map>
#include <unordered_set>
#include "../shapes_2D/Segment2d.h"
#include "../../data_structures/SegmentBalancedTree.h"

namespace Algorithms2d {
    struct pair_hashFunction {
        size_t operator()(const std::pair<double, double>& x) const {
            std::hash<std::string> hash_str;
            return hash_str(std::to_string(x.first) + std::to_string(x.second));
        }
    };

    class event_comp {
    public:
        bool operator()(const Shapes2D::Point2d& a, const Shapes2D::Point2d& b) const {
            if (a.getY() > b.getY() + eps) return true;
            if (std::abs(a.getY() - b.getY()) <= eps && a.getX() < b.getX()) return true;
            return false;
        }
    };

    using EventMap = std::multimap<Shapes2D::Point2d, int, event_comp>;

    class SegmentIntersection2d {
    public:
        SegmentIntersection2d() = default;
        ~SegmentIntersection2d() = default;

        static void intersect(std::pair<bool, Shapes2D::Point2d*>* intersectionPair,
                              Shapes2D::Segment2d& a, Shapes2D::Segment2d& b, bool test);

        static void intersect(std::vector<Shapes2D::Segment2d>& segments,
                              std::vector<Shapes2D::Point2d>* intersections);

        static void handleEventPoint(EventMap::iterator e, EventMap* events,
                                     SegmentBalancedTree* status,
                                     std::vector<Shapes2D::Point2d>* intersections);

        static std::vector<Shapes2D::Segment2d> findInteriorMap(EventMap::iterator e,
                                                                 SegmentBalancedTree* status);

        static bool isInterior(const Shapes2D::Segment2d& s, const Shapes2D::Point2d& p);

        static std::vector<Shapes2D::Point2d>* solve(std::vector<Shapes2D::Segment2d>& segments);

        static void handle_segments(Shapes2D::Segment2d& s, Shapes2D::Segment2d& t,
                                    const Shapes2D::Point2d& p, EventMap* events);
    };
}



