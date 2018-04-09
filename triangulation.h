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
    void swap(int oldTriangleIndex, Triangle* newTriangle);
    void addTriangle(Triangle* triangle);
    void getPoints(std::vector<cg3::Point2Dd>* checkerArray);
    void getTriangles(cg3::Array2D<unsigned int>* checkerArray);

protected:
    cg3::Point2Dd bounding1;
    cg3::Point2Dd bounding2;
    cg3::Point2Dd bounding3;
    std::vector<cg3::Point2Dd> points;
    std::vector<int> triangulationTriangles;
    DAG *DAGtriangles;
};

#endif // TRIANGULATION_H
