#pragma once

#include "Point2d.h"
#include "Line2d.h"
#include <cfloat>
#include <cmath>

namespace Shapes2D {
    class Segment2d {
    private:
        Point2d origin, target;

    public:
        Segment2d(const Point2d &p, const Point2d &q);

        [[nodiscard]] Point2d getOrigin() const;
        [[nodiscard]] Point2d getTarget() const;
        [[nodiscard]] Point2d getUpper() const;
        [[nodiscard]] Point2d getLower() const;
        void setUpper(const Point2d& p);
        void setLower(const Point2d& p);
        void setOrigin(const Point2d& new_p) noexcept(false);
        void setTarget(const Point2d& new_p) noexcept(false);
        [[nodiscard]] double getSlope() const;
        [[nodiscard]] double getLength() const;

        void adder(const Point2d &p);
        void rotate(double &deg);

        [[nodiscard]] double oriePred(const Segment2d &s) const noexcept(false);
        [[nodiscard]] double oriePred(const Point2d &p) const noexcept(false);

        [[nodiscard]] bool isParallel(const Segment2d &s) const noexcept(false);
        [[nodiscard]] bool isVertical(const Segment2d &s) const noexcept(false);
        [[nodiscard]] double dist(const Segment2d &s) const noexcept(false);
        [[nodiscard]] double dist(const Point2d &p) const noexcept(false);
        [[nodiscard]] bool isIntersect(const Segment2d &s) const;
        [[nodiscard]] Point2d* getIntersect(const Segment2d &s) const;
        [[nodiscard]] bool containPoint(const Point2d &p) const;

        [[nodiscard]] double getXfromY(const double &y) const;
        [[nodiscard]] double getYfromX(const double &x) const;

        [[nodiscard]] std::string toStr() const;

        bool operator<(const Segment2d &s) const {
            if (getUpper().getX() == s.getUpper().getX()) {
                return getLower().getX() < s.getLower().getX();
            }
            return getUpper().getX() < s.getUpper().getX();
        }

        bool operator>(const Segment2d &s) const {
            if (getUpper().getX() == s.getUpper().getX()) {
                return getLower().getX() > s.getLower().getX();
            }
            return getUpper().getX() > s.getUpper().getX();
        }

        bool operator==(const Segment2d &s) const {
            return getOrigin() == s.getOrigin() && getTarget() == s.getTarget();
        }

        bool operator!=(const Segment2d &s) const {
            return getOrigin() != s.getOrigin() || getTarget() != s.getTarget();
        }

        ~Segment2d();
    };
}
