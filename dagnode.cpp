#include "dagnode.h"

/**
 * @brief DagNode constructor.
 * @param p1: index of the first vertex in the points vector.
 * @param p2: index of the second vertex in the points vector.
 * @param p3: index of the third vertex in the points vector.
 * @param DAGIndex: index of the triangle in the DAG.
 * @param adj1: index of the first adjacent triangle.
 * @param adj2: index of the second adjacent triangle.
 * @param adj3: index of the third adjacent triangle.
 */
DagNode::DagNode(int p1, int p2, int p3, int DAGIndex, int adj1, int adj2, int adj3): Triangle(p1, p2, p3), triangleDAGIndex(DAGIndex){
    adjacencies.push_back(adj1);
    adjacencies.push_back(adj2);
    adjacencies.push_back(adj3);
}


/**
 * @brief Add a new child to the node.
 * @param Index in the DAG of the child.
 */
void DagNode::addChild(int child){
    children.push_back(child);
}

/**
 * @brief Change one adjacency of the triangle.
 * @param oldValue
 * @param newValue
 *
 * Search and substitute the old value with the new value.
 */
void DagNode::changeAdj(int oldValue, int newValue){
    std::replace(adjacencies.begin(), adjacencies.end(), oldValue, newValue);
}

/**
 * @brief Get the DAG index of the node.
 */
int DagNode::getTriangleDAGIndex() const{
    return triangleDAGIndex;
}

/**
 * @brief Get the triangulation index of the node.
 */
int DagNode::getTriangleTriangulationIndex() const{
    return triangleTriangulationIndex;
}

/**
 * @brief Return true if the node has no children.
 */
bool DagNode::isLeaf() const{
    return children.empty();
}

/**
 * @brief Set the index of the triangulation.
 */
void DagNode::setTriangulationIndex(int index){
    triangleTriangulationIndex = index;
}
