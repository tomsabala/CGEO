#include "2D_bindings.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

double round_to(double value, double precision = 1.0)
{
    return std::round(value / precision) * precision;
}

namespace py = pybind11;

PYBIND11_MODULE(EXTENSION_NAME, h) {
    h.doc() = "2D geometric classes binding to python";

    auto h_shapes = h.def_submodule("libShapes_2D", "This is shapes lib");

    auto h_algorithms = h.def_submodule("libAlgorithms_2D", "This is algorithms lib");

    py::class_<Shapes2D::Point2d>(h_shapes, "Point")
            .def(py::init<>(), "empty constructor")
            .def(py::init<double, double>(), "standard constructor")
            .def_property("x", &Shapes2D::Point2d::getX, &Shapes2D::Point2d::setX)
            .def_property("y", &Shapes2D::Point2d::getY, &Shapes2D::Point2d::setY)
//            .def("copyPoint", &Shapes2D::Point2d::copyPoint, "copy point coordinates",
//            py::arg("point"))
            .def("norm", &Shapes2D::Point2d::norm, "calculate point norm")
            .def("dist", &Shapes2D::Point2d::dist, "calculate distance to another point",
            py::arg("point"))
            .def("subtract", &Shapes2D::Point2d::subtract, "subtract point coordinates from other point")
            .def("adder", &Shapes2D::Point2d::adder, "add coordinates of a given point")
            .def("oriePred", &Shapes2D::Point2d::oriePred, "calculate orientation predicator")
            .def("toStr", &Shapes2D::Point2d::toStr, "return string representation of point")
            .def("__repr__",
                [](const Shapes2D::Point2d& p) {
                std::string r("Point(");
                std::string ret_x = std::to_string(round_to(p.getX(), 0.01));
                ret_x = ret_x.substr(0, ret_x.find('.')+3);
                r += ret_x;
                r += ", ";
                std::string ret_y = std::to_string(round_to(p.getY(), 0.01));
                ret_y = ret_y.substr(0, ret_y.find('.')+3);
                r += ret_y;
                r += ")";
                return r;});
//            .def("__lt__",
//                 [](const Shapes2D::Point2d& p, Shapes2D::Point2d q) {
//                     return p._lt_(q);})
//            .def("__gt__",
//                 [](const Shapes2D::Point2d& p, Shapes2D::Point2d q) {
//                     return p._gt_(q);})
//            .def("__eq__",
//                 [](const Shapes2D::Point2d& p, Shapes2D::Point2d q) {
//                     return p._eq_(&q);});

    py::class_<Shapes2D::Segment2d>(h_shapes, "Segment")
            .def(py::init<>(), "empty constructor")
            .def(py::init<Shapes2D::Point2d*, Shapes2D::Point2d*>(), "standard constructor")
            .def(py::init<Shapes2D::Segment2d*>(), "constructing segment from other segment")
            .def_property("origin", &Shapes2D::Segment2d::getOrigin, &Shapes2D::Segment2d::setOrigin)
            .def_property("target", &Shapes2D::Segment2d::getTarget, &Shapes2D::Segment2d::setTarget)
            .def("getSlope", &Shapes2D::Segment2d::getSlope, "get the slope of the segment")
            .def("getLength", &Shapes2D::Segment2d::getLength, "get the length of the segment")
            .def("getUpper", &Shapes2D::Segment2d::getUpper, "get the upper point of the segment")
            .def("getLower", &Shapes2D::Segment2d::getLower, "get the lower point of the segment")
            .def("adder", &Shapes2D::Segment2d::adder, "shift segment with point threshold",
                 py::arg("point"))
            .def("rotate", &Shapes2D::Segment2d::rotate, "rotate segment direction with given degree",
                 py::arg("degree"))
            .def("__eq__", &Shapes2D::Segment2d::_eq_, "check given segment is equal to current segment",
                 py::arg("segment"))
            .def("copySegment", &Shapes2D::Segment2d::copySegment, "set origin and target w.r.t given segment",
                 py::arg("segment"))
            .def("oriePred", py::overload_cast<Shapes2D::Segment2d*>(&Shapes2D::Segment2d::oriePred, py::const_), "calculate orientation")
            .def("oriePred", py::overload_cast<Shapes2D::Point2d*>(&Shapes2D::Segment2d::oriePred, py::const_), "calculate orientation")
            .def("isParallel", &Shapes2D::Segment2d::isParallel, "check if two segments are parallel",
                 py::arg("segment"))
            .def("isVertical", &Shapes2D::Segment2d::isVertical, "check if two segments are vertical",
                 py::arg("segment"))
            .def("dist", static_cast<double (Shapes2D::Segment2d::*)(Shapes2D::Segment2d*)>(&Shapes2D::Segment2d::dist), "calculate distance to segment if parallel")
            .def("dist", static_cast<double (Shapes2D::Segment2d::*)(Shapes2D::Point2d*)>(&Shapes2D::Segment2d::dist), "calculate distance to point")
            .def("isIntersect", &Shapes2D::Segment2d::isIntersect, "check if two segments intersect",
                 py::arg("segment"))
            .def("__repr__",
                 [](Shapes2D::Segment2d &s) {
                     std::string r("Segment: ");
                     r += s.getOrigin()->toStr();
                     r += " -->  ";
                     r += s.getTarget()->toStr();
                     return r;
                 });

    py::class_<Shapes2D::Polygon>(h_shapes, "Polygon")
            .def(py::init<>(), "empty constructor")
            .def(py::init<std::vector<Shapes2D::Point2d>>())
            .def("getVertices", &Shapes2D::Polygon::getVertices, "get all vertices in polygon")
            .def("insert", py::overload_cast<const Shapes2D::Point2d &>(&Shapes2D::Polygon::insert))
            .def("insert", py::overload_cast<const Shapes2D::Point2d &, int>(&Shapes2D::Polygon::insert))
            .def("getByIndex", &Shapes2D::Polygon::getByIndex, "return Point2d by index",
                 py::arg("i"))
            .def("getLexMin", &Shapes2D::Polygon::getLexMin, "return lowest point w.r.t lexicographic order")
            .def("getLexMin_index", &Shapes2D::Polygon::getLexMin_index, "return lowest point index w.r.t lexicographic order")
            .def("getLexMax", &Shapes2D::Polygon::getLexMax, "return highest point w.r.t lexicographic order")
            .def("getLexMax_index", &Shapes2D::Polygon::getLexMax_index, "return highest point index w.r.t lexicographic order")
            .def("lexOrder", &Shapes2D::Polygon::lexOrder, "return arr of all vertices sorted by lex. order")
            .def("getEdges", &Shapes2D::Polygon::getEdges, "return arr of all edges of the polygon")
            .def("getSize", &Shapes2D::Polygon::getSize, "return number of vertices in polygon")
            .def("isConvex", &Shapes2D::Polygon::isConvex, "check whether polygon is convex")
            .def("isY_Monotone", &Shapes2D::Polygon::isY_Monotone, "check whether polygon is y-monotone")
            .def("isInnerCusp", &Shapes2D::Polygon::isInnerCusp, "check whether given point is an inner cusp")
            .def("decomposeY_Monotone", &Shapes2D::Polygon::decomposeY_Monotone, "decompose the given polygon into y-monotone polygons");

    py::class_<Algorithms2d::ConvexHull>(h_algorithms, "ConvexHullUtils")
            .def(py::init<>())
            .def_static("grahamConvexHull", &Algorithms2d::ConvexHull::grahamConvexHull, "graham convex hull algorithm")
            .def("giftWrapConvexHull", &Algorithms2d::ConvexHull::giftWrapConvexHull, "gift wrapping convex hull algorithm");

    py::class_<Algorithms2d::SegmentIntersection2d>(h_algorithms, "SegmentIntersect")
            .def(py::init<>())
            .def("intersection", &Algorithms2d::SegmentIntersection2d::solve, "solve segment intersection");

    py::class_<Node>(h_algorithms, "Node")
            .def(py::init<Shapes2D::Segment2d *>());

    py::class_<SegmentBalancedTree>(h_algorithms, "SegmentTree")
            .def("insert", &SegmentBalancedTree::insert, "insert a new segment to the tree")
            .def("searchSegment", &SegmentBalancedTree::search, "search a segment inside the tree and return its pointer")
            .def("searchPoint", &SegmentBalancedTree::search_p, "search for a segment that contains a given point inside the tree")
            .def("maxx", &SegmentBalancedTree::maxx, "return the maximum segment in the tree")
            .def("minn", &SegmentBalancedTree::minn, "return the minimum segment in the tree")
            .def("InOrder", &SegmentBalancedTree::walkInOrder, "print the tree segment in an in-order walk")
            .def("remove", &SegmentBalancedTree::remove, "remove a segment from the tree")
            .def("getPred", &SegmentBalancedTree::getPred, "get predecessor of node")
            .def("getSucc", &SegmentBalancedTree::getSucc, "get successor of node");

    py::class_<Shapes2D::Triangle2d>(h_shapes, "Triangle")
            .def(py::init<Shapes2D::Point2d, Shapes2D::Point2d, Shapes2D::Point2d>())
            .def_property("a", &Shapes2D::Triangle2d::getA, &Shapes2D::Triangle2d::setA)
            .def_property("b", &Shapes2D::Triangle2d::getB, &Shapes2D::Triangle2d::setB)
            .def_property("c", &Shapes2D::Triangle2d::getC, &Shapes2D::Triangle2d::setC)
            .def("area", &Shapes2D::Triangle2d::area, "get area of triangle")
            .def("getVertex", &Shapes2D::Triangle2d::getVertices, "get vertex list");

    py::class_<Algorithms2d::Triangulation2D>(h_algorithms, "TriangulationUtils")
            .def(py::init<>())
            .def("triangulate", &Algorithms2d::Triangulation2D::triangulate, "triangulate polygon");

    py::class_<Shapes2D::Circle2d>(h_shapes, "Circle")
            .def(py::init<>())
            .def(py::init<double>())
            .def(py::init<double, Shapes2D::Point2d *>())
            .def(py::init<Shapes2D::Point2d , Shapes2D::Point2d , Shapes2D::Point2d >())
            .def_property("r", &Shapes2D::Circle2d::getRadius, &Shapes2D::Circle2d::setRadius)
            .def_property("center", &Shapes2D::Circle2d::getCenter, &Shapes2D::Circle2d::setCenter)
            .def("circleIntersect", &Shapes2D::Circle2d::circleIntersect, "check if the circle intersect with a given circle")
            .def("lineIntersect", &Shapes2D::Circle2d::lineIntersect, "check if the circle intersect with a given line")
            .def("segIntersect", &Shapes2D::Circle2d::segIntersect, "check if the circle intersect with a given segment")
            .def("polyIntersect", &Shapes2D::Circle2d::polyIntersect, "check if the circle intersect with a given polygon")
            .def("pointContains", &Shapes2D::Circle2d::pointContains, "check if a point is contained in the circle")
            .def("segContains", &Shapes2D::Circle2d::segmentContains, "check if a segment is contained in the circle")
            .def("circleContains", &Shapes2D::Circle2d::circleContains, "check if a circle is contained in the circle")
            .def("polyContains", &Shapes2D::Circle2d::polyContains, "check if a polygon is contained in the circle");

    py::class_<Algorithms2d::SmallestEnclosingDisk>(h_algorithms, "EnclosingDistUtils")
            .def(py::init<>())
            .def("findDisc", &Algorithms2d::SmallestEnclosingDisk::findDisc, "find enclosing disc");
}