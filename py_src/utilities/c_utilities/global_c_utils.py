from build import libGeo_2D as Geo
from py_src.modules.polygon import Polygon


def grahamConvexHull(polygon: Polygon) -> Polygon:
    cPolygon = Geo.libAlgorithms_2D.ConvexHullUtils.grahamConvexHull(polygon.polygon)
    return Polygon.fromCPolygon(cPolygon)


def giftWrapConvexHull(polygon: Polygon) -> Polygon:
    cPolygon = Geo.libAlgorithms_2D.ConvexHullUtils.giftWrapConvexHull(polygon.polygon)
    return Polygon.fromCPolygon(cPolygon)
