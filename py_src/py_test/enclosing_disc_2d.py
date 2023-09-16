from build import libGeo_2D as Geo
import random
import py_src.plots_2d.CirclePlot as CirclePlot


triUtility = Geo.libAlgorithms_2D.TriangulationUtils()
discUtils = Geo.EnclosingDistUtils()
Point = Geo.libShapes_2D.Point


def generatePoints(n=10):
    _points = []
    for i in range(n):
        points.append((random.randint(-10, 10), random.randint(-10, 10)))

    return _points


points_vector = generatePoints(100)

points = []
for p in points_vector:
    points.append(Point(p[0], p[1]))

disc = discUtils.findDisc(points)

CirclePlot.PlotCircles().plotEnclosingDisc(points, disc)
