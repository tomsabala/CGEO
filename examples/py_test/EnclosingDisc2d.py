from build import libGeo_2D as Geo
import random
import examples.Plots2D.CirclePlot as CirclePlot
import numpy as np

def generatePoints(n=10):
    points = []
    for i in range(n):
        points.append((random.randint(-10, 10), random.randint(-10, 10)))

    return points


triUtility = Geo.TriangulationUtils()

points_vector = generatePoints(100)

points = []
for p in points_vector:
    points.append(Geo.Point(p[0], p[1]))

discUtils = Geo.EnclosingDistUtils()
disc = discUtils.findDisc(points)

CirclePlot.PlotCircles().plotEnclosingDisc(points, disc)
