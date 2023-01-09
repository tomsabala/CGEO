from build import libGeo_2D as Geo
import random
import examples.Plots2D.CirclePlot as CirclePlot

def generatePoints(n=10):
    points = []
    for i in range(n):
        points.append((random.randint(-10, 10), random.randint(-10, 10)))

    return points


discUtils = Geo.EnclosingDistUtils()

points_vector = generatePoints()

# points_vector = [(6.00, -10.00), (0.00, 10.00), (2.00, 6.00), (7.00, 9.00), (-6.00, -9.00),
#                  (8.00, -7.00), (-5.00, 5.00), (-2.00, 10.00), (-7.00, 9.00), (-10.00, -10.00)]

for i in range(len(points_vector)):
    x, y = points_vector[i][0], points_vector[i][1]
    points_vector[i] = Geo.Point(x, y)
#
# for point in points_vector:
#     print(point)

disc = discUtils.findDisc(points_vector)

CirclePlot.PlotCircles().plotEnclosingDisc(points_vector, disc)

