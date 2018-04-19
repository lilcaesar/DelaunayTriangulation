#include "dag.h"

DAG::DAG(): nTriangle(0){
}
DAG::DAG(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3): bounding1(p1), bounding2(p2), bounding3(p3), nPoints(3), nTriangle(1){
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    nodes.push_back(DagNode(0,1,2,0,-1,-1,-1));
    nodes[0].setTriangulationIndex(0);
}

/**
 * @brief Add new node.
 * @param newNode
 */
void DAG::addNode(DagNode newNode){
    nodes.push_back(newNode);
    nTriangle++;
}

/**
 * @brief Add new point.
 * @param newPoint
 */
void DAG::addPoint(const cg3::Point2Dd& newPoint){
    points.push_back(newPoint);
    nPoints++;
}

/**
 * @brief Changes a specific adjacency of a triangle.
 * @param triangle
 * @param oldValue
 * @param newValue
 */
void DAG::changeTriangleAdj(int triangle, int oldValue, int newValue){
    nodes[triangle].changeAdj(oldValue, newValue);
}

/**
 * @brief Add a child to a specific triangle.
 * @param triangle
 * @param child
 */
void DAG::addNodeChild(int triangle, int child){
    nodes[triangle].addChild(child);
}

/**
 * @brief Set the triangulation index of a triangle.
 * @param triangle
 * @param index
 */
void DAG::setTriangleTriangulationIndex(int triangle, int index){
    nodes[triangle].setTriangulationIndex(index);
}

/**
 * @brief Clear all the data of the class.
 */
void DAG::clearGraph(){
    nodes.clear();
    points.clear();
}

/**
 * @brief Initialize the data for the root node.
 *
 * The root node is the triangle composed by the given bounding triangle
 * so this method adds the vertices to the points vector and the initialized
 * triangle to the nodes vector.
 */
void DAG::initializeBounding(){
    nTriangle=1;
    nPoints=3;
    points.push_back(bounding1);
    points.push_back(bounding2);
    points.push_back(bounding3);
    nodes.push_back(DagNode(0,1,2,0,-1,-1,-1));
    nodes[0].setTriangulationIndex(0);
}

/**
 * @brief Get Points list.
 * @return Vector of Points.
 */
std::vector<cg3::Point2Dd> DAG::getPoints() const{
    return points;
}

/**
 * @brief Get number of points.
 */
int DAG::getNPoints() const{
    return nPoints;
}
