
#include <iostream>
#include "Triangulation2D.h"

using namespace Algorithms2d;

std::vector<Shapes2D::Triangle2d *>
Triangulation2D::triangulate(Shapes2D::Polygon *poly)
{
    /* vector output */
    std::vector<Shapes2D::Triangle2d *> res;

    /* create decomposition of poly into y-monotone polygons */
    std::vector<Shapes2D::Polygon *> poly_decompose = Shapes2D::Polygon::decomposeY_Monotone(poly);

    /* for each sub-poly, compute the responsive triangulation */
    for (Shapes2D::Polygon *sub_poly : poly_decompose)
    {
        std::vector<Shapes2D::Triangle2d *> sub_res = Algorithms2d::Triangulation2D::triangulate_YMonotone(sub_poly);
        res.insert(res.end(), sub_res.begin(), sub_res.end());
    }

    return res;
}

/**
 * this function triangulate the polygon poly,
 * while assuming that poly is a y-monotone polygon
 * @param poly a y-monotone polygon
 * @return vector of Triangles in poly
 */
std::vector<Shapes2D::Triangle2d *>
Triangulation2D::triangulate_YMonotone(Shapes2D::Polygon *poly)
{
    /* vector output */
    std::vector<Shapes2D::Triangle2d *> res;

    /* poly is basically a triangle */
    if (poly->getSize() == 3)
    {
        auto *tri = new Shapes2D::Triangle2d(*poly->getByIndex(0), *poly->getByIndex(1), *poly->getByIndex(2));
        res.push_back(tri);
        return res;
    }

    /* sorted stack of vertex, from y=inf to y=-inf */
    std::stack<std::pair<Shapes2D::Point2d *, int>> vertex_Stack;
    std::vector<std::pair<Shapes2D::Point2d *, int>> sorted_vertex = Algorithms2d::Triangulation2D::sortByY(poly);

    /* init stack */
    int i=2;
    vertex_Stack.push(sorted_vertex[0]);
    vertex_Stack.push(sorted_vertex[1]);

    /* append vertices and compute the triangles respectively */
    while(i < sorted_vertex.size())
    {
        std::pair<Shapes2D::Point2d *, int> p = sorted_vertex[i];
        Algorithms2d::Triangulation2D::popFromStack(&res, &vertex_Stack, p); /* compute the triangle and dynamically pop vertices from stack */

        i++;
    }

    return res;
}

/**
 * this function is responsible for dynamically piping vertices from the stack,
 * as long as they can create a new triangle with another vertex p
 * @param res every valid triangle is been inserted into res
 * @param vertex_Stack dynamic stack
 * @param p the pivot vertex
 */
void
Triangulation2D::popFromStack(std::vector<Shapes2D::Triangle2d *> * res, std::stack<std::pair<Shapes2D::Point2d *, int>> *vertex_Stack, std::pair<Shapes2D::Point2d *, int> p)
{
    if (p.second == vertex_Stack->top().second)
    {
        /* p is on the same rail as every other vertex in the stack */
        while(vertex_Stack->size() >= 2)
        {
            std::pair<Shapes2D::Point2d *, int> first_pair = vertex_Stack->top();
            vertex_Stack->pop();
            std::pair<Shapes2D::Point2d *, int> second_pair = vertex_Stack->top();
            vertex_Stack->pop();

            if (p.second)
            {
                if (p.first->oriePred(first_pair.first, second_pair.first) > 0)
                {
                    res->push_back(new Shapes2D::Triangle2d(*p.first, *first_pair.first, *second_pair.first));
                    vertex_Stack->push(second_pair);
                }
                else
                {
                    vertex_Stack->push(second_pair);
                    vertex_Stack->push(first_pair);
                    break;
                }
            }

            else
            {
                if (p.first->oriePred(first_pair.first, second_pair.first) < 0)
                {
                    res->push_back(new Shapes2D::Triangle2d(*p.first, *first_pair.first, *second_pair.first));
                    vertex_Stack->push(second_pair);
                }
                else
                {
                    vertex_Stack->push(second_pair);
                    vertex_Stack->push(first_pair);
                    break;
                }
            }
        }
    }
    else
    { /* p is on the opposite rail from all other vertices in the stack */

        std::pair<Shapes2D::Point2d *, int> last_p = vertex_Stack->top();
        while(vertex_Stack->size() >= 2)
        {
            std::pair<Shapes2D::Point2d *, int> first_pair = vertex_Stack->top();
            vertex_Stack->pop();
            std::pair<Shapes2D::Point2d *, int> second_pair = vertex_Stack->top();
            vertex_Stack->pop();

            if (p.second)
            {
                if (p.first->oriePred(first_pair.first, second_pair.first) < 0)
                {
                    res->push_back(new Shapes2D::Triangle2d(*p.first, *first_pair.first, *second_pair.first));
                    if(vertex_Stack->empty())
                        break;
                    vertex_Stack->push(second_pair);
                }
                else
                {
                    vertex_Stack->push(second_pair);
                    vertex_Stack->push(first_pair);
                    break;
                }
            }
            else
            {
                if (p.first->oriePred(first_pair.first, second_pair.first) > 0)
                {
                    res->push_back(new Shapes2D::Triangle2d(*p.first, *first_pair.first, *second_pair.first));
                    if(vertex_Stack->empty())
                        break;
                    vertex_Stack->push(second_pair);
                }
                else
                {
                    vertex_Stack->push(second_pair);
                    vertex_Stack->push(first_pair);
                    break;
                }
            }
        }
        vertex_Stack->push(last_p);
    }

    vertex_Stack->push(p);
}

