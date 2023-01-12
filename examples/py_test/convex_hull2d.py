from build import libGeo_2D as Geo
from examples.Plots2D import PolygonPlot

_utility = Geo.ConvexHullUtils()
polygons = []

for i in range(10):
    dots = PolygonPlot.generateRandomPolygons(center=(0, 0),
                                              avg_radius=20,
                                              irregularity=0.5,
                                              spikiness=0.5,
                                              num_vertices=20)
    points_arr = [Geo.Point(x, y) for x, y in dots]
    poly = Geo.Polygon(points_arr)
    convex_poly = _utility.grahamConvexHull(poly)
    polygons.append((poly, convex_poly))

test = []
for poly1, poly2 in polygons:
    curr1 = []
    for p in poly1.getVertices():
        curr1.append([p.x, p.y])
    curr2 = []
    for p in poly2.getVertices():
        curr2.append([p.x, p.y])
    test.append((curr1, curr2))
PolygonPlot.main(tests=test, titles=["square", "dalton"])
