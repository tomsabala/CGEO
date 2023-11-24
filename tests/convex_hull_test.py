import json

from shapely.geometry import Polygon as sPolygon

from py_src.cgeo.modules.polygon import Polygon, Point
from py_src.cgeo.utilities.c_utilities.global_c_utils import grahamConvexHull
from py_src.cgeo.utilities.get_random_polygon import generateRandomPolygonPoints, toConvexContour


def _getPolygonSizeTests():
    with open('polygon_size_tests.json', 'r') as file:
        polygonSizeTests = json.load(file)
    return polygonSizeTests


def _generateRandomPolygon(n: int):
    dots = generateRandomPolygonPoints(center=(0, 0),
                                       avg_radius=20,
                                       irregularity=0.5,
                                       spikiness=0.5,
                                       num_vertices=n)
    return dots


def _generateRandomConvexPolygon(n: int):
    dots = toConvexContour(num_vertices=n)
    return dots


def constructPolygonFromDots(dots: list) -> Polygon:
    points_arr = [Point(x, y) for x, y in dots]
    return Polygon(points_arr)


def testRandomPolygons():
    for numVertices, numTest in _getPolygonSizeTests().items():
        for _ in range(numTest):
            polygon_points = _generateRandomPolygon(int(numVertices))

            computed_hull_polygon = sPolygon(shell=grahamConvexHull(constructPolygonFromDots(polygon_points)).toList())

            expected_hull_polygon = sPolygon(shell=polygon_points).convex_hull

            assert computed_hull_polygon.difference(expected_hull_polygon).area < 1e-6


def testRandomConvexPolygons():
    for numVertices, numTest in _getPolygonSizeTests().items():
        for _ in range(numTest):
            polygon_points = _generateRandomConvexPolygon(int(numVertices))

            computed_hull_polygon = sPolygon(shell=grahamConvexHull(constructPolygonFromDots(polygon_points)).toList())

            poly = sPolygon(shell=polygon_points)

            assert computed_hull_polygon.difference(poly).area < 1e-6
