#include "triangle.h"

Triangle::Triangle(){
}

Triangle::Triangle(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3) : p_1(p1), p_2(p2), p_3(p3){

}

Triangle::Triangle(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3, int DAGIndex) : triangleDAGIndex(DAGIndex), p_1(p1), p_2(p2), p_3(p3){

}

cg3::Point2Dd Triangle::p1() const{
    return p_1;
}

cg3::Point2Dd Triangle::p2() const{
    return p_2;
}

cg3::Point2Dd Triangle::p3() const{
    return p_3;
}

Triangle& Triangle::getSon1() const{
    return *sons[0];
}

Triangle& Triangle::getSon2() const{
    return *sons[1];
}

Triangle& Triangle::getSon3() const{
    return *sons[2];
}

void Triangle::addSon(Triangle* son){
    sons.push_back(son);
}

int Triangle::getTriangleDAGIndex() const{
    return triangleDAGIndex;
}

int Triangle::getTriangleTriangulationIndex() const{
    return triangleTriangulationIndex;
}

bool Triangle::isLeaf() const{
    return sons.empty();
}

void Triangle::setDAGIndex(int index){
    triangleDAGIndex=index;
}

void Triangle::setTriangulationIndex(int index){
    triangleTriangulationIndex = index;
}
