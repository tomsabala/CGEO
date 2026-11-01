
![](https://github.com/tomsabala/CGEO/raw/main/logo.png)

[![License](https://img.shields.io/badge/License-GNU%203.0-green.svg)](https://img.shields.io/badge/License-GNU%203.0-green.svg)
[![](https://img.shields.io/badge/-c++-black?logo=c%2B%2B&style=social)](https://img.shields.io/badge/-c++-black?logo=c%2B%2B&style=social)
[![Computational](https://img.shields.io/static/v1?label=Computational&message=Geometry&color=green)]()
[![Made with](https://img.shields.io/static/v1?label=Made%20With&message=Python&color=blue)](https://img.shields.io/static/v1?label=Made%20With&message=Python&color=blue)
[![Maintained?](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://img.shields.io/badge/Maintained%3F-yes-green.svg)


# CGEO

<p>This project is a collection of several algorithms and applications of computational geometry.

It is built for quick and easy use of well-known performance-oriented algorithms and important data structures in the field of computational geometry in any Python program.

This is an ongoing project, some features are done and ready, and some are under construction.</p>


## Features
<p>You can find the followong algorithms available:

* [Convex Hull](https://github.com/tomsabala/CGEO/blob/main/src/2D/algorithms_2D/ConvexHull2D.cpp)
    * [Gift-Wrapping](https://en.wikipedia.org/wiki/Gift_wrapping_algorithm) Convex Hull by Jarvis march
    * [Grahm-Scan](https://en.wikipedia.org/wiki/Graham_scan) Convex Hull by Ronald Graham
    * Devide & Conquer Convex Hull
* [Segmentation Intersection](https://github.com/tomsabala/CGEO/blob/main/src/2D/algorithms_2D/SegmentIntersection2D.cpp)
* [Polygon Triangulation](https://github.com/tomsabala/CGEO/blob/main/src/2D/algorithms_2D/Triangulation2D.cpp)
* Shapes
    * 2D Basic Shapes
        * [Point](https://github.com/tomsabala/CGEO/blob/main/src/2D/shapes_2D/Point2d.cpp)
        * [Line](https://github.com/tomsabala/CGEO/blob/main/src/2D/shapes_2D/Line2d.cpp)
        * [Segment](https://github.com/tomsabala/CGEO/blob/main/src/2D/shapes_2D/Segment2d.cpp)
        * [Polygon](https://github.com/tomsabala/CGEO/blob/main/src/2D/shapes_2D/Polygon.cpp)
* [Balanced Binary Segment Tree](https://github.com/tomsabala/CGEO/blob/main/src/data_structures/SegmentBalancedTree.cpp)
* [Smallest Enclosing Disc](https://github.com/tomsabala/CGEO/blob/main/src/2D/algorithms_2D/SmallestEnclosingDisk.cpp)<p/>

All the algorithms are implemented using c++. 
But a user can use this source code as a C++ extension for a Python program.

The source code is wrapperd with [pybind11](https://pybind11.readthedocs.io/en/stable/), 
and you can find multiple code-examples of python programs with the wrapped package via the following [link](https://github.com/tomsabala/CGEO/tree/main/examples).


## Install

    pip install cgeo

Wheels are published for CPython 3.10–3.14 on Linux (x86_64, aarch64), macOS (arm64, x86_64) and
Windows (x86_64). No compiler required.

## Build from source

    git clone git@github.com:tomsabala/CGEO.git
    cd CGEO
    pip install -e ".[test]"
    pytest tests

The C++ core can also be built on its own, which produces the `cgeo_core` static library and the
`_cgeo` extension module:

    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build -j

<!--- 
## Some Nice Examples
<details>
      <summary>Convex-Hull</summary>
      <p>![](https://github.com/tomsabala/CGEO/blob/main/py_src/plot_images/convex_hull.png) ![](https://github.com/tomsabala/CGEO/blob/main/py_src/plot_images/Convex_Hull002.png)</p>
   
   * The pink layer is the initial polygon form, and the green layer is the convex hull of the follow polygon.
     
</details>

<details>
      <summary>Segement Intersection</summary>
      <p>![](https://github.com/tomsabala/CGEO/blob/main/py_src/plot_images/Segment_Intersection.png)</p>
   
   * The input is given as a list of segments, and the algorithms is coloring all segments intersections with blue.
     
</details>

<details>
      <summary>Y-Monotone Polygons Decomposition</summary>
      <p>![](https://github.com/tomsabala/CGEO/blob/main/py_src/plot_images/y_decomposition.png)</p>  
         
   * The pink layer is the initial polygon form, and the green layer is the convex hull of the follow polygon.
   * A [reference](https://en.wikipedia.org/wiki/Monotone_polygon) for y-monotone polygons definition.
   
</details>

<details>
      <summary>Basic Polygon Triangulation</summary>
      <p>![](https://github.com/tomsabala/CGEO/blob/main/py_src/plot_images/Ppolygon_Triangulating.jpeg)</p>     
</details>

<details>
      <summary>Smallest Enclosing Disc</summary>
      <p>![](https://github.com/tomsabala/CGEO/blob/main/py_src/plot_images/EnclosingDisc.png)</p>     
</details>

-- >