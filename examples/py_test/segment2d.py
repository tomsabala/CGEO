from build import libGeo_2D as Geo

# Constructors
s1 = Geo.Segment()
p = Geo.Point(1, 1)
q = Geo.Point(2, 2)
s2 = Geo.Segment(p, q)

# Output segments
print("s1 : {}".format(s1))
print("s2 : {}\n".format(s2))

# Change origin and target of segment
new_origin1, new_target1 = Geo.Point(0, 0), Geo.Point(1, 1)
s1.origin, s1.target = new_origin1, new_target1
new_origin2, new_target2 = Geo.Point(1, 1), Geo.Point(1, 2)
s2.origin, s2.target = new_origin2, new_target2

# Output segments
print("After changing properties: ")
print("s1 : {}".format(s1))
print("s2 : {}\n".format(s2))

# Print general info
print("General properties and methods use: ")
print("s2 length : {}".format(s2.getLength()))
print("s2 slope : {}".format(s2.getSlope()))
s2.rotate(90)
print("s2 slope after rotating with 90 degrees : {}".format(s2.getSlope()))
print("s2 : {}\n".format(s2))

# Orientation predict
print("collide s1 and s2 origin in order to use predict")
null_origin = Geo.Point()
s1.origin = null_origin
s2.origin = null_origin
print("s1 : {}".format(s1))
print("s2 : {}\n".format(s2))
print("orientation for s2->s1 is {} (positive)".format(s2.oriePred(s1)))
print("orientation for s1->s2 is {} (negative)\n".format(s1.oriePred(s2)))


