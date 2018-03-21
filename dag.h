#ifndef DAG_H
#define DAG_H

#include <triangle.h>

class DAG
{
public:
    DAG();
    DAG(Triangle triangle);
    Triangle& getRootTriangle();
    void addNodes(int triangle,const cg3::Point2Dd& newPoint);
    Triangle& getTriangle(int index);
    int getNtriangles() const;

private:
    int nTriangle;
    std::vector<Triangle> nodes;
};

#endif // DAG_H
