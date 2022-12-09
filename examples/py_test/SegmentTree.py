from build import libGeo_2D as Geo

p1, q1 = Geo.Point(2, 10), Geo.Point(6, 6)
s1 = Geo.Segment(p1, q1)
p2, q2 = Geo.Point(6, 2), Geo.Point(8, 6)
s2 = Geo.Segment(p2, q2)
p3, q3 = Geo.Point(8, 8), Geo.Point(10, 4)
s3 = Geo.Segment(p3, q3)
p4, q4 = Geo.Point(10, 2), Geo.Point(12, 6)
s4 = Geo.Segment(p4, q4)

tree = Geo.SegmentTree()

print(s1)
print(s2)
print(s3)
print(s4)
print()

tree.setHeight(p1)
tree.insert(s1)

tree.setHeight(p3)
tree.insert(s3)

tree.setHeight(q2)
tree.insert(s2)

tree.setHeight(q4)
tree.insert(s4)

tree.InOrder(tree.getRoot())


