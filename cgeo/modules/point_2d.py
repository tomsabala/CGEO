from __future__ import annotations
from cgeo.utilities.error_handling.error_utilities import *

from cgeo import _cgeo


@handle_errors_for_class
class Point2D:
    def __init__(self, x=0.0, y=0.0):
        self._point = _cgeo.libShapes_2D.Point(x, y)

    @property
    def x(self) -> float:
        return self._point.x

    @x.setter
    def x(self, value: float) -> None:
        self._point.x = value

    @property
    def y(self) -> float:
        return self._point.y

    @y.setter
    def y(self, value: float) -> None:
        self._point.y = value

    def __copy__(self) -> Point2D:
        return Point2D(self.x, self.y)

    def __str__(self) -> str:
        return self._point.toStr()

    def __eq__(self, other: Point2D) -> bool:
        return self._point.__eq__(other._point)

    def __lt__(self, other: Point2D) -> bool:
        return self._point.__lt__(other._point)

    def __gt__(self, other: Point2D) -> bool:
        return self._point.__gt__(other._point)

    def toDict(self) -> dict:
        return {"x": self.x, "y": self.y}

    @classmethod
    def fromDict(cls, data) -> Point2D:
        return cls(data["x"], data["y"])

    @classmethod
    def fromCPoint(cls, cPoint: _cgeo.libShapes_2D.Point):
        newPoint = cls()
        newPoint._point = cPoint
        return newPoint

    @property
    def norm(self) -> float:
        return self._point.norm()

    def dist(self, other: Point2D) -> float:
        return self._point.dist(other._point)

    def subtract(self, other: Point2D) -> Point2D:
        return Point2D(self.x - other.x, self.y - other.y)

    def adder(self, other: Point2D) -> Point2D:
        return Point2D(self.x + other.x, self.y + other.y)

    def oriePred(self, q: Point2D, r: Point2D) -> float:
        return self._point.oriePred(q._point, r._point)

    @property
    def cPoint(self):
        return self._point
