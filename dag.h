#ifndef DAG_H
#define DAG_H

#include <triangle.h>

class DAG
{
public:
    DAG();
    Triangle getRootTriangle() const;
    void addNodes(int triangle,const cg3::Point2Dd& newPoint);

private:
    int nTriangle;
    std::vector<Triangle> nodes;
};

#endif // DAG_H
