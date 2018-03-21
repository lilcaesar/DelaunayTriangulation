#include "dag.h"

DAG::DAG(): nTriangle(0)
{
}

Triangle DAG::getRootTriangle()const{
    return nodes[0];
}

void DAG::addNodes(int triangle,const cg3::Point2Dd& newPoint){
    nTriangle=nTriangle+3;
    nodes.push_back(Triangle(newPoint, nodes[triangle].p1(), nodes[triangle].p2()));
    nodes.push_back(Triangle(newPoint, nodes[triangle].p2(), nodes[triangle].p3()));
    nodes.push_back(Triangle(newPoint, nodes[triangle].p3(), nodes[triangle].p1()));
    nodes[triangle].addSon(&nodes[nTriangle-3]);
    nodes[triangle].addSon(&nodes[nTriangle-2]);
    nodes[triangle].addSon(&nodes[nTriangle-1]);
}
