from py_src.plots_2d import polygon_plot as PolygonPlot
from py_src.modules.point_2d import Point2D as Point
from py_src.modules.polygon import Polygon


dots = PolygonPlot.generateRandomPolygons(center=(0, 0),
                                          avg_radius=10,
                                          irregularity=0.2,
                                          spikiness=0.5,
                                          num_vertices=20)

points_arr = [Point(x, y) for x, y in dots]
poly = Polygon(points_arr)

sub_polygons = poly.decomposeToYMonotone()

sub_polygons_points = []
for p in sub_polygons:
    sub_polygons_points.append(p.getEdges())

PolygonPlot.PlotPolygon().plotPolygons(dots, sub_polygons_points)
