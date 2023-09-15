
#include "Face3d.h"

using namespace Shapes3d;
using namespace std;

Face3d::Face3d()
:   p(make_pair(new Point3d(), 0)), q(make_pair(new Point3d(), 1)), t(make_pair(new Point3d(), 2))
{}

Face3d::Face3d(Point3d P, Point3d Q, Point3d T)
:   p(make_pair(new Point3d(P.getX(), P.getY(), P.getZ()), 0)),
    q(make_pair(new Point3d(Q.getX(), Q.getY(), Q.getZ()), 1)),
    t(make_pair(new Point3d(T.getX(), T.getY(), T.getZ()), 2))
{}

/* getter and setter */
Point3d * Face3d::getByIndex(int i)
{
    if (i<0 || i>2) return nullptr;
    if (p.second == i) return p.first;
    if (q.second == i) return q.first;
    return t.first;
}
void Face3d::setByIndex(int i, Point3d *P)
{
    if (i<0 || i>2) return;
    if (p.second == i) {p.first->copyPoint(P);return;}
    if (q.second == i) {q.first->copyPoint(P); return;}
    t.first->copyPoint(P);
}

void Face3d::swap(std::pair<Point3d *, int> *x, std::pair<Point3d *, int> *y)
{
    int tmp = x->second;
    x->second = y->second;
    y->second = tmp;
}

void Face3d::twist()
{
    if(p.second==0){
        q.second==1 ? swap(&p, &q) : swap(&p, &t);
        return ;
    }
    if(q.second==0) {
        p.second == 1 ? swap(&q, &p) : swap(&q, &t);
        return;
    }
    p.second==1 ? swap(&t, &p) : swap(&t, &q);
}

bool Face3d::isDegenerated()
{
    auto *pq = new Point3d(p.first->getX() - q.first->getX(),
                              p.first->getY() - q.first->getY(),
                              p.first->getZ() - q.first->getZ());
    auto *pt = new Point3d(p.first->getX() - t.first->getX(),
                              p.first->getY() - t.first->getY(),
                              p.first->getZ() - t.first->getZ());
    auto *crossProd = pq->crossProd(pt);
    delete pq;
    delete pt;

    return abs(crossProd->getX()) <= eps && abs(crossProd->getY()) <= eps && abs(crossProd->getZ()) <= eps;
}

int Face3d::areaSign(Point3d *P)
{return 0;}