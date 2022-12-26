# CGEO

This project is a collection of several Computational Geometry Algorithms and Applications.

The algorithms are implemented in C++ and are wrapped with PyBind11 to use in Python.

The reason for the project is educational, I am challenginע my self with implementing the algorithms so I can understand the theoretic material better.

This is an on-going project and has new features every now and then.

# How To Run

For some running examples you can checkout the [examples](https://github.com/tomsabala/CGEO/tree/main/examples) directory which has some cool examples for each class and algorithm. And you can also run each one of it by yourself.

I suggest reading the relevant examples before trying to use the functionality by yourself.

# Some Nice Examples
You can have a look for an ouput example on convex hull algorithm using [Graham Convex Hull Algorithm](https://en.wikipedia.org/wiki/Graham_scan) :
![Convex Hull 1](examples/PlotImages/convex_hull.png =100x100)
![Convex Hull 2](examples/PlotImages/Convex_Hull002.png =100x100)

The pink layer is the initial polygon form, and the green layer is the convex hull of the follow polygon.

Also, a nice usefull y-monotonic decomposition of a polygon :
![Decomposition](examples/PlotImages/y_decomposition.png =100x100)
