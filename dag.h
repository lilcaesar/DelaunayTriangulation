#ifndef DAG_H
#define DAG_H

#include <triangle.h>

class DAG
{
public:
    DAG();
    DAG(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3);
    Triangle& getRootTriangle();
    void edgeFlip(int triangle1, int triangle2);
    void addNodes(int triangle,const cg3::Point2Dd& newPoint);
    Triangle& getTriangle(int index);
    cg3::Point2Dd& getPoint(int index);
    int getNtriangles() const;
    std::vector<Triangle>* getVector();
    bool clearGraph();
    std::vector<cg3::Point2Dd> getPoints();
    int getNPoints();

private:
    cg3::Point2Dd bounding1;
    cg3::Point2Dd bounding2;
    cg3::Point2Dd bounding3;
    std::vector<cg3::Point2Dd> points;
    int nPoints;
    int nTriangle;
    std::vector<Triangle> nodes;
};

#endif // DAG_H
