#pragma once

#include "Point2d.h"
#include "Line2d.h"
#include "Polygon.h"

namespace Shapes2D {
    class Circle2d {
    private:
        double r;
        Point2d* c;

        static std::pair<double, Point2d*> circleFrom3Points(const Point2d&, const Point2d&, const Point2d&);

    public:
        Circle2d();
        explicit Circle2d(double radius);
        Circle2d(double radius, Point2d* center);
        Circle2d(const Point2d& p, const Point2d& q);
        Circle2d(const Point2d& p, const Point2d& q, const Point2d& t);

        [[nodiscard]] double getRadius() const;
        void setRadius(double radius);
        Point2d* getCenter();
        void setCenter(Point2d* p);
        void setCircle(Point2d* p, Point2d* q, Point2d* t);

        bool circleIntersect(Circle2d* circ);
        bool lineIntersect(Line2d* l);
        bool segIntersect(Segment2d* s);
        bool polyIntersect(Polygon* poly);

        int pointContains(const Point2d& p);
        int segmentContains(Segment2d* s);
        int circleContains(Circle2d* circ);
        int polyContains(Polygon* poly);

        ~Circle2d();
    };
}