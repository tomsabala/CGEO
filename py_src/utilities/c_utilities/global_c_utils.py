from build import libGeo_2D as Geo
from py_src.modules.polygon import Polygon
from py_src.modules.segment_2d import Segment2D as Segment
from py_src.modules.point_2d import Point2D as Point
from py_src.modules.triangle import Triangle
from py_src.modules.circle import Circle


def grahamConvexHull(polygon: Polygon) -> Polygon:
    cPolygon = Geo.libAlgorithms_2D.ConvexHullUtils.grahamConvexHull(polygon.cPolygon)
    return Polygon.fromCPolygon(cPolygon)


def giftWrapConvexHull(polygon: Polygon) -> Polygon:
    cPolygon = Geo.libAlgorithms_2D.ConvexHullUtils.giftWrapConvexHull(polygon.cPolygon)
    return Polygon.fromCPolygon(cPolygon)


def segmentIntersection(segments: list[Segment]) -> list[Point]:
    cPointList = Geo.libAlgorithms_2D.SegmentIntersect.intersection([s.cSegment for s in segments])
    return [Point.fromCPoint(p) for p in cPointList]


def triangulate(polygon: Polygon) -> list[Triangle]:
    cTriangles = Geo.libAlgorithms_2D.TriangulationUtils.triangulate(polygon.cPolygon)
    return [Triangle.fromCTriangle(triangle) for triangle in cTriangles]


def enclosingDisc(points: list[Point]) -> Circle:
    cCircle = Geo.libAlgorithms_2D.EnclosingDistUtils.findDisc([p.cPoint for p in points])
    return Circle.fromCCircle(cCircle)
