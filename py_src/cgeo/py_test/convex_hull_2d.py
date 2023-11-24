from py_src.cgeo.plots_2d import polygon_plot as PolygonPlot
from py_src.cgeo.utilities.c_utilities.global_c_utils import *
from py_src.cgeo.utilities.get_random_polygon import generateRandomPolygonPoints

polygons = []

for i in range(10):
    dots = generateRandomPolygonPoints(center=(0, 0),
                                       avg_radius=20,
                                       irregularity=0.5,
                                       spikiness=0.5,
                                       num_vertices=20)
    points_arr = [Point(x, y) for x, y in dots]
    poly = Polygon(points_arr)
    convex_poly = giftWrapConvexHull(poly)
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
PolygonPlot.main(_tests=test, titles=["square", "dalton"])