/**
 * get a sorted vector of all points in the polygon by their y coordinate
 * @param poly assuming poly is y-monotone
 * @return sorted points vector
 */
std::vector<std::pair<Shapes2D::Point2d *, int>>
Triangulation2D::sortByY(Shapes2D::Polygon *poly)
{
    std::pair<std::vector<std::pair<Shapes2D::Point2d *, int>>, std::vector<std::pair<Shapes2D::Point2d *, int>>> rails = Algorithms2d::Triangulation2D::findLeftRightRails(poly);

    std::vector<std::pair<Shapes2D::Point2d *, int>> res;

    int leftIndex=0, rightIndex=0;
    while (leftIndex<rails.first.size() && rightIndex<rails.second.size())
    {
        if (rails.first[leftIndex].first->getY() > rails.second[rightIndex].first->getY())
            res.push_back(rails.first[leftIndex ++]);
        else
            res.push_back(rails.second[rightIndex ++]);
    }

    while (leftIndex<rails.first.size())
        res.push_back(rails.first[leftIndex ++]);

    while (rightIndex<rails.second.size())
        res.push_back(rails.second[rightIndex ++]);

    return res;
}

/**
 * get a two rails from up to bottom points of poly
 * @param poly assuming poly is a y-monotone polygon
 * @return two sorted vectors
 */
std::pair<std::vector<std::pair<Shapes2D::Point2d *, int>>, std::vector<std::pair<Shapes2D::Point2d *, int>>>
Triangulation2D::findLeftRightRails(Shapes2D::Polygon *poly)
{
    int n = poly->getSize();
    /* get upper and lower polygons points */
    Shapes2D::Point2d *upperPoint=poly->getByIndex(0), *lowerPoint=poly->getByIndex(0);
    int upperIndex=0, lowerIndex=0;
    for (int i=0; i<n; ++i)
    {
        Shapes2D::Point2d *curr_point = poly->getByIndex(i);
        if (upperPoint->getY() < curr_point->getY())
        {
            upperPoint = curr_point;
            upperIndex = i;
        }
        if (lowerPoint->getY() > curr_point->getY())
        {
            lowerPoint = curr_point;
            lowerIndex = i;
        }
    }

    /* construct the left and right rails from top to bottom */
    std::vector<std::pair<Shapes2D::Point2d *, int>>leftRail;
    std::vector<std::pair<Shapes2D::Point2d *, int>>rightRail;

    for (int i=upperIndex; i!=lowerIndex; i=(i+1)%n)
    {
        rightRail.emplace_back(poly->getByIndex(i), 1);
    }
    for (int i=upperIndex==0?n-1:upperIndex-1; i!=lowerIndex; i=i==0?n-1:i-1)
    {
        leftRail.emplace_back(poly->getByIndex(i), 0);
    }
    leftRail.emplace_back(poly->getByIndex(lowerIndex), 0);

    return std::make_pair(leftRail, rightRail);
}
