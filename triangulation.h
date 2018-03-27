#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <dag.h>

class Triangulation
{
public:
    Triangulation();
    Triangulation(Triangle* triangle, std::vector<Triangle> *trianglesVector);
    ~Triangulation();
    bool clearTriangulation();
    void insertVertex(const cg3::Point2Dd& point);
    std::vector<cg3::Point2Dd*> getTriangleVertices(int triangleIndex);
    void swap(int oldTriangleIndex, Triangle* newTriangle);
    void addTriangle(Triangle* triangle);

protected:
    int nTriangles;
    int nVertices;
    std::vector<cg3::Point2Dd> points;
    std::vector<int> triangles;
    std::vector<Triangle> *DAGtriangles;
};

#endif // TRIANGULATION_H
