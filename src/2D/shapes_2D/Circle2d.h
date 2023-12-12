#pragma once

#include "Point2d.h"
#include "Line2d.h"
#include "Polygon.h"


namespace Shapes2D
{
    class Circle2d {
    private:
        double r;
        Point2d *c;

        static std::pair<double, Point2d*> circleFrom3Points(const Point2d&, const Point2d&, const Point2d&);

    public:
        /* constructors */
        Circle2d();
        explicit Circle2d(double );
        Circle2d(double, Point2d *);
        Circle2d(const Point2d& , const Point2d& );
        Circle2d(const Point2d& , const Point2d& , const Point2d& );

        /* getter and setter */
        double getRadius() const;
        void setRadius(double radius);
        Point2d* getCenter();
        void setCenter(Point2d *p);
        void setCircle(Point2d *, Point2d *, Point2d *);


        /* intersecting checking methods */
        bool circleIntersect(Circle2d *circ);
        bool lineIntersect(Line2d *l);
        bool segIntersect(Segment2d *s);
        bool polyIntersect(Polygon *poly);

        /* containers checking methods */
        int pointContains(const Point2d &p);
        int segmentContains(Segment2d *s);
        int circleContains(Circle2d *c);
        int polyContains(Polygon *poly);

        ~Circle2d();
    };
}