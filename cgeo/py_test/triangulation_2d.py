from cgeo.plots_2d import polygon_plot as PolygonPlot
from cgeo.utilities.c_utilities.global_c_utils import triangulate
from cgeo.modules.point_2d import Point2D as Point
from cgeo.modules.polygon import Polygon
from cgeo.utilities.get_random_polygon import generateRandomPolygonPoints


plt = PolygonPlot.PlotPolygon()
for i in range(10):
    dots = generateRandomPolygonPoints(center=(0, 0),
                                       avg_radius=20,
                                       irregularity=0.5,
                                       spikiness=0.5,
                                       num_vertices=10)

    points_arr = [Point(x, y) for x, y in dots]
    poly = Polygon(points_arr)

    # decompose to triangles
    Triangles = triangulate(poly)
    edges = []

    for tri in Triangles:
        vertex = tri.getVertices()
        edges.append((vertex[0], vertex[1]))
        edges.append((vertex[1], vertex[2]))
        edges.append((vertex[2], vertex[0]))

    plt.plotTriangulation(Poly=dots, Triangles=edges)

