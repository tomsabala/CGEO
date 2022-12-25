//
// Created by tomsabala on 12/25/22.
//

#include <iostream>
#include "Triangulation2D.h"

std::vector<Triangle2d *>
        Triangulation2D::triangulate(Shapes2D::Polygon poly)
        {
    std::vector<Triangle2d*> res;
    if (poly.getSize() <= 3)
    {
        Triangle2d *tri = new Triangle2d(*poly.getByIndex(0), *poly.getByIndex(1), *poly.getByIndex(2));
        res.push_back(tri);
        return res;
    }
    int v;
    int u;
    for(int i=0; i<poly.getSize(); i++)
    {
        u = getDiagonal(poly, i);
        if(u != -1){
            v = i;
            break;
        }
    }

    std::pair<Shapes2D::Polygon, Shapes2D::Polygon> sub_polygons = constructPoly(poly, std::make_pair(v, u));
    std::vector<Triangle2d *> tri_poly1 = triangulate(sub_polygons.first);
    std::vector<Triangle2d *> tri_poly2 = triangulate(sub_polygons.second);

    res.insert(res.end(), tri_poly1.begin(), tri_poly1.end());
    res.insert(res.end(), tri_poly2.begin(), tri_poly2.end());

//    std::cout<<"pol1 is decomposed to : \n";
//    for (Triangle2d *tri : tri_poly1)
//    {
//        for (Shapes2D::Point2d p : tri->vertex)
//        {
//            std::cout<<p.toStr()<<'\n';
//        }
//    }
//
//    std::cout<<"pol2 is decomposed to : \n";
//    for (Triangle2d *tri : tri_poly2)
//    {
//        for (Shapes2D::Point2d p : tri->vertex)
//        {
//            std::cout<<p.toStr()<<'\n';
//        }
//    }


    return res;
}

/**
 * this function is responsible for finding a vertex in poly
 * which has two adjacent vertices with y-value lower then the vertex y-value
 * @param poly simple polygon
 * @return vector<int> (of length 0 if not found)
 */
std::vector<int>
Triangulation2D::downInnerCusp(Shapes2D::Polygon poly)
{
    int n = poly.getSize();
    std::vector<int> res;

    for (int i=0; i<n; i++)
    {
        int pred = i == 0 ? n-1 : i-1;
        int succ = i == n-1 ? 0 : i+1;

        if (poly.getByIndex(pred)->getY() < poly.getByIndex(i)->getY() && poly.getByIndex(succ)->getY() < poly.getByIndex(i)->getY())
            res.push_back(i);
    }

    return res;
}

/**
 * this function is responsible for finding a vertex in poly
 * which has two adjacent vertices with y-value bigger then the vertex y-value
 * @param poly simple polygon
 * @return vector<int> (of length 0 if not found)
 */
std::vector<int>
Triangulation2D::upperInnerCusp(Shapes2D::Polygon poly)
{
    int n = poly.getSize();
    std::vector<int> res;

    for (int i=0; i<n; i++)
    {
        int pred = i == 0 ? n-1 : i-1;
        int succ = i == n-1 ? 0 : i+1;

        if (poly.getByIndex(pred)->getY() > poly.getByIndex(i)->getY() && poly.getByIndex(succ)->getY() > poly.getByIndex(i)->getY())
            res.push_back(i);
    }

    return res;
}

std::pair<Shapes2D::Polygon, Shapes2D::Polygon>
Triangulation2D::constructPoly(Shapes2D::Polygon poly, std::pair<int, int> vertex_ind) {
    Shapes2D::Polygon *poly1, *poly2;
    std::vector<Shapes2D::Point2d> poly1_points, poly2_points;

    for(int i=vertex_ind.first; i!=vertex_ind.second;  i = (i + 1) % poly.getSize())
    {
        poly1_points.push_back(*poly.getByIndex(i));
    }
    poly1_points.push_back(*poly.getByIndex(vertex_ind.second));

    for(int i=vertex_ind.second; i!=vertex_ind.first;  i = (i + 1) % poly.getSize())
    {
        poly2_points.push_back(*poly.getByIndex(i));
    }
    poly2_points.push_back(*poly.getByIndex(vertex_ind.first));

    poly1 = new Shapes2D::Polygon(poly1_points);
    poly2 = new Shapes2D::Polygon(poly2_points);

    return std::make_pair(*poly1, *poly2);

}

int Triangulation2D::getDiagonal(Shapes2D::Polygon poly, int v) {

    for (int i=0; i<poly.getSize(); i++)
    {
        int val = goodDiagonal(poly, v, i);
        if (val)
            return i;
    }

    return -1;
}


int Triangulation2D::goodDiagonal(Shapes2D::Polygon poly, int v, int u)
{
    if (u == v)
        return 0;
    if ((v + 1) % poly.getSize() == u || (u + 1) % poly.getSize() == v)
        return 0;

    std::vector<Shapes2D::Segment2d> edges = poly.getEdges();
    Shapes2D::Segment2d *seg = new Shapes2D::Segment2d(poly.getByIndex(v), poly.getByIndex(u));
    for (Shapes2D::Segment2d e : edges)
    {
        Shapes2D::Point2d *intersect = e.getIntersect(seg);
        if (intersect == nullptr)
            continue;
        if(!intersect->_eq_(seg->getLower()) && !intersect->_eq_(seg->getLower()))
            return 0;
    }

    Shapes2D::Point2d *midPoint = new Shapes2D::Point2d((seg->getTarget()->getX() + seg->getOrigin()->getX()) / 2, (seg->getTarget()->getY() + seg->getOrigin()->getY()) / 2);
    return poly.isInPoly(midPoint);
}
