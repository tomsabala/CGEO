from build import libGeo_2D as Geo
from examples.Plots2D import PolygonPlot


dots = PolygonPlot.generateRandomPolygons(center=(0, 0),
                                          avg_radius=10,
                                          irregularity=0.5,
                                          spikiness=0.5,
                                          num_vertices=20)
# dots = [(1, 0), (1, 2), (2, 3), (3, 1), (4, 3), (4, 4),
#         (5, 4), (5, 2), (6, 2), (5, 1), (6, 0), (5, -1),
#         (4, 0), (4, -2), (2, -1), (2, 1)]

points_arr = [Geo.Point(x, y) for x, y in dots]
poly = Geo.Polygon(points_arr)

for p in poly.getVertices():
    print(p)

sub_polygons = Geo.Polygon.decomposeY_Monotone(poly)

sub_polygons_points = []
for p in sub_polygons:
    sub_polygons_points.append(p.getEdges())

PolygonPlot.PlotPolygon().plotPolygons(dots, sub_polygons_points)
