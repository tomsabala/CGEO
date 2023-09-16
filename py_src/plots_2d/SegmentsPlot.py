import matplotlib.pyplot as plt
import numpy as np

class PlotSegments:
    def __init__(self):
        pass

    def plot(self, xy: np.array, dots, **kwargs) -> None:

        fig, ax = plt.subplots(figsize=(10, 10))
        ab_pairs = np.c_[xy[0], xy[1]]
        ab_args = ab_pairs.reshape(-1, 2, 2).swapaxes(1, 2).reshape(-1, 2)

        # segments
        ax.plot(*ab_args, c='k')
        for dot in dots:
            plt.scatter([dot[0]], [dot[1]], color='blue')
        plt.grid()
        plt.show()


def generate_random_segments(n: int) -> list:
    import random

    segments = []
    for i in range(n):
        x1, y1 = random.randint(0, 20), random.randint(0, 20)
        x2, y2 = random.randint(0, 20), random.randint(0, 20)

        while x1 == x2 and y1 == y2:
            x1, y1 = random.randint(0, 20), random.randint(0, 20)
            x2, y2 = random.randint(0, 20), random.randint(0, 20)

        segments.append([[x1, y1], [x2, y2]])

    return segments


def main(segments, dots):
    _x = []
    _y = []
    for seg in segments:
        _x.append(seg[0][0])
        _x.append(seg[1][0])
        _y.append(seg[0][1])
        _y.append(seg[1][1])
    kwargs = {'max_x': max(_x), 'min_x': min(_x), 'max_y': max(_y), 'min_y': min(_y)}

    PlotSegments().plot([_x, _y], dots, **kwargs)