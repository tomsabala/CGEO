from build import libGeo_2D as Geo
from examples.Plots2D import PolygonPlot


# dots = PolygonPlot.generateRandomPolygons(center=(0, 0),
#                                       avg_radius=10,
#                                       irregularity=0.2,
#                                       spikiness=0.5,
#                                       num_vertices=20)

dots = [(-12.95, -15.60),
        (-28.36, -7.77),
        (-8.80, 5.66),
        (-12.11, 24.69),
        (2.26, 12.54),
        (11.47, 14.70),
        (8.85, 1.53),
        (16.55, -6.14),
        (6.31, -11.63),
        (-10.28, -33.66)
        ]

points_arr = [Geo.Point(x, y) for x, y in dots]
poly = Geo.Polygon(points_arr)

for p in poly.getVertices():
    print(p)

sub_polygons = Geo.Polygon.decomposeY_Monotone(poly)

sub_polygons_points = []
for p in sub_polygons:
    sub_polygons_points.append(p.getEdges())

PolygonPlot.PlotPolygon().plotPolygons(dots, sub_polygons_points)
