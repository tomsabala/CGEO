from __future__ import annotations
from build import libGeo_2D as Geo
from py_src.cgeo.utilities.get_vector_type import getVectorType
from py_src.cgeo.utilities.error_handling.error_utilities import handle_errors_for_class
from py_src.cgeo.modules.point_2d import Point2D as Point
from py_src.cgeo.modules.segment_2d import Segment2D as Segment


@handle_errors_for_class
class Polygon:
    def __init__(self, args=None):
        if args is None:
            args = []
        if len(args) == 0:
            self._polygon = Geo.libShapes_2D.Polygon()
        elif getVectorType(args) != Point.__name__:
            raise TypeError('invalid argument')
        else:
            self._polygon = Geo.libShapes_2D.Polygon([p.cPoint for p in args])

    @property
    def cPolygon(self) -> Geo.libShapes_2D.Polygon:
        return self._polygon

    @property
    def size(self) -> int:
        return self._polygon.getSize()

    @property
    def isEmpty(self) -> bool:
        return self.size == 0

    @property
    def isConvex(self) -> bool:
        return self._polygon.isConvex()

    @property
    def isYMonotone(self) -> bool:
        return self._polygon.isY_Monotone()

    @classmethod
    def fromCPolygon(cls, cPolygon: Geo.libShapes_2D.Polygon) -> Polygon:
        newPolygon = cls()
        newPolygon._polygon = cPolygon
        return newPolygon

    def getVertices(self) -> list[Point]:
        cVertices = self._polygon.getVertices()
        return [Point.fromCPoint(cVertex) for cVertex in cVertices]

    def insert(self, vertex: Point, index=-1) -> None:
        if index < 0:
            self._polygon.insert(vertex.cPoint)
        else:
            self._polygon.insert(vertex.cPoint, index)

    def getByIndex(self, index: int) -> Point:
        return Point.fromCPoint(self._polygon.getByIndex(index))

    def getLexMin(self) -> Point:
        return Point.fromCPoint(self._polygon.getLexMin())

    def getLexMinIndex(self) -> int:
        return self._polygon.getLexMin_index()

    def getLexMax(self) -> Point:
        return Point.fromCPoint(self._polygon.getLexMax())

    def getLexMaxIndex(self) -> int:
        return self._polygon.getLexMax_index()

    def getLexOrder(self) -> list[Point]:
        return [Point.fromCPoint(cVertex) for cVertex in self._polygon.lexOrder()]

    def getEdges(self) -> list[Segment]:
        return [Segment.fromCSegment(cEdge) for cEdge in self._polygon.getEdges()]

    def isInnerCusp(self, index: int) -> bool:
        return self._polygon.isInnerCusp(index)

    def decomposeToYMonotone(self) -> list[Polygon]:
        return [Polygon.fromCPolygon(cPolygon) for cPolygon in self._polygon.decomposeY_Monotone()]

    def toList(self) -> list:
        return [[p.x, p.y] for p in self.getVertices()]
