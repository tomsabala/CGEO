"""End-to-end checks against the compiled extension.

Imports nothing outside the standard library and cgeo: cibuildwheel runs this
file against every built wheel, with only pytest installed.
"""

import math

from cgeo.modules.circle import Circle
from cgeo.modules.point_2d import Point2D as Point
from cgeo.modules.polygon import Polygon
from cgeo.modules.segment_2d import Segment2D as Segment
from cgeo.utilities.c_utilities.global_c_utils import (
    enclosingDisc,
    grahamConvexHull,
    segmentIntersection,
    triangulate,
)

SQUARE = [(0, 0), (4, 0), (4, 4), (0, 4)]


def _polygon(points):
    return Polygon([Point(x, y) for x, y in points])


def test_graham_hull_drops_the_interior_point():
    hull = grahamConvexHull(_polygon(SQUARE + [(2, 2)]))
    assert set(map(tuple, hull.toList())) == {(0.0, 0.0), (4.0, 0.0), (4.0, 4.0), (0.0, 4.0)}


def test_segment_intersection_finds_the_crossing():
    segments = [Segment(Point(0, 0), Point(4, 4)), Segment(Point(0, 4), Point(4, 0))]
    assert [(p.x, p.y) for p in segmentIntersection(segments)] == [(2.0, 2.0)]


def test_triangulation_partitions_the_square():
    triangles = triangulate(_polygon(SQUARE))
    assert len(triangles) == 2
    assert math.isclose(sum(t.area for t in triangles), 16.0, rel_tol=1e-9)


def test_enclosing_disc_of_a_right_triangle():
    disc = enclosingDisc([Point(0, 0), Point(4, 0), Point(4, 3)])
    assert math.isclose(disc.r, 2.5, rel_tol=1e-9)
    assert math.isclose(disc.center.x, 2.0, abs_tol=1e-9)
    assert math.isclose(disc.center.y, 1.5, abs_tol=1e-9)


def test_circle_centre_survives_a_round_trip():
    circle = Circle(1.0, Point(3, 4))
    assert (circle.center.x, circle.center.y) == (3.0, 4.0)
