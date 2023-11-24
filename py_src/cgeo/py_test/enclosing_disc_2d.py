import random
import py_src.cgeo.plots_2d.circle_plot as CirclePlot
from py_src.cgeo.modules.point_2d import Point2D as Point
from py_src.cgeo.utilities.c_utilities.global_c_utils import enclosingDisc


def generatePoints(n=10):
    _points = []
    for i in range(n):
        _points.append(Point(random.randint(-10, 10), random.randint(-10, 10)))

    return _points


points_vector = generatePoints(50)

disc = enclosingDisc(points_vector)

CirclePlot.PlotCircles().plotEnclosingDisc(points_vector, disc)
