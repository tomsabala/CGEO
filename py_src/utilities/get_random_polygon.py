import math
from typing import Tuple, List
import random
from math import atan2


def toConvexContour(num_vertices: int) -> List[Tuple[float, float]]:
    """
    Port of Valtr algorithm by Sander Verdonschot.

    imp from: https://stackoverflow.com/questions/6758083/how-to-generate-a-random-convex-polygon

    """
    xs = [random.uniform(-10, 10) for _ in range(num_vertices)]
    ys = [random.uniform(-10, 10) for _ in range(num_vertices)]
    xs = sorted(xs)
    ys = sorted(ys)
    minX, *xs, maxX = xs
    minY, *ys, maxY = ys
    vectorsXS = _toVectorsCoordinates(coordinates=xs, minCoordinate=minX, maxCoordinate=maxX)
    vectorsYS = _toVectorsCoordinates(coordinates=ys, minCoordinate=minY, maxCoordinate=maxY)
    random.shuffle(vectorsYS)

    def _toVectorAngle(vector):
        x, y = vector
        return atan2(y, x)

    vectors = sorted(zip(vectorsXS, vectorsYS),
                     key=_toVectorAngle)
    pointX = pointY = 0
    minPolygonX = minPolygonY = 0
    points = []
    for vectorX, vectorY in vectors:
        points.append((pointX, pointY))
        pointX += vectorX
        pointY += vectorY
        minPolygonX = min(minPolygonX, pointX)
        minPolygonX = min(minPolygonY, pointY)
    shiftX, shiftY = minX - minPolygonX, minY - minPolygonY
    return [(x + shiftX, y + shiftY)
            for x, y in points]


def _toVectorsCoordinates(coordinates: List[float], minCoordinate: float, maxCoordinate: float) -> list:
    lastMin = lastMax = minCoordinate
    result = []
    for coordinate in coordinates:
        if _toRandomBoolean():
            result.append(coordinate - lastMin)
            lastMin = coordinate
        else:
            result.append(lastMax - coordinate)
            lastMax = coordinate
    result.extend((maxCoordinate - lastMin,
                   lastMax - maxCoordinate))
    return result


def _toRandomBoolean():
    return random.getrandbits(1)


def generateRandomPolygonPoints(center: Tuple[float, float], avg_radius: float,
                                irregularity: float, spikiness: float,
                                num_vertices: int) -> List[Tuple[float, float]]:
    """
        imp from https://stackoverflow.com/questions/8997099/algorithm-to-generate-random-2d-polygon
    """
    # Parameter check
    if irregularity < 0 or irregularity > 1:
        raise ValueError("Irregularity must be between 0 and 1.")
    if spikiness < 0 or spikiness > 1:
        raise ValueError("Spikiness must be between 0 and 1.")

    irregularity *= 2 * math.pi / num_vertices
    spikiness *= avg_radius
    angle_steps = randomAngleSteps(num_vertices, irregularity)

    # now generate the points
    points_set = set()
    points = []
    angle = random.uniform(0, 2 * math.pi)
    counter = 0
    while counter < num_vertices:
        radius = clip(random.gauss(avg_radius, spikiness), 0, 2 * avg_radius)
        point = (center[0] + radius * math.cos(angle),
                 center[1] + radius * math.sin(angle))
        if point in points_set:
            continue
        points.append(point)
        angle += angle_steps[counter]
        points_set.add(point)
        counter += 1

    return points


def randomAngleSteps(steps: int, irregularity: float) -> List[float]:
    # generate n angle steps
    angles = []
    lower = (2 * math.pi / steps) - irregularity
    upper = (2 * math.pi / steps) + irregularity
    cumsum = 0
    for i in range(steps):
        angle = random.uniform(lower, upper)
        angles.append(angle)
        cumsum += angle

    # normalize the steps so that point 0 and point n+1 are the same
    cumsum /= (2 * math.pi)
    for i in range(steps):
        angles[i] /= cumsum
    return angles


def clip(value, lower, upper):
    return min(upper, max(value, lower))
