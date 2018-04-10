#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>

class Triangle
{
public:
    Triangle(int p1, int p2, int p3);
    Triangle(int p1, int p2, int p3, int adj1, int adj2, int adj3);
    Triangle(int p1, int p2, int p3, int DAGIndex);
    Triangle(int p1, int p2, int p3, int DAGIndex, int adj1, int adj2, int adj3);
    int p1() const;
    int p2() const;
    int p3() const;
    int getPointIndex(const int point1, const int point2);
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

    const int p_1;
    const int p_2;
    const int p_3;

    //adj1 is related to p_1-p_2, adj2 to p_2-p_3 and adj3 to p_3-p_1
    std::vector<int> adjacencies;

    std::vector<int> children;
};

#endif // TRIANGLE_H
