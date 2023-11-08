import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Polygon


class PlotPolygon:
    def __init__(self):
        pass

    @staticmethod
    def plotConvexHull(dots: np.array, **kwargs) -> None:

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

    def plotPolygons(self, poly: np.array, sub_polygons: np.array) -> None:

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

    @staticmethod
    def getBoundingBox(dots):
        x = [x for (x, _) in dots]
        y = [y for (_, y) in dots]

        return max(x), min(x), max(y), min(y)


def main(_tests, titles=None):
    for test1, test2 in _tests:
        _plt = PlotPolygon()
        max_x, min_x, max_y, min_y = _plt.getBoundingBox(test1)

        kwargs = {'max_x': max_x, 'min_x': min_x, 'max_y': max_y, 'min_y': min_y, 'hull': test2, 'titles': titles}
        PlotPolygon().plotConvexHull(test1, **kwargs)


if __name__ == "__main__":
    tests = [
        [[1, 1], [-1, -1], [1, -1]],
        [[0, 1], [1, 4], [6, 2], [1, 2], [0.5, 1.5]],
        [[0, 0], [0, 1], [1, 1], [1, 0]],
        [[0, 0], [1, 1], [0, 1], [1, 0]],
    ]
    main(tests)
