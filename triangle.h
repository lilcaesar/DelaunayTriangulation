#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>

class Triangle
{
public:
    Triangle();
    Triangle(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3);
    Triangle(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3, int adj1, int adj2, int adj3);
    Triangle(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3, int DAGIndex);
    Triangle(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3, int DAGIndex, int adj1, int adj2, int adj3);
    cg3::Point2Dd p1() const;
    cg3::Point2Dd p2() const;
    cg3::Point2Dd p3() const;
    int getChild1() const;
    int getChild2() const;
    int getChild3() const;
    void addChild(int child);
    int getAdj1() const;
    int getAdj2() const;
    int getAdj3() const;
    void addAdj(int child);
    void setAdj(int oldValue, int newValue);
    int getTriangleDAGIndex() const;
    int getTriangleTriangulationIndex() const;
    bool isLeaf() const;
    void setDAGIndex(int index);
    void setTriangulationIndex(int index);

private:
    int triangleDAGIndex;
    int triangleTriangulationIndex;
    const cg3::Point2Dd p_1;
    const cg3::Point2Dd p_2;
    const cg3::Point2Dd p_3;
    std::vector<int> adjacencies;   //adj1 is related to p_1-p_2, adj2 to p_2-p_3 and adj3 to p_3-p_1
    std::vector<int> children;
};

#endif // TRIANGLE_H
