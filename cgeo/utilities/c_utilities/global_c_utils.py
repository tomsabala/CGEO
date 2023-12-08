from cgeo.modules.polygon import Polygon
from cgeo.modules.segment_2d import Segment2D as Segment
from cgeo.modules.point_2d import Point2D as Point
from cgeo.modules.triangle import Triangle
from cgeo.modules.circle import Circle

from cgeo import _cgeo

def grahamConvexHull(polygon: Polygon) -> Polygon:
    cPolygon = _cgeo.libAlgorithms_2D.ConvexHullUtils.grahamConvexHull(polygon.cPolygon)
    return Polygon.fromCPolygon(cPolygon)


def giftWrapConvexHull(polygon: Polygon) -> Polygon:
    cPolygon = _cgeo.libAlgorithms_2D.ConvexHullUtils.giftWrapConvexHull(polygon.cPolygon)
    return Polygon.fromCPolygon(cPolygon)


def segmentIntersection(segments: list[Segment]) -> list[Point]:
    cPointList = _cgeo.libAlgorithms_2D.SegmentIntersect.intersection([s.cSegment for s in segments])
    return [Point.fromCPoint(p) for p in cPointList]


def triangulate(polygon: Polygon) -> list[Triangle]:
    cTriangles = _cgeo.libAlgorithms_2D.TriangulationUtils.triangulate(polygon.cPolygon)
    return [Triangle.fromCTriangle(triangle) for triangle in cTriangles]


def enclosingDisc(points: list[Point]) -> Circle:
    cCircle = _cgeo.libAlgorithms_2D.EnclosingDistUtils.findDisc([p.cPoint for p in points])
    return Circle.fromCCircle(cCircle)
