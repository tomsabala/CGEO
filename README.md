<p align="center">
<img src=examples/PlotImages/Logo.png width=350 height=250/>
<p/>
<p align="center">
<img src="https://img.shields.io/badge/License-GNU%203.0-green.svg" align="left">
   <img src="https://img.shields.io/badge/-c++-black?logo=c%2B%2B&style=social">
   <img src="https://img.shields.io/static/v1?label=Computational&message=Geometry&color=green">
   <img src="https://img.shields.io/static/v1?label=Made%20With&message=Python&color=blue">
   <img src="https://img.shields.io/badge/Maintained%3F-yes-green.svg" align="right">
<p/>

# CGEO

<p>This project is a collection of several algorithms and applications of computational geometry.

It is built for quick and easy use of well-known performance-oriented algorithms and important data structures in the field of computational geometry in any Python program.

This is an ongoing project, some features are done and ready, and some are under construction.</p>


## Features
<p>You can find the followong algorithms available:

* [Convex Hull](https://github.com/tomsabala/CGEO/blob/main/2D/Algorithms_2D/ConvexHull2D.cpp)
    * [Gift-Wrapping](https://en.wikipedia.org/wiki/Gift_wrapping_algorithm) Convex Hull by Jarvis march
    * [Grahm-Scan](https://en.wikipedia.org/wiki/Graham_scan) Convex Hull by Ronald Graham
    * Devide & Conquer Convex Hull
* [Segmentation Intersection](https://github.com/tomsabala/CGEO/blob/main/2D/Algorithms_2D/SegmentIntersection2D.cpp)
* [Polygon Triangulation](https://github.com/tomsabala/CGEO/blob/main/2D/Algorithms_2D/Triangulation2D.cpp)
* Shapes
    * 2D Basic Shapes
        * [Point](https://github.com/tomsabala/CGEO/blob/main/2D/Shapes_2D/Point2d.cpp)
        * [Line](https://github.com/tomsabala/CGEO/blob/main/2D/Shapes_2D/Line2d.cpp)
        * [Segment](https://github.com/tomsabala/CGEO/blob/main/2D/Shapes_2D/Segment2d.cpp)
        * [Polygon](https://github.com/tomsabala/CGEO/blob/main/2D/Shapes_2D/Polygon.cpp)
* [Balanced Binary Segment Tree](https://github.com/tomsabala/CGEO/blob/main/DataStructures/BBST.cpp)
* [Smallest Enclosing Disc](https://github.com/tomsabala/CGEO/blob/main/2D/Algorithms_2D/SmallestEnclosingDisk.cpp)<p/>

All the algorithms are implemented using c++. 
But a user can use this source code as a C++ extension for a Python program.

The source code is wrapperd with [pybind11](https://pybind11.readthedocs.io/en/stable/), 
and you can find multiple code-examples of python programs with the wrapped package via the following [link](https://github.com/tomsabala/CGEO/tree/main/examples/py_test).


## How To Run
For some running examples you can checkout the [examples](CGEO/examples) directory which has some cool examples for each class and algorithm. And you can also run each one of it by yourself.

I suggest reading the relevant examples before trying to use the functionality by yourself.

You can use this project in one of the following options: <br />

----- 

As a submodule within your repository with the following steps:
1) Link the repository to your own repo with `git submodule add https://github.com/tomsabala/CGEO`.
2) Enter the `CGEO` directory.<br />
<t/>2.1) Update the pybind11 extension with `git submodule update --init`. <br/>
<t/>2.2) Build the package with `./run.sh`. <br />

-----

Clone this repo, to your local machine:
1) Clone repo: `git clone git@github.com:tomsabala/CGEO.git`.
2) Enter the `CGEO` directory.<br />
<t/>2.1) Update the pybind11 extension with `git submodule update --init`. <br />
<t/>2.2) Build the package with `./run.sh`.


You can import the library in any `*.py` file with `from CGEO.build import libGeo_2D`.
In order to run your `file.py` program: 
1) Set the path for user defined modules with `export PYTHONPATH=.`.
2) Execute program `python file.py`.

::notice that the `run.sh` shell script includes some linux os commands. If you are under windows OS, build the library using the suitable commands.

After scanning dependencies and build are finish, you can use it as an extension in your own python environment.


## Some Nice Examples
<details>
      <summary>Convex-Hull</summary>
      <p><img src=examples/PlotImages/convex_hull.png width=250 height=250/> <img src=examples/PlotImages/Convex_Hull002.png width=250 height=250 /></p>
   
   * The pink layer is the initial polygon form, and the green layer is the convex hull of the follow polygon.
     
</details>

<details>
      <summary>Segement Intersection</summary>
      <p><img src=examples/PlotImages/SegmentIntersection.png width=250 height=250/></p>
   
   * The input is given as a list of segments, and the algorithms is coloring all segments intersections with blue.
     
</details>

<details>
      <summary>Y-Monotone Polygons Decomposition</summary>
      <p><img src=examples/PlotImages/y_decomposition.png width=250 height=250 /></p>  
         
   * The pink layer is the initial polygon form, and the green layer is the convex hull of the follow polygon.
   * A [reference](https://en.wikipedia.org/wiki/Monotone_polygon) for y-monotone polygons definition.
   
</details>

<details>
      <summary>Basic Polygon Triangulation</summary>
      <p><img src=https://github.com/tomsabala/CGEO/blob/main/examples/PlotImages/Ppolygon_Triangulating.jpeg width=250 height=250 /></p>     
</details>

<details>
      <summary>Smallest Enclosing Disc</summary>
      <p><img src=https://github.com/tomsabala/CGEO/blob/main/examples/PlotImages/EnclosingDisc.png width=250 height=250 /></p>     
</details>

## Issues
* Segment intersection is currently on and off, a problem with the balanced segement tree is causing the segment to be un-predictable.
