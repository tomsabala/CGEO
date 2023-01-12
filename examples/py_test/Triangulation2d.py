from build import libGeo_2D as Geo
from examples.Plots2D import PolygonPlot


_utility = Geo.TriangulationUtils()

plt = PolygonPlot.PlotPolygon()
for i in range(10):
    dots = PolygonPlot.generateRandomPolygons(center=(0, 0),
                                              avg_radius=20,
                                              irregularity=0.5,
                                              spikiness=0.5,
                                              num_vertices=10)

    points_arr = [Geo.Point(x, y) for x, y in dots]
    poly = Geo.Polygon(points_arr)

    # decompose to triangles
    Triangles = _utility.triangulate(poly)
    edges = []

    for i, tri in enumerate(Triangles):
        vertex = tri.getVertex()
        edges.append((vertex[0], vertex[1]))
        edges.append((vertex[1], vertex[2]))
        edges.append((vertex[2], vertex[0]))

    plt.plotTriangulation(Poly=dots, Triangles=edges)

