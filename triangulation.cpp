#include "triangulation.h"

/**
 * @brief Triangulation constructor.
 * @param graph: The pointer to the associated DAG.
 */
Triangulation::Triangulation(DAG *graph): DAGtriangles(graph){
    triangulationTriangles.push_back(0);
}

/**
 * @brief Clear the triangulation vector.
 */
void Triangulation::clearTriangulation(){
    triangulationTriangles.clear();
}

/**
 * @brief Initialize the triangulation vector with the index of the bounding triangle.
 */
void Triangulation::initializeBounding(){
    triangulationTriangles.push_back(0);
}

/**
 * @brief Swap the value of a index of the triangulation vector.
 * @param oldTriangleIndex.
 * @param newTriangle.
 */
void Triangulation::swap(int oldTriangleIndex, int newTriangle){
    triangulationTriangles[oldTriangleIndex]= newTriangle;
    DAGtriangles->setTriangleTriangulationIndex(newTriangle, oldTriangleIndex);
}

/**
 * @brief Add a triangle to the triangulation
 * @param triangle: A Triangle object.
 *
 * Adds a new triangle to the triangulation and sets the triangulation index of the triangle.
 */
void Triangulation::addTriangle(const DagNode &triangle){
    DAGtriangles->setTriangleTriangulationIndex(triangle.getTriangleDAGIndex(), triangulationTriangles.size());
    triangulationTriangles.push_back(triangle.getTriangleDAGIndex());
}

/**
 * @brief Return the vector of triangulation indices
 */
std::vector<int> Triangulation::getTriangles() const{
    return triangulationTriangles;
}

/**
 * @brief Add a Point in the voronoiEdges vector.
 * @param point: the new point.
 */
void Triangulation::addPointInVoronoiEdges(cg3::Point2Dd point){
    voronoiEdges.push_back(point);
}

/**
 * @brief Clear the Voronoi graph.
 */
void Triangulation::clearVoronoi(){
    voronoiEdges.clear();
}
