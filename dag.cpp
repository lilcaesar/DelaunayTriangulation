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

void DAG::edgeFlip(int triangle1, int triangle2){
    nTriangle = nTriangle+2;
    int oppositePointPosition= nodes[triangle2].getPointIndex(nodes[triangle1].p2(),nodes[triangle1].p3());

    if(oppositePointPosition==1){//TODO Check if 1 is a possible solution(i suppose it culd be only -1, 2 or 3)
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle1].p2(), nodes[triangle2].p1(),
                                 nTriangle-2, nodes[triangle1].getAdj1(), nodes[triangle2].getAdj3(), nTriangle-1));
        nodes.push_back(Triangle(nodes[triangle2].p1(), nodes[triangle2].p2(), nodes[triangle1].p1(),
                                 nTriangle-1, nodes[triangle2].getAdj1(), nodes[triangle1].getAdj3(), nTriangle-2));
        nodes[nodes[triangle2].getAdj1()].setAdj(triangle2, nTriangle-1);
        nodes[nodes[triangle1].getAdj3()].setAdj(triangle2, nTriangle-2);

    }else if(oppositePointPosition==2){
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle1].p2(), nodes[triangle2].p2(),
                                 nTriangle-2, nodes[triangle1].getAdj1(), nodes[triangle2].getAdj1(), nTriangle-1));
        nodes.push_back(Triangle(nodes[triangle2].p2(), nodes[triangle2].p3(), nodes[triangle1].p1(),
                                 nTriangle-1, nodes[triangle2].getAdj2(), nodes[triangle1].getAdj3(), nTriangle-2));
        nodes[nodes[triangle2].getAdj2()].setAdj(triangle2, nTriangle-2);
        nodes[nodes[triangle1].getAdj1()].setAdj(triangle2, nTriangle-1);
    }else if(oppositePointPosition==3){
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle1].p2(), nodes[triangle2].p3(),
                                 nTriangle-2, nodes[triangle1].getAdj1(), nodes[triangle2].getAdj2(), nTriangle-1));
        nodes.push_back(Triangle(nodes[triangle2].p3(), nodes[triangle2].p1(), nodes[triangle1].p1(),
                                 nTriangle-1, nodes[triangle2].getAdj3(), nodes[triangle1].getAdj3(), nTriangle-2));
        nodes[nodes[triangle2].getAdj3()].setAdj(triangle2, nTriangle-2);
        nodes[nodes[triangle1].getAdj2()].setAdj(triangle2, nTriangle-1);
    }

    nodes[nodes[triangle1].getAdj1()].setAdj(triangle1, nTriangle-2);
    nodes[nodes[triangle1].getAdj3()].setAdj(triangle1, nTriangle-1);

    nodes[triangle1].addChild(nTriangle-2);
    nodes[triangle1].addChild(nTriangle-1);
    nodes[triangle2].addChild(nTriangle-2);
    nodes[triangle2].addChild(nTriangle-1);
}

void DAG::addNodes(int triangle,const cg3::Point2Dd& newPoint){
    nTriangle=nTriangle+3;
    //store the adjacency values of the father node in order to give them to the child and update all the relatives triangles
    int adj1=nodes[triangle].getAdj1();
    int adj2=nodes[triangle].getAdj2();
    int adj3=nodes[triangle].getAdj3();
    //adj==-1 means outside the bounding triangle
    if(adj1>=0){
        nodes[adj1].setAdj(triangle, nTriangle-3);
        nodes.push_back(Triangle(newPoint, nodes[triangle].p1(), nodes[triangle].p2(), nTriangle-3,
                                 nTriangle-1, adj1, nTriangle-2));
    }else{
        nodes.push_back(Triangle(newPoint, nodes[triangle].p1(), nodes[triangle].p2(), nTriangle-3,
                                 nTriangle-1, adj1, nTriangle-2));
    }

    if(adj2>=0){
        nodes[adj2].setAdj(triangle, nTriangle-2);
        nodes.push_back(Triangle(newPoint, nodes[triangle].p2(), nodes[triangle].p3(), nTriangle-2,
                                 nTriangle-3, adj2, nTriangle-1));
    }else{
        nodes.push_back(Triangle(newPoint, nodes[triangle].p2(), nodes[triangle].p3(), nTriangle-2,
                                 nTriangle-3, adj2, nTriangle-1));
    }

    if(adj3>=0){
        nodes[adj3].setAdj(triangle, nTriangle-1);
        nodes.push_back(Triangle(newPoint, nodes[triangle].p3(), nodes[triangle].p1(), nTriangle-1,
                                 nTriangle-2, adj3, nTriangle-3));
    }else{
        nodes.push_back(Triangle(newPoint, nodes[triangle].p3(), nodes[triangle].p1(), nTriangle-1,
                                 nTriangle-2, adj3, nTriangle-3));
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
