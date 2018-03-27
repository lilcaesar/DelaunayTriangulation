#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>

class Triangle
{
public:
    Triangle();
    Triangle(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3);
    Triangle(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3, int DAGIndex);
    ~Triangle();
    cg3::Point2Dd p1() const;
    cg3::Point2Dd p2() const;
    cg3::Point2Dd p3() const;
    int getSon1() const;
    int getSon2() const;
    int getSon3() const;
    void addSon(int son);
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
    std::vector<int> adjacencies;
    std::vector<int> sons;
};

#endif // TRIANGLE_H
