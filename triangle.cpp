#include "triangle.h"
#include <algorithm>

Triangle::Triangle(int p1, int p2, int p3) : p_1(p1), p_2(p2), p_3(p3){

}

Triangle::Triangle(int p1, int p2, int p3, int adj1, int adj2, int adj3) : p_1(p1), p_2(p2), p_3(p3){
    adjacencies.push_back(adj1);
    adjacencies.push_back(adj2);
    adjacencies.push_back(adj3);
}

Triangle::Triangle(int p1, int p2, int p3, int DAGIndex) : triangleDAGIndex(DAGIndex), p_1(p1), p_2(p2), p_3(p3){

}

Triangle::Triangle(int p1, int p2, int p3, int DAGIndex, int adj1, int adj2, int adj3) : triangleDAGIndex(DAGIndex), p_1(p1), p_2(p2), p_3(p3){
    adjacencies.push_back(adj1);
    adjacencies.push_back(adj2);
    adjacencies.push_back(adj3);
}

int Triangle::p1() const{
    return p_1;
}

int Triangle::p2() const{
    return p_2;
}

int Triangle::p3() const{
    return p_3;
}

int Triangle::getPointIndex(const int point1, const int point2){
    if((p_1==point1 && p_2==point2)||(p_2==point1 && p_1==point2))
        return 3;
    if((p_2==point1 && p_3==point2)||(p_3==point1 && p_2==point2))
        return 1;
    if((p_3==point1 && p_1==point2)||(p_1==point1 && p_3==point2))
        return 2;
    return -1;
}

int Triangle::getChild1() const{
    return children[0];
}

int Triangle::getChild2() const{
    return children[1];
}

int Triangle::getChild3() const{
    return children[2];
}

void Triangle::addChild(int child){
    children.push_back(child);
}

int Triangle::getAdj1() const{
    return adjacencies[0];
}

int Triangle::getAdj2() const{
    return adjacencies[1];
}

int Triangle::getAdj3() const{
    return adjacencies[2];
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
