#include "triangle.h"
#include <algorithm>

/**
 * @brief Triangle constructor.
 * @param p1: index of the first vertex in the points vector.
 * @param p2: index of the second vertex in the points vector.
 * @param p3: index of the third vertex in the points vector.
 * @param DAGIndex: index of the triangle in the DAG.
 * @param adj1: index of the first adjacent triangle.
 * @param adj2: index of the second adjacent triangle.
 * @param adj3: index of the third adjacent triangle.
 */
Triangle::Triangle(int p1, int p2, int p3, int DAGIndex, int adj1, int adj2, int adj3) : triangleDAGIndex(DAGIndex), p_1(p1), p_2(p2), p_3(p3){
    adjacencies.push_back(adj1);
    adjacencies.push_back(adj2);
    adjacencies.push_back(adj3);
}

/**
 * @brief Get opposite point index given the vertices of one edge.
 * @param point1: first vertex of the edge.
 * @param point2: second vertex of the edge.
 * @return index of the opposite edge.
 */
int Triangle::getOppositePointIndex(const int point1, const int point2) const{
    if((p_1==point1 && p_2==point2)||(p_2==point1 && p_1==point2))
        return 3;
    if((p_2==point1 && p_3==point2)||(p_3==point1 && p_2==point2))
        return 1;
    if((p_3==point1 && p_1==point2)||(p_1==point1 && p_3==point2))
        return 2;
    return -1;
}

/**
 * @brief Add a new child to the triangle
 * @param Index in the DAG of the child
 */
void Triangle::addChild(int child){
    children.push_back(child);
}

/**
 * @brief Change one adjacency of the triangle.
 * @param oldValue
 * @param newValue
 *
 * Search and substitute the old value with the new value.
 */
void Triangle::changeAdj(int oldValue, int newValue){
    std::replace(adjacencies.begin(), adjacencies.end(), oldValue, newValue);
}

/**
 * @brief Get the DAG index of the triangle.
 */
int Triangle::getTriangleDAGIndex() const{
    return triangleDAGIndex;
}

/**
 * @brief Get the triangulation index of the triangle.
 */
int Triangle::getTriangleTriangulationIndex() const{
    return triangleTriangulationIndex;
}

/**
 * @brief Return true if the triangle has no children.
 */
bool Triangle::isLeaf() const{
    return children.empty();
}

/**
 * @brief Set the index of the triangulation
 */
void Triangle::setTriangulationIndex(int index){
    triangleTriangulationIndex = index;
}
