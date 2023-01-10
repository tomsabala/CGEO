from build import libGeo_2D as Geo
import random
import examples.Plots2D.CirclePlot as CirclePlot
import numpy as np

def generatePoints(n=10):
    points = []
    for i in range(n):
        points.append((random.randint(-10, 10), random.randint(-10, 10)))

    return points


triUtility = Geo.TriangulationUtils()

def GenerateRandomPointInPolygon(poly, n=10):
    # triangulate polygon
    triangles = triUtility.triangulate(poly)

    # calculate distribution by size of triangle
    triAreas = []
    polyArea = 0
    for tri in triangles:
        area = tri.area()
        polyArea += area
        triAreas.append(area)

    for i in range(len(triAreas)):
        triAreas[i] = triAreas[i]/polyArea

    points = []
    for i in range(n):
        # picking random triangle
        indices = np.arange(0, len(triAreas))
        triangle_ind = np.random.choice(indices, p=triAreas)
        triangle = triangles[triangle_ind]

        # picking random point with in triangle
        r1 = np.random.uniform(0, 1)
        r2 = np.random.uniform(0, 1)

        ax = triangle.a.x
        ay = triangle.a.y
        bx = triangle.b.x
        by = triangle.b.y
        cx = triangle.c.x
        cy = triangle.c.y

        px = (1 - np.sqrt(r1)) * ax + (np.sqrt(r1) * (1 - r2)) * bx + (np.sqrt(r1) * r2) * cx
        py = (1 - np.sqrt(r1)) * ay + (np.sqrt(r1) * (1 - r2)) * by + (np.sqrt(r1) * r2) * cy

        points.append(Geo.Point(px, py))

    return points


