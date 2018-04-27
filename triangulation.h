#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <dag.h>
#include <cg3/data_structures/arrays/array2d.h>

class Triangulation
{
public:
    Triangulation(DAG *graph);
    void clearTriangulation();
    void initializeBounding();
    void swap(int oldTriangleIndex, int newTriangle);
    void addTriangle(const DagNode &triangle);
    std::vector<int> getTriangles() const;
    void addPointInVoronoiEdges(cg3::Point2Dd point);
    void clearVoronoi();

protected:
    std::vector<int> triangulationTriangles;
    std::vector<cg3::Point2Dd> voronoiEdges;
    DAG *DAGtriangles;
};

#endif // TRIANGULATION_H
