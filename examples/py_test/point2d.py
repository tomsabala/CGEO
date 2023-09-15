from build import libGeo_2D as Geo

Point = Geo.libShapes_2D.Point

# constructors
p1 = Point()
p2 = Point(1, 2)

print("test")
print(p2)

print("p1 : {}".format(p1))
print("p2 : {}\n".format(p2))
# set x, y
p1.x = 2
p1.y = 1

print("p1 after setting other coordinates : {}\n".format(p1))

# copy details from another point
p2.copyPoint(Point(10, 10))

print("p2 after copy coordinates from other point : {}\n".format(p2))

# calculate norm and distance between two points
print("distance between p1 and p2 is {}".format(p2.dist(p1)))
print("p1 norm is {}\n".format(p1.norm()))

# compare between two points
print("p1 == p2 is {}".format(p1.__eq__(p2)))
p2.copyPoint(p1)
print("(after copying coordinates of p1 to p2)\np1 == p2 is {}\n".format(p1.__eq__(p2)))


# add and subtract
p2.x = 10
p2.y = 10
p1 = p1.subtract(p2)
print("p1 after subtract p1-p2\np1 : {}".format(p1))
p1 = p1.adder(p2)
print("p1 after adding p1+p2\np1 : {}\n".format(p1))

# orientation predicator for p = (0, 0), q = (1, 0), r = (1, 1)
p, q, r = Point(), Point(1, 1), Point(2, 1)
print("orientation for p->q and p->r is {} (negative)".format(p.oriePred(q, r)))
print("orientation for p->r and p->q is {} (positivenegative)\n".format(p.oriePred(r, q)))
