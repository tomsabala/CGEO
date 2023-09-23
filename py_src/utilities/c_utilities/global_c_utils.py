from build import libGeo_2D as Geo
from py_src.modules.polygon import Polygon
from py_src.modules.segment_2d import Segment2D as Segment
from py_src.modules.point_2d import Point2D as Point

def grahamConvexHull(polygon: Polygon) -> Polygon:
    cPolygon = Geo.libAlgorithms_2D.ConvexHullUtils.grahamConvexHull(polygon.polygon)
    return Polygon.fromCPolygon(cPolygon)


def giftWrapConvexHull(polygon: Polygon) -> Polygon:
    cPolygon = Geo.libAlgorithms_2D.ConvexHullUtils.giftWrapConvexHull(polygon.polygon)
    return Polygon.fromCPolygon(cPolygon)


def segmentIntersection(segments: list[Segment]) -> list[Point]:
    cPointList = Geo.libAlgorithms_2D.SegmentIntersect.intersection([s.segment for s in segments])
    return [Point.fromCPoint(p) for p in cPointList]
