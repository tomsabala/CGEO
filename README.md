![C++](https://img.shields.io/badge/-c++-black?logo=c%2B%2B&style=social)![Computational Geometry](https://img.shields.io/static/v1?label=Computational&message=Geometry&color=%3CCOLOR%3E)![Python](https://img.shields.io/static/v1?label=Made%20With&message=Python&color=blue)
# CGEO

This project is a collection of several Computational Geometry Algorithms and Applications.

The algorithms are implemented in C++ and are wrapped with PyBind11 to use in Python.

The reason for the project is educational, I am challenging my self with implementing the algorithms so I can understand the theoretic material better.

This is an on-going project and has new features every now and then.

# How To Run

For some running examples you can checkout the [examples](https://github.com/tomsabala/CGEO/tree/main/examples) directory which has some cool examples for each class and algorithm. And you can also run each one of it by yourself.

I suggest reading the relevant examples before trying to use the functionality by yourself.

# Some Nice Examples
You can have a look on an output example on convex hull algorithm using [Graham Convex Hull Algorithm](https://en.wikipedia.org/wiki/Graham_scan) : <br />
<img src=examples/PlotImages/convex_hull.png width=250 height=250/> <img src=examples/PlotImages/Convex_Hull002.png width=250 height=250 />

The pink layer is the initial polygon form, and the green layer is the convex hull of the follow polygon.

Also, a nice usefull [y-monotonic](https://en.wikipedia.org/wiki/Monotone_polygon) decomposition of a polygon : <br />
<img src=examples/PlotImages/y_decomposition.png width=250 height=250 />

Here the initial polygon is the overall pink layer, and each sub-polygon is decomposed with an inner diagonal edge.
