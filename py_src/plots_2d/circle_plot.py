import matplotlib.pyplot as plt
from matplotlib import patches


class PlotCircles:
    def __init__(self):
        pass

    @staticmethod
    def plotEnclosingDisc(dots, circle) -> None:

        fig = plt.figure()
        ax = fig.add_subplot()
        circle1 = patches.Circle((circle.center.x, circle.center.y), radius=circle.r, edgecolor='blue', fill=False)
        ax.add_patch(circle1)
        ax.axis('equal')

        for dot in dots:
            plt.scatter(dot.x, dot.y, color='black', s=5)
        plt.grid()
        plt.show()