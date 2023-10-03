
#pragma once

#include "Point2d.h"
#include "Line2d.h"
#include <cfloat>
#include <valarray>
#include <vector>

namespace Shapes2D {
    class Segment2d {
    private:
        Point2d *origin, *target;

    public:
        /* constructors */
        Segment2d();
        Segment2d(Shapes2D::Point2d *p, Shapes2D::Point2d *q);
        explicit Segment2d(const Segment2d *s);
        explicit Segment2d(Segment2d *s);

        /* getter and setter */
        Point2d* getOrigin() const;
        Point2d* getTarget() const;
        Point2d* getUpper() const;
        Point2d* getLower() const;
        void setUpper(const Point2d& p) const;
        void setLower(const Point2d& p) const;
        void setOrigin(const Point2d& new_p) noexcept(false);
        void setTarget(const Point2d& new_p) noexcept(false);
        double getSlope();
        double getLength() const;

        /* shifting methods */
        void adder(Point2d *p) const noexcept(false);
        void rotate(double &deg) const;

        /* built-in methods */
        bool _eq_(Segment2d *s) const noexcept(false);
        bool _lt_(Segment2d *s) const noexcept(false);
        bool _gt_(Segment2d *s) const noexcept(false);
        void copySegment(Segment2d *s) noexcept(false);
        std::string toStr() const;

        /* orientation predict */
        double oriePred(Segment2d *s) const noexcept(false);
        double oriePred(Point2d *p) const noexcept(false);

        /* different */
        bool isParallel(Segment2d *s) noexcept(false);
        bool isVertical(Segment2d *s) noexcept(false);
        double dist(Segment2d *s) noexcept(false);
        double dist(Point2d *p) noexcept(false);
        bool isIntersect(Segment2d *s) const;
        Point2d* getIntersect(Segment2d *s) const;
        bool containPoint(Point2d p) const;

        double getXfromY(double y) const;
        double getYfromX(double x) const;
        ~Segment2d();
    };
}
