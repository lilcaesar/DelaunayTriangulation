#include "dag.h"

DAG::DAG(): nTriangle(0){
}
DAG::DAG(Triangle triangle): nTriangle(1){
    triangle.setDAGIndex(0);
    nodes.push_back(triangle);
}

Triangle& DAG::getRootTriangle(){
    return nodes[0];
}

void DAG::addNodes(int triangle,const cg3::Point2Dd& newPoint){
    nTriangle=nTriangle+3;
    nodes.push_back(Triangle(newPoint, nodes[triangle].p1(), nodes[triangle].p2(), nTriangle-3));
    nodes.push_back(Triangle(newPoint, nodes[triangle].p2(), nodes[triangle].p3(), nTriangle-2));
    nodes.push_back(Triangle(newPoint, nodes[triangle].p3(), nodes[triangle].p1(), nTriangle-1));
    nodes[triangle].addSon(&nodes[nTriangle-3]);
    nodes[triangle].addSon(&nodes[nTriangle-2]);
    nodes[triangle].addSon(&nodes[nTriangle-1]);
}

Triangle& DAG::getTriangle(int index){
    return nodes[index];
}

int DAG::getNtriangles() const{
    return nTriangle;
}
