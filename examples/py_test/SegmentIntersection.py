from build import libGeo_2D as Geo
from examples.Plots2D import SegmentsPlot

# segments_coord = SegmentsPlot.generate_random_segments(5)
# segments_test = [0 for i in range(5)]
# for i, seg in enumerate(segments_coord):
#     p = Geo.Point(seg[0][0], seg[0][1])
#     q = Geo.Point(seg[1][0], seg[1][1])
#     seg = Geo.Segment(p, q)
#     segments_test[i] = seg

segments_test = [i for i in range(5)]
segments_test[0] = Geo.Segment(Geo.Point(1.00, 5.00), Geo.Point(0.00, 4.00))
segments_test[1] = Geo.Segment(Geo.Point(0.00, 4.00), Geo.Point(9.00, 3.00))
segments_test[2] = Geo.Segment(Geo.Point(1.00, 4.00), Geo.Point(8.00, 3.00))
segments_test[3] = Geo.Segment(Geo.Point(5.00, 5.00), Geo.Point(6.00, 2.00))
segments_test[4] = Geo.Segment(Geo.Point(7.00, 5.00), Geo.Point(3.00, 2.00))


print("segments test: ")
for i in range(len(segments_test)):
    print(segments_test[i])
print("")

try:
    interUtility = Geo.SegmentIntersect()
    intersection_points = interUtility.intersection(segments_test)

    seg2plot = [[[seg.target.x, seg.target.y], [seg.origin.x, seg.origin.y]] for seg in segments_test]

    inter2plot = [[point.x, point.y] for point in intersection_points]

    SegmentsPlot.main(seg2plot, inter2plot)
except Exception as e:
    print(e)