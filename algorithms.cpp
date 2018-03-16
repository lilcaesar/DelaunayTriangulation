#include "algorithms.h"

#include <cg3/core/cg3/geometry/2d/utils2d.h>

Triangle* findTriangle(const cg3::Point2Dd& vertex,Triangle* triangle){
    Triangle* finalTriangle;
    finalTriangle = triangle;
    if(!triangle->isLeaf()){
        if(cg3::isPointLyingInTriangle(triangle->getSon1()->p1(),
                                       triangle->getSon1()->p2(),
                                       triangle->getSon1()->p3(),
                                       vertex, true
                                       )){
            finalTriangle = findTriangle(vertex, triangle->getSon1());
        }else if(cg3::isPointLyingInTriangle(triangle->getSon2()->p1(),
                                             triangle->getSon2()->p2(),
                                             triangle->getSon2()->p3(),
                                             vertex, true
                                             )){
            finalTriangle = findTriangle(vertex, triangle->getSon2());
        }else{
            finalTriangle = findTriangle(vertex, triangle->getSon3());
        }
    }
    return finalTriangle;
}

void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph){
    Triangle* triangle;
    triangulation.insertVertex(newVertex);
    triangle = findTriangle(newVertex, graph.getRootTriangle());
}
