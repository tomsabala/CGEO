from  __future__ import annotations
from build import libGeo_2D as Geo
from py_src.utilities.error_handling.error_utilities import handle_errors_for_class
from py_src.modules.segment_2d import Segment2D as Segment
from py_src.modules.point_2d import Point2D as Point
from py_src.modules.triangle import Triangle
from py_src.modules.polygon import Polygon

@handle_errors_for_class
class Circle:
    def __init__(self, r=0.0, center=Point(0, 0)):
        self._circle = Geo.libShapes_2D.Circle(r, center.cPoint)

    @classmethod
    def fromTriangle(cls, triangle: Triangle) -> Circle:
        newCircle = cls()
        cCircle = Geo.libShapes_2D.Circle(triangle.a.cPoint, triangle.b.cPoint, triangle.c.cPoint)
        newCircle._circle = cCircle
        return newCircle

    @property
    def r(self) -> float:
        return self._circle.r

    @property
    def center(self) -> Point:
        return Point.fromCPoint(self._circle.center)

    @property
    def cCircle(self) -> Geo.libShapes_2D.Circle:
        return self._circle

    @classmethod
    def fromCCircle(cls, cCircle: Geo.libShapes_2D.Circle) -> Circle:
        newCircle = cls()
        newCircle._circle = cCircle
        return newCircle

    def circleIntersect(self, circle: Circle) -> bool:
        return self._circle.circleIntersect(circle.cCircle)

    # should add line intersect

    def segIntersect(self, segment: Segment) -> bool:
        return self._circle.segIntersect(segment.cSegment)

    def polyIntersect(self, polygon: Polygon) -> bool:
        return self._circle.polyIntersect(polygon.cPolygon)

    def pointContains(self, point: Point) -> bool:
        return self._circle.pointContains(point.cPoint)

    def segmentContains(self, segment: Segment) -> bool:
        return self._circle.segmentContains(segment.cSegment)

    def circleContains(self, circle: Circle) -> bool:
        return self._circle.circleContains(circle.cCircle)

    def polyContains(self, polygon: Polygon) -> bool:
        return self._circle.polyContains(polygon.cPolygon)
