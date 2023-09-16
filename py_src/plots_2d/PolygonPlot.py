
import math
import random
from typing import List, Tuple

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Polygon


class PlotPolygon:
    def __init__(self):
        pass

    def plotConvexHull(self, dots: np.array, **kwargs) -> None:

        """
        imp from : https://stackoverflow.com/questions/43971259/how-to-draw-polygons-with-python
        """
        q = Polygon(kwargs['hull'], facecolor='lightgreen', edgecolor='lightgreen')
        p = Polygon(dots, facecolor='pink', edgecolor='black')
        _, ax = plt.subplots()
        ax.add_patch(q)
        ax.add_patch(p)
        ax.set_xlim([kwargs['min_x'] - 1, kwargs['max_x'] + 1])
        ax.set_ylim([kwargs['min_y'] - 1, kwargs['max_y'] + 1])

        for [x, y] in dots:
            plt.scatter(x, y, color='black')
        for [x, y] in kwargs['hull']:
            plt.scatter(x, y, color='black')
        plt.show()

    def plotPolygons(self, poly: np.array, sub_polygons: np.array) ->None:

        p = Polygon(poly, facecolor='pink', edgecolor='black')
        _, ax = plt.subplots()
        ax.add_patch(p)
        max_x, min_x, max_y, min_y = self.getBoundingBox(poly)

        ax.set_xlim([min_x - 1, max_x + 1])
        ax.set_ylim([min_y - 1, max_y + 1])

        for sub_poly in sub_polygons:
            for edge in sub_poly:
                plt.plot([edge.origin.x, edge.target.x], [edge.origin.y, edge.target.y], color='black')
        plt.show()

    def plotTriangulation(self, Poly: np.array, Triangles: np.array) -> None:
        p = Polygon(Poly, facecolor='pink', edgecolor='black')
        _, ax = plt.subplots()
        ax.add_patch(p)

        max_x, min_x, max_y, min_y = self.getBoundingBox(Poly)

        ax.set_xlim([min_x - 1, max_x + 1])
        ax.set_ylim([min_y - 1, max_y + 1])

        for [x, y] in Poly:
            plt.scatter(x, y, color='black')
        for [x, y] in Triangles:
            plt.plot([x.x, y.x], [x.y, y.y], color='blue', marker='|')
        plt.show()


    def getBoundingBox(self, dots):
        x = [x for (x, _) in dots]
        y = [y for (_, y) in dots]

        return max(x), min(x), max(y), min(y)

def main(tests, titles=None):
    for test1, test2 in tests:
        plt = PlotPolygon()
        max_x, min_x, max_y, min_y = plt.getBoundingBox(test1)

        kwargs = {'max_x': max_x, 'min_x': min_x, 'max_y': max_y, 'min_y': min_y, 'hull': test2, 'titles': titles}
        PlotPolygon().plotConvexHull(test1, **kwargs)


def generateRandomPolygons(center: Tuple[float, float], avg_radius: float,
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
    angle_steps = random_angle_steps(num_vertices, irregularity)

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


def random_angle_steps(steps: int, irregularity: float) -> List[float]:
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


if __name__ == "__main__":

    tests = [
        [[1, 1], [-1, -1], [1, -1]],
        [[0, 1], [1, 4], [6, 2], [1, 2], [0.5, 1.5]],
        [[0, 0], [0, 1], [1, 1], [1, 0]],
        [[0, 0], [1, 1], [0, 1], [1, 0]],
    ]
    main(tests)


