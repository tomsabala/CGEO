from build import libGeo_2D as Geo
from examples.Plots2D import SegmentsPlot

segments_coord = SegmentsPlot.generate_random_segments(20)

segments_test = [0 for i in range(20)]
for i, seg in enumerate(segments_coord):
    p = Geo.Point(seg[0][0], seg[0][1])
    q = Geo.Point(seg[1][0], seg[1][1])
    seg = Geo.Segment(p, q)
    segments_test[i] = seg

try:
    interUtility = Geo.SegmentIntersect()
    intersection_points = interUtility.intersection(segments_test)

    seg2plot = [[[seg.target.x, seg.target.y], [seg.origin.x, seg.origin.y]] for seg in segments_test]

    inter2plot = [[point.x, point.y] for point in intersection_points]

    SegmentsPlot.main(seg2plot, inter2plot)
except Exception as e:
    print(e)