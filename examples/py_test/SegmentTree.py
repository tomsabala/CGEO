from build import libGeo_2D as Geo

Point = Geo.libShapes_2D.Point
Segment = Geo.libShapes_2D.Segment
SegmentTree = Geo.libAlgorithms_2D.SegmentTree

p1, q1 = Point(2, 10), Point(6, 6)
s1 = Segment(p1, q1)
p2, q2 = Point(6, 2), Point(8, 6)
s2 = Segment(p2, q2)
p3, q3 = Point(8, 8), Point(10, 4)
s3 = Segment(p3, q3)
p4, q4 = Point(10, 2), Point(12, 6)
s4 = Segment(p4, q4)

tree = SegmentTree()

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


