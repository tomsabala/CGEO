from build import libGeo_2D as Geo
from py_src.plots_2d import segments_plot

Point = Geo.libShapes_2D.Point
Segment = Geo.libShapes_2D.Segment

interUtility = Geo.libAlgorithms_2D.SegmentIntersect()


segments_coord = SegmentsPlot.generate_random_segments(20)

segments_test = []
for i, seg in enumerate(segments_coord):
    p = Point(seg[0][0], seg[0][1])
    q = Point(seg[1][0], seg[1][1])
    seg = Segment(p, q)
    segments_test.append(seg)

try:
    intersection_points = interUtility.intersection(segments_test)

    seg2plot = [[[seg.target.x, seg.target.y], [seg.origin.x, seg.origin.y]] for seg in segments_test]

    inter2plot = [[point.x, point.y] for point in intersection_points]

    SegmentsPlot.main(seg2plot, inter2plot)
except Exception as e:
    print(e)