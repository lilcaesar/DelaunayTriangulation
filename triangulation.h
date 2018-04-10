#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <dag.h>
#include <cg3/data_structures/arrays/array2d.h>

class Triangulation
{
public:
    Triangulation(Triangle* triangle, DAG *graph);
    void clearTriangulation();
    void insertVertex(const cg3::Point2Dd& point);
    std::vector<cg3::Point2Dd*> getTriangleVertices(int triangleIndex);
    void swap(int oldTriangleIndex, int newTriangle);
    void addTriangle(int triangle);
    std::vector<int> getTriangles();

protected:
    std::vector<int> triangulationTriangles;
    DAG *DAGtriangles;
};

#endif // TRIANGULATION_H
