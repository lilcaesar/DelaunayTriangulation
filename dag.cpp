#include "dag.h"

DAG::DAG(): nTriangle(0){
}
DAG::DAG(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3): bounding1(p1), bounding2(p2), bounding3(p3), nPoints(3), nTriangle(1){
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    nodes.push_back(Triangle(0,1,2,-1,-1,-1,-1));
    nodes[0].setDAGIndex(0);
    nodes[0].setTriangulationIndex(0);
}

Triangle& DAG::getRootTriangle(){
    return nodes[0];
}

void DAG::addNode(Triangle newNode){
    nodes.push_back(newNode);
    nTriangle++;
}

void DAG::addPoint(const cg3::Point2Dd& newPoint){
    points.push_back(newPoint);
    nPoints++;
}

void DAG::changeTriangleAdj(int triangle, int oldValue, int newValue){
    nodes[triangle].setAdj(oldValue, newValue);
}

void DAG::addTriangleChild(int triangle, int child){
    nodes[triangle].addChild(child);
}

void DAG::setTriangleTriangulationIndex(int triangle, int index){
    nodes[triangle].setTriangulationIndex(index);
}

int DAG::getNtriangles() const{
    return nTriangle;
}

void DAG::clearGraph(){
    nodes.clear();
    points.clear();
}

void DAG::initializeBounding(){
    nTriangle=1;
    nPoints=3;
    points.push_back(bounding1);
    points.push_back(bounding2);
    points.push_back(bounding3);
    nodes.push_back(Triangle(0,1,2,-1,-1,-1,-1));
    nodes[0].setDAGIndex(0);
    nodes[0].setTriangulationIndex(0);
}

std::vector<cg3::Point2Dd> DAG::getPoints() const{
    return points;
}

int DAG::getNPoints() const{
    return nPoints;
}