def GenerateRandomPointsInString():
    """
    we wish to draw a string on the plane by picking random points for each letter,
    given the letter a shape of a polygon
    :return: "SMALLEST ENCLOSING DISC" in the plane
    """

    S1 = Geo.Polygon([Geo.Point(-13.9387483128614, 10.5805248225835), Geo.Point(-11.5328709614751, 10.1604509993256),
                      Geo.Point(-11.6092480202493, 9.3584918821969), Geo.Point(-13.0222236075714, 9.3584918821969),
                      Geo.Point(-13.0222236075714, 8.3274015887456), Geo.Point(-11.1891741969914, 8.7092868826164),
                      Geo.Point(-11.5710594908622, 6.188843943069), Geo.Point(-14, 6.1128912170395),
                      Geo.Point(-14.0151253716355, 6.9144260014236), Geo.Point(-12.4493956667651, 6.6089177663269),
                      Geo.Point(-12.411207137378, 7.9073277654877), Geo.Point(-13.785994195313, 7.5254424716169)])

    M = Geo.Polygon([Geo.Point(-10.3872150798626, 5.9215242373594), Geo.Point(-9.5470674333468, 10.1986395287127),
                     Geo.Point(-8.0959033166376, 9.0529836471002), Geo.Point(-7.332132728896, 9.893131293616),
                     Geo.Point(-5.7282144946385, 6.5325407075527), Geo.Point(-7.2557556701218, 6.3415980606173),
                     Geo.Point(-7.5612639052185, 8.518344235681), Geo.Point(-8.286845963573, 7.6781965891652),
                     Geo.Point(-8.745108316218, 8.9002295295519), Geo.Point(-9.165182139476, 6.0742783549077)])

    A = Geo.Polygon([Geo.Point(-4.8577195382737, 6.2455905864338), Geo.Point(-3.4369027314135, 9.3966804115839),
                     Geo.Point(-1.4892877326722, 6.2652210018431), Geo.Point(-2.6349436142847, 6.3034095312302),
                     Geo.Point(-2.7876977318331, 7.2199342365202), Geo.Point(-3.7424109665101, 7.2963112952944),
                     Geo.Point(-4, 6)])

    L1 = Geo.Polygon([Geo.Point(-1.3365336151239, 9.5876230585194), Geo.Point(-0.1526892041243, 9.6640001172935),
                      Geo.Point(-0.1494327252791, 6.8548982916448), Geo.Point(0.6874584423915, 7.105368648359),
                      Geo.Point(0.916589618714, 6.2270324724561), Geo.Point(0.916589618714, 6.2270324724561)])

    L2 = Geo.Polygon([Geo.Point(1.6421716770686, 9.7403771760677), Geo.Point(1.6421716770686, 9.7403771760677),
                      Geo.Point(2.6732619705198, 6.7234833544881), Geo.Point(4.0862375578419, 7.1817457071331),
                      Geo.Point(4, 6), Geo.Point(1.8023260909042, 5.8816520428068)])

    E1 = Geo.Polygon([Geo.Point(4.9263852043577, 9.7785657054548), Geo.Point(6.4539263798411, 9.9313198230031),
                     Geo.Point(7.1031313794215, 9.2821148234227), Geo.Point(5.6901557920994, 9.0529836471002),
                     Geo.Point(5.6901557920994, 8.3655901181327), Geo.Point(7.4850166732923, 8.4801557062939),
                     Geo.Point(7.6377707908407, 7.563631001004), Geo.Point(5.8810984390348, 7.6781965891652),
                     Geo.Point(5.9192869684219, 6.6089177663269), Geo.Point(7.1795084381957, 7.105368648359),
                     Geo.Point(7.4086396145182, 6.1506554136819), Geo.Point(5.0643791191854, 5.9456451924602)])

    S2 = Geo.Polygon([Geo.Point(8.6306725549048, 10.6187133519706), Geo.Point(10.8837957887427, 10.7332789401318),
                      Geo.Point(10.9219843181298, 9.5494345291323), Geo.Point(9.5471972601948, 10.0458854111643),
                      Geo.Point(9.3562546132594, 8.7474754120035), Geo.Point(10.6546646124202, 8.9384180589389),
                      Geo.Point(10.540099024259, 6.3415980606173), Geo.Point(8.6059397993459, 6.200580989049),
                      Geo.Point(8.5542954961306, 7.2199342365202), Geo.Point(9.9672710834527, 7.0289915895848),
                      Geo.Point(10, 8), Geo.Point(8.6306725549048, 7.9837048242619)])

    T = Geo.Polygon([Geo.Point(11.5330007883231, 10.8860330576802), Geo.Point(14.3207634335802, 10.4277707050352),
                     Geo.Point(14.3589519629673, 9.3966804115839), Geo.Point(13.289673140129, 9.7785657054548),
                     Geo.Point(13.2514846107419, 6.2270324724561), Geo.Point(11.7239434352586, 6.3034095312302),
                     Geo.Point(12.2585828466777, 9.7785657054548), Geo.Point(11.4184352001619, 10.1604509993256)])

    E2 = Geo.Polygon([Geo.Point(-16.0616843665375, 4.7071290028502), Geo.Point(-12.6995555417304, 4.5361732998939),
                      Geo.Point(-12.6425703074116, 3.1115424419248), Geo.Point(-15.3208763203935, 3.3394833791998),
                      Geo.Point(-15.3208763203935, 2.2567639271433), Geo.Point(-13.3833783535555, 2.1997786928245),
                      Geo.Point(-13.0414669476429, 0.6041921318991), Geo.Point(-15.206905851756, 1.0600740064493),
                      Geo.Point(-15.206905851756, -0.4215420858386), Geo.Point(-13.7822749937869, -0.1936011485636),
                      Geo.Point(-13.3833783535555, -1.2763206006201), Geo.Point(-16.2675322027503, -1.5195670333831)])

    N1 = Geo.Polygon([Geo.Point(-11.6168360896738, 4.3652175969376), Geo.Point(-10.4771314032985, 4.2512471283),
                      Geo.Point(-9.4513971855608, 0.6611773662179), Geo.Point(-8.9385300766919, 4.3652175969376),
                      Geo.Point(-7.6278696873603, 4.1942618939813), Geo.Point(-8.3686777335042, -1.2193353663013),
                      Geo.Point(-10.0212495287484, -0.9344091947075), Geo.Point(-10.8990948181647, 2.7175843503024),
                      Geo.Point(-11.1609542151237, -0.9913944290263), Geo.Point(-12.1297031985427, -1.1053648976638)])

    C1 = Geo.Polygon([Geo.Point(-6.8344992621951, 4.2843633925747), Geo.Point(-3.7528737536843, 4.1372766596625),
                      Geo.Point(-3.581918050728, 2.9405867389685), Geo.Point(-5.9183126577973, 3.3964686135186),
                      Geo.Point(-6.0322831264349, 0.2052954916678), Geo.Point(-3.6389032850468, 0.7181626005367),
                      Geo.Point(-3.6389032850468, -0.4215420858386), Geo.Point(-7.0010321098539, -0.9913944290263)])

    L3 = Geo.Polygon([Geo.Point(-2.1654389041131, 4.1599221052698), Geo.Point(-1.1885382093399, 4.1942618939813),
                     Geo.Point(-1.8153757868463, 0.3762511946241), Geo.Point(-0.1058187572833, 1.0600740064493),
                     Geo.Point(-0.3907449288772, -0.2505863828823), Geo.Point(-2.61049550432, -0.6953740131304)])

    O = Geo.Polygon([Geo.Point(1.3757973350046, 4.2512471283), Geo.Point(3.940132879349, 4.4222028312563),
                     Geo.Point(3.2563100675238, -0.1366159142448), Geo.Point(0.845289865294, -0.399576077101)])

    S3 = Geo.Polygon([Geo.Point(8.6306725549048-3.20892358, 10.6187133519706-5.62665817753 ), Geo.Point(10.8837957887427-3.20892358, 10.7332789401318-5.62665817753 ),
                      Geo.Point(10.9219843181298-3.20892358, 9.5494345291323-5.62665817753 ), Geo.Point(9.5471972601948-3.20892358, 10.0458854111643-5.62665817753 ),
                      Geo.Point(9.3562546132594-3.20892358, 8.7474754120035-5.62665817753 ), Geo.Point(10.6546646124202-3.20892358, 8.9384180589389-5.62665817753 ),
                      Geo.Point(10.540099024259-3.20892358, 6.3415980606173-5.62665817753 ), Geo.Point(8.6059397993459-3.20892358, 6.200580989049-5.62665817753 ),
                      Geo.Point(8.5542954961306-3.20892358, 7.2199342365202-5.62665817753 ), Geo.Point(9.9672710834527-3.20892358, 7.0289915895848-5.62665817753 ),
                      Geo.Point(10-3.20892358, 8-5.62665817753 ), Geo.Point(8.6306725549048-3.20892358, 7.9837048242619-5.62665817753 )])

    I1 = Geo.Polygon([Geo.Point(10.2085086544131, 4.3082323626188), Geo.Point(11.2342428721509, 4.3652175969376),
                      Geo.Point(11.0632871691946, -0.7064682574324), Geo.Point(10, 0)])

    N2 = Geo.Polygon([Geo.Point(12.5449032614825, 4.5931585342126), Geo.Point(13.6846079478577, 4.4791880655751),
                      Geo.Point(14.7103421655955, 0.889118303493), Geo.Point(15.2232092744644, 4.5931585342126),
                      Geo.Point(16.533869663796, 4.4222028312563), Geo.Point(15.793061617652, -0.9913944290263),
                      Geo.Point(14.1404898224079, -0.7064682574324), Geo.Point(13.2626445329915, 2.9455252875775),
                      Geo.Point(13.0007851360326, -0.7634534917512), Geo.Point(12.0320361526136, -0.8774239603887)])

    G = Geo.Polygon([Geo.Point(17.5596038815338, 4.023306191025), Geo.Point(21.4915850495285, 4.023306191025),
                     Geo.Point(21.9474669240786, 2.5416900987371), Geo.Point(18.7562938022278, 3.1685276762435),
                     Geo.Point(18.4143823963152, 0.0913250230303), Geo.Point(20.6368065347471, -0.4785273201574),
                     Geo.Point(19.7250427856468, 1.9718377555495), Geo.Point(21.0357031749784, 2.085808224187),
                     Geo.Point(21.5485702838473, -1.2763206006201), Geo.Point(17.3103400013876, -1.2645497567254)])

    D = Geo.Polygon([Geo.Point(-7.1719878128102, -2.8719071615455),
                     Geo.Point(-4.6076522684658, -5.6641836431649),
                     Geo.Point(-7.0409729817695, -9.0666808623293)])

    I2 = Geo.Polygon([Geo.Point(-3.581918050728, -2.3020548183578), Geo.Point(-2.7271395359465, -2.2450695840391),
                      Geo.Point(-2.7271395359465, -9.1402829366095), Geo.Point(-3.6958885193655, -9.2542534052471)])

    S4 = Geo.Polygon([Geo.Point(8.6306725549048-9.47729935833, 10.6187133519706-13.8325319194 ), Geo.Point(10.8837957887427-9.47729935833, 10.7332789401318-13.8325319194 ),
                      Geo.Point(10.9219843181298-9.47729935833, 9.5494345291323-13.8325319194 ), Geo.Point(9.5471972601948-9.47729935833, 10.0458854111643-13.8325319194 ),
                      Geo.Point(9.3562546132594-9.47729935833, 8.7474754120035-13.8325319194), Geo.Point(10.6546646124202-9.47729935833, 8.9384180589389-13.8325319194 ),
                      Geo.Point(10.540099024259-9.47729935833, 6.3415980606173-13.8325319194), Geo.Point(8.6059397993459-9.47729935833, 6.200580989049-13.8325319194),
                      Geo.Point(8.5542954961306-9.47729935833, 7.2199342365202-13.8325319194), Geo.Point(9.9672710834527-9.47729935833, 7.0289915895848-13.8325319194 ),
                      Geo.Point(10-9.47729935833, 8-13.8325319194), Geo.Point(8.6306725549048-9.47729935833, 7.9837048242619-13.8325319194 )])

    C2 = Geo.Polygon([Geo.Point(5.3617126194013, -3.1758563071167), Geo.Point(9.011818733719, -3.1568333331393),
                      Geo.Point(8.3849811562126, -4.4105084881521), Geo.Point(6.0485865491433, -4.2965380195146),
                      Geo.Point(5.9916013148245, -7.2597702040903), Geo.Point(8.8408630307627, -6.6329326265839),
                      Geo.Point(9.011818733719, -7.7156520786404), Geo.Point(4.9658670970867, -8.8553567650157)])

    return GenerateRandomPointInPolygon(S1, 200) + GenerateRandomPointInPolygon(M, 200) + GenerateRandomPointInPolygon(A, 200) +\
        GenerateRandomPointInPolygon(L1, 200) + GenerateRandomPointInPolygon(L2, 200) + GenerateRandomPointInPolygon(E1, 200) + \
        GenerateRandomPointInPolygon(S2, 200) + GenerateRandomPointInPolygon(T, 200) + GenerateRandomPointInPolygon(E2, 200) + \
        GenerateRandomPointInPolygon(N1, 200)  + GenerateRandomPointInPolygon(C1, 200) + GenerateRandomPointInPolygon(L3, 200) +\
        GenerateRandomPointInPolygon(O, 200) + GenerateRandomPointInPolygon(S3, 200) + GenerateRandomPointInPolygon(I1, 200) +\
        GenerateRandomPointInPolygon(N2, 200) + GenerateRandomPointInPolygon(G, 200) + GenerateRandomPointInPolygon(D, 200) + \
    GenerateRandomPointInPolygon(I2, 200) + GenerateRandomPointInPolygon(S4, 200) + GenerateRandomPointInPolygon(C2, 200)


points_vector = GenerateRandomPointsInString()

# for i in range(len(points_vector)):
#     x, y = points_vector[i][0], points_vector[i][1]
#     points_vector[i] = Geo.Point(x, y)

discUtils = Geo.EnclosingDistUtils()
disc = discUtils.findDisc(points_vector)

CirclePlot.PlotCircles().plotEnclosingDisc(points_vector, disc)
