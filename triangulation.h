#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <dag.h>

class Triangulation
{
public:
    Triangulation();
    Triangulation(Triangle* triangle, DAG *graph);
    void clearTriangulation();
    void insertVertex(const cg3::Point2Dd& point);
    std::vector<cg3::Point2Dd*> getTriangleVertices(int triangleIndex);
    void swap(int oldTriangleIndex, Triangle* newTriangle);
    void addTriangle(Triangle* triangle);

protected:
    cg3::Point2Dd bounding1;
    cg3::Point2Dd bounding2;
    cg3::Point2Dd bounding3;
    std::vector<cg3::Point2Dd> points;
    std::vector<int> triangulationTriangles;
    DAG *DAGtriangles;
};

#endif // TRIANGULATION_H
