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
    void insertVertex(const cg3::Point2Dd& point);
    std::vector<cg3::Point2Dd*> getTriangleVertices(int triangleIndex);
    void swap(int oldTriangleIndex, int newTriangle);
    void addTriangle(const DagNode &triangle);
    std::vector<int> getTriangles() const;
    void computeBisector(const cg3::Point2Dd &p1, const cg3::Point2Dd &p2, double &a, double &b, double &c) const;
    cg3::Point2Dd computeCircumcenter(int Triangle) const;
    void computeVoronoiPoints();
    void clearVoronoi();

protected:
    std::vector<int> triangulationTriangles;
    std::vector<cg3::Point2Dd> voronoiEdges;
    DAG *DAGtriangles;
};

#endif // TRIANGULATION_H
