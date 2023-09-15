from build import libGeo_2D as Geo

Point = Geo.libShapes_2D.Point
Polygon = Geo.libShapes_2D.Polygon

# init polygon
points_arr = []
for x, y in [(0, 0), (1, 0), (1, 1), (0, 1)]:
    points_arr.append(Point(x, y))
poly = Polygon(points_arr)

# print edges
edges_list = poly.getEdges()
for e in edges_list:
    print(e)

# check if convex
print("\nsquare is convex : {}".format(poly.isConvex()))
print("square is y-monotone : {}\n".format(poly.isY_Monotone()))

print("on the other hand if we construct another non convex nor y-monotone such as : \n")
# construct example polygon
test_poly = Polygon([Geo.Point(x, y) for x, y in [(0, 0), (-3, 3), (0, 1), (3, 3)]])

# print edges
edges_list = test_poly.getEdges()
for e in edges_list:
    print(e)


# check if convex
print("\ndalton is not convex : {}".format(test_poly.isConvex()))
print("dalton is not y-monotone : {}\n".format(test_poly.isY_Monotone()))
