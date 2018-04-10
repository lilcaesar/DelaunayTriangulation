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

void DAG::edgeFlip(int triangle1, int triangle2){
    nTriangle = nTriangle+2;
    int oppositePointPosition= nodes[triangle2].getPointIndex(nodes[triangle1].p2(),nodes[triangle1].p3());

    if(oppositePointPosition==1){//TODO Check if 1 is a possible solution(i suppose it culd be only -1, 2 or 3)
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle1].p2(), nodes[triangle2].p1(),
                                 nTriangle-2, nodes[triangle1].getAdj1(), nodes[triangle2].getAdj3(), nTriangle-1));
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle2].p1(), nodes[triangle2].p2(),
                                 nTriangle-1, nTriangle-2, nodes[triangle2].getAdj1(), nodes[triangle1].getAdj3()));
        nodes[nodes[triangle2].getAdj1()].setAdj(triangle2, nTriangle-1);
        nodes[nodes[triangle2].getAdj3()].setAdj(triangle2, nTriangle-2);

    }else if(oppositePointPosition==2){
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle1].p2(), nodes[triangle2].p2(),
                                 nTriangle-2, nodes[triangle1].getAdj1(), nodes[triangle2].getAdj1(), nTriangle-1));
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle2].p2(), nodes[triangle2].p3(),
                                 nTriangle-1, nTriangle-2, nodes[triangle2].getAdj2(), nodes[triangle1].getAdj3()));
        nodes[nodes[triangle2].getAdj2()].setAdj(triangle2, nTriangle-1);
        nodes[nodes[triangle2].getAdj1()].setAdj(triangle2, nTriangle-2);
    }else if(oppositePointPosition==3){
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle1].p2(), nodes[triangle2].p3(),
                                 nTriangle-2, nodes[triangle1].getAdj1(), nodes[triangle2].getAdj2(), nTriangle-1));
        nodes.push_back(Triangle(nodes[triangle1].p1(), nodes[triangle2].p3(), nodes[triangle2].p1(),
                                 nTriangle-1, nTriangle-2, nodes[triangle2].getAdj3(), nodes[triangle1].getAdj3()));
        nodes[nodes[triangle2].getAdj3()].setAdj(triangle2, nTriangle-1);
        nodes[nodes[triangle2].getAdj2()].setAdj(triangle2, nTriangle-2);
    }

    nodes[nodes[triangle1].getAdj1()].setAdj(triangle1, nTriangle-2);
    nodes[nodes[triangle1].getAdj3()].setAdj(triangle1, nTriangle-1);

    nodes[triangle1].addChild(nTriangle-2);
    nodes[triangle1].addChild(nTriangle-1);
    nodes[triangle2].addChild(nTriangle-2);
    nodes[triangle2].addChild(nTriangle-1);
}

void DAG::addNodes(int triangle,const cg3::Point2Dd& newPoint){
    points.push_back(newPoint);
    nPoints++;
    nTriangle=nTriangle+3;
    //store the adjacency values of the father node in order to give them to the child and update all the relatives triangles
    int adj1=nodes[triangle].getAdj1();
    int adj2=nodes[triangle].getAdj2();
    int adj3=nodes[triangle].getAdj3();
    //adj==-1 means outside the bounding triangle
    if(adj1>=0){
        nodes[adj1].setAdj(triangle, nTriangle-3);
        nodes.push_back(Triangle(nPoints-1, nodes[triangle].p1(), nodes[triangle].p2(), nTriangle-3,
                                 nTriangle-1, adj1, nTriangle-2));
    }else{
        nodes.push_back(Triangle(nPoints-1, nodes[triangle].p1(), nodes[triangle].p2(), nTriangle-3,
                                 nTriangle-1, adj1, nTriangle-2));
    }

    if(adj2>=0){
        nodes[adj2].setAdj(triangle, nTriangle-2);
        nodes.push_back(Triangle(nPoints-1, nodes[triangle].p2(), nodes[triangle].p3(), nTriangle-2,
                                 nTriangle-3, adj2, nTriangle-1));
    }else{
        nodes.push_back(Triangle(nPoints-1, nodes[triangle].p2(), nodes[triangle].p3(), nTriangle-2,
                                 nTriangle-3, adj2, nTriangle-1));
    }

    if(adj3>=0){
        nodes[adj3].setAdj(triangle, nTriangle-1);
        nodes.push_back(Triangle(nPoints-1, nodes[triangle].p3(), nodes[triangle].p1(), nTriangle-1,
                                 nTriangle-2, adj3, nTriangle-3));
    }else{
        nodes.push_back(Triangle(nPoints-1, nodes[triangle].p3(), nodes[triangle].p1(), nTriangle-1,
                                 nTriangle-2, adj3, nTriangle-3));
    }

    nodes[triangle].addChild(nTriangle-3);
    nodes[triangle].addChild(nTriangle-2);
    nodes[triangle].addChild(nTriangle-1);
}

Triangle& DAG::getTriangle(int index){
    return nodes[index];
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
