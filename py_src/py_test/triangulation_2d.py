from build import libGeo_2D as Geo
from py_src.plots_2d import polygon_plot


_utility = Geo.TriangulationUtils()
Point = Geo.libShapes_2D.Point
Polygon = Geo.libShapes_2D.Polygon


plt = PolygonPlot.PlotPolygon()
for i in range(10):
    dots = PolygonPlot.generateRandomPolygons(center=(0, 0),
                                              avg_radius=20,
                                              irregularity=0.5,
                                              spikiness=0.5,
                                              num_vertices=10)

    points_arr = [Point(x, y) for x, y in dots]
    poly = Polygon(points_arr)

    # decompose to triangles
    Triangles = _utility.triangulate(poly)
    edges = []

    for tri in Triangles:
        vertex = tri.getVertex()
        edges.append((vertex[0], vertex[1]))
        edges.append((vertex[1], vertex[2]))
        edges.append((vertex[2], vertex[0]))

    plt.plotTriangulation(Poly=dots, Triangles=edges)
