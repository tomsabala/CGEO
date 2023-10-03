from __future__ import annotations
from build import libGeo_2D as Geo
from py_src.modules.point_2d import Point2D as Point
from py_src.utilities.error_handling.error_utilities import handle_errors_for_class


@handle_errors_for_class
class Triangle:
    def __init__(self, a: Point, b: Point, c: Point) -> None:
        self._triangle = Geo.libShapes_2D.Triangle(a.cPoint, b.cPoint, c.cPoint)


    @property
    def cTriangle(self) -> Geo.libShapes_2D.Triangle:
        return self._triangle

    @property
    def a(self) -> Point:
        return Point.fromCPoint(self._triangle.a)

    @a.setter
    def a(self, newPoint: Point) -> None:
        self._triangle.a = newPoint.cPoint

    @property
    def b(self) -> Point:
        return Point.fromCPoint(self._triangle.b)

    @b.setter
    def b(self, newPoint: Point) -> None:
        self._triangle.b = newPoint.cPoint

    @property
    def c(self) -> Point:
        return Point.fromCPoint(self._triangle.c)

    @c.setter
    def c(self, newPoint: Point) -> None:
        self._triangle.c = newPoint.cPoint

    @property
    def area(self) -> float:
        return self._triangle.area()

    @classmethod
    def fromCTriangle(cls, cTriangle: Geo.libShapes_2D.Triangle) -> Triangle:
        newTriangle = cls(Point.fromCPoint(cTriangle.a), Point.fromCPoint(cTriangle.b), Point.fromCPoint(cTriangle.c))
        newTriangle._triangle = cTriangle
        return newTriangle

    def getVertices(self) -> (Point, Point, Point):
        return self.a, self.b, self.c
