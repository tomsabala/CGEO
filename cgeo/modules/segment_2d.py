from __future__ import annotations
from typing import Union
from cgeo.modules.point_2d import Point2D as Point
from cgeo.utilities.error_handling.error_utilities import *

from cgeo import _cgeo

@handle_errors_for_class
class Segment2D:
    def __init__(self, *args):
        if len(args) == 0:
            self._segment = _cgeo.libShapes_2D.Segment()
        elif len(args) == 1:
            assert(isinstance(args[0], Segment2D))
            self._segment = _cgeo.libShapes_2D.Segment(args[0].origin, args[0].target)
        elif len(args) == 2:
            assert(isinstance(args[0], Point) and isinstance(args[1], Point))
            self._segment = _cgeo.libShapes_2D.Segment(args[0].cPoint, args[1].cPoint)
        else:
            raise ValueError('too many arguments')

    def __eq__(self, other: Segment2D) -> bool:
        return self._segment.__eq__(other.cSegment)

    def __copy__(self):
        return Segment2D(self.origin, self.target)

    def __str__(self):
        return str(self._segment)

    @property
    def origin(self) -> _cgeo.libShapes_2D.Point:
        return self._segment.origin

    @origin.setter
    def origin(self, value: Point | _cgeo.libShapes_2D.Point) -> None:
        self._segment.origin = value if isinstance(value, _cgeo.libShapes_2D.Point) else value.cPoint

    @property
    def target(self) -> _cgeo.libShapes_2D.Point:
        return self._segment.target

    @target.setter
    def target(self, value: Point | _cgeo.libShapes_2D.Point) -> None:
        self._segment.target = value if isinstance(value, _cgeo.libShapes_2D.Point) else value.cPoint

    @property
    def slope(self) -> float:
        return self._segment.getSlope()

    @property
    def length(self) -> float:
        return self._segment.getLength()

    @property
    def cSegment(self) -> _cgeo.libShapes_2D.Segment:
        return self._segment

    @classmethod
    def fromCSegment(cls, cSegment: _cgeo.libShapes_2D.Segment):
        newSegment = cls()
        newSegment._segment = cSegment
        return newSegment

    def __originX(self) -> float:
        return self.origin.x

    def __originY(self) -> float:
        return self.origin.y

    def __targetX(self) -> float:
        return self.target.x

    def __targetY(self) -> float:
        return self.target.y

    def getUpperPoint(self) -> _cgeo.libShapes_2D.Point:
        cPoint = self._segment.getUpper()
        return self.origin if self.__originX() == cPoint.x and self.__originY() == cPoint.y else self.target

    def adder(self, offsetPoint: Point) -> None:
        self._segment.adder(_cgeo.libShapes_2D.Point(offsetPoint.x, offsetPoint.y))

    def rotate(self, d: float) -> None:
        self._segment.rotate(d)

    def oriePred(self, other: Union[Point, Segment2D]) -> float:
        if not isinstance(other, (Point, Segment2D)):
            raise TypeError('Invalid argument type. Expected Point or Segment2D.')

        if isinstance(other, Point):
            return self._segment.oriePred(other.cPoint)

        return self._segment.oriePred(other.cSegment)

    def isParallel(self, other: Segment2D) -> bool:
        return self._segment.isParallel(other.cSegment)

    def isVertical(self, other: Segment2D) -> bool:
        return self._segment.isVertical(other.cSegment)

    def dist(self, other: Union[Point, Segment2D]) -> float:
        if not isinstance(other, (Point, Segment2D)):
            raise TypeError('Invalid argument type. Expected Point or Segment2D.')

        if isinstance(other, Point):
            return self._segment.dist(other.cPoint)

        return self._segment.dist(other.cSegment)

    def isIntersect(self, other: Segment2D) -> bool:
        return self._segment.isIntersect(other.cSegment)
