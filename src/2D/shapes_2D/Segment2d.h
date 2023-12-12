
#pragma once

#include "Point2d.h"
#include "Line2d.h"
#include <cfloat>
#include <valarray>
#include <vector>

namespace Shapes2D {
    class Segment2d {
    private:
        Point2d origin, target;

    public:
        /* constructors */
        Segment2d(const Shapes2D::Point2d &p, const Shapes2D::Point2d &q);

        /* getter and setter */
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

        /* shifting methods */
        void adder(const Point2d &p) const;
        void rotate(double &deg) const;\

        /* orientation predict */
        [[nodiscard]] double oriePred(const Segment2d &s) const noexcept(false);
        [[nodiscard]] double oriePred(const Point2d &p) const noexcept(false);

        /* different */
        [[nodiscard]] bool isParallel(const Segment2d &s) const noexcept(false);
        [[nodiscard]] bool isVertical(const Segment2d &s) const noexcept(false);
        [[nodiscard]] double dist(const Segment2d &s) const noexcept(false);
        [[nodiscard]] double dist(const Point2d &p) const noexcept(false);
        bool isIntersect(const Segment2d &s) const;
        [[nodiscard]] Point2d * getIntersect(const Segment2d &s) const;
        [[nodiscard]] bool containPoint(const Point2d &p) const;

        [[nodiscard]] double getXfromY(const double &y) const;
        [[nodiscard]] double getYfromX(const double &x) const;

        /* built-in methods */
        [[nodiscard]] std::string toStr() const;
        bool operator <(const Segment2d & s) const
        {
            if (this->getUpper().getX() == s.getUpper().getX())
                return this->getLower().getX() < s.getLower().getX();
            return this->getUpper().getX() < s.getUpper().getX();
        }
        bool operator >(const Segment2d & s) const
        {
            if (this->getUpper().getX() == s.getUpper().getX())
                return this->getLower().getX() > s.getLower().getX();
            return this->getUpper().getX() > s.getUpper().getX();
        }
        bool operator ==(const Segment2d & s) const
        {
            return this->getOrigin() == s.getOrigin() && this->getTarget() == s.getTarget();
        }
        bool operator !=(const Segment2d & s) const
        {
            return this->getOrigin() != s.getOrigin() || this->getTarget() != s.getTarget();
        }

        ~Segment2d();
    };
}
