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
    int adj1=nodes[triangle].getAdj1();
    int adj2=nodes[triangle].getAdj2();
    int adj3=nodes[triangle].getAdj3();
    nodes.push_back(Triangle(newPoint, nodes[triangle].p1(), nodes[triangle].p2(), nTriangle-3,
                             nTriangle-1, adj1, nTriangle-2));
    if(adj1>=0){
        nodes[adj1].setAdj(triangle, nTriangle-3);
    }
    nodes.push_back(Triangle(newPoint, nodes[triangle].p2(), nodes[triangle].p3(), nTriangle-2,
                             nTriangle-3, adj2, nTriangle-1));
    if(adj2>=0){
        nodes[adj2].setAdj(triangle, nTriangle-2);
    }
    nodes.push_back(Triangle(newPoint, nodes[triangle].p3(), nodes[triangle].p1(), nTriangle-1,
                             nTriangle-2, adj3, nTriangle-3));
    if(adj3>=0){
        nodes[adj3].setAdj(triangle, nTriangle-1);
    }
    nodes[triangle].addChild(nTriangle-3);
    nodes[triangle].addChild(nTriangle-2);
    nodes[triangle].addChild(nTriangle-1);
}

Triangle& DAG::getTriangle(int index){
    return nodes[index];
}

int DAG::getNtriangles() const{
    return nTriangle;
}

std::vector<Triangle>* DAG::getVector(){
    return &nodes;
}

bool DAG::clearGraph()
{
    nodes.clear();
    return nodes.empty();
}
