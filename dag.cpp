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

Triangle& DAG::getTriangle(int index){
    return nodes[index];
}

void DAG::addPoint(const cg3::Point2Dd& newPoint){
    points.push_back(newPoint);
    nPoints++;
}

cg3::Point2Dd &DAG::getPoint(int index){
    return points[index];
}

int DAG::getNtriangles() const{
    return nTriangle;
}

std::vector<Triangle>* DAG::getVector(){
    return &nodes;
}

void DAG::clearGraph(){
    nodes.clear();
    points.clear();
    nTriangle=1;
    nPoints=3;
    points.push_back(bounding1);
    points.push_back(bounding2);
    points.push_back(bounding3);
    nodes.push_back(Triangle(0,1,2,-1,-1,-1,-1));
    nodes[0].setDAGIndex(0);
    nodes[0].setTriangulationIndex(0);

}

std::vector<cg3::Point2Dd> DAG::getPoints(){
    return points;
}

int DAG::getNPoints(){
    return nPoints;
}
