#include "triangle.h"
#include <algorithm>

/**
 * @brief Triangle constructor
 * @param p1: index of the first vertex in the points vector
 * @param p2: index of the second vertex in the points vector
 * @param p3: index of the third vertex in the points vector
 * @param DAGIndex: index of the triangle
 * @param adj1
 * @param adj2
 * @param adj3
 */
Triangle::Triangle(int p1, int p2, int p3, int DAGIndex, int adj1, int adj2, int adj3) : triangleDAGIndex(DAGIndex), p_1(p1), p_2(p2), p_3(p3){
    adjacencies.push_back(adj1);
    adjacencies.push_back(adj2);
    adjacencies.push_back(adj3);
}

int Triangle::getPointIndex(const int point1, const int point2) const{
    if((p_1==point1 && p_2==point2)||(p_2==point1 && p_1==point2))
        return 3;
    if((p_2==point1 && p_3==point2)||(p_3==point1 && p_2==point2))
        return 1;
    if((p_3==point1 && p_1==point2)||(p_1==point1 && p_3==point2))
        return 2;
    return -1;
}

void Triangle::addChild(int child){
    children.push_back(child);
}

void Triangle::addAdj(int child){
    adjacencies.push_back(child);
}

void Triangle::setAdj(int oldValue, int newValue){
    std::replace(adjacencies.begin(), adjacencies.end(), oldValue, newValue);
}

int Triangle::getTriangleDAGIndex() const{
    return triangleDAGIndex;
}

int Triangle::getTriangleTriangulationIndex() const{
    return triangleTriangulationIndex;
}

bool Triangle::isLeaf() const{
    return children.empty();
}

void Triangle::setDAGIndex(int index){
    triangleDAGIndex=index;
}

void Triangle::setTriangulationIndex(int index){
    triangleTriangulationIndex = index;
}
