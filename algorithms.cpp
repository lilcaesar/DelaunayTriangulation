#include "algorithms.h"

#include <cg3/core/cg3/geometry/2d/utils2d.h>

int findTriangle(const cg3::Point2Dd& vertex,const Triangle& triangle, DAG& graph){
    int finalTriangle;
    finalTriangle = triangle.getTriangleDAGIndex();
    if(!triangle.isLeaf()){
        if(cg3::isPointLyingInTriangle(graph.getTriangle(triangle.getSon1()).p1(),
                                       graph.getTriangle(triangle.getSon1()).p2(),
                                       graph.getTriangle(triangle.getSon1()).p3(),
                                       vertex, true
                                       )){
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getSon1()), graph);
        }else if(cg3::isPointLyingInTriangle(graph.getTriangle(triangle.getSon2()).p1(),
                                             graph.getTriangle(triangle.getSon2()).p2(),
                                             graph.getTriangle(triangle.getSon2()).p3(),
                                             vertex, true
                                             )){
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getSon2()), graph);
        }else{
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getSon3()), graph);
        }
    }
    return finalTriangle;
}

void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph){
    int triangle;
    triangle = findTriangle(newVertex, graph.getRootTriangle(), graph);
    graph.addNodes(triangle, newVertex);
    triangulation.insertVertex(newVertex);
    triangulation.swap(graph.getTriangle(triangle).getTriangleTriangulationIndex(), &graph.getTriangle(graph.getNtriangles()-3));
    triangulation.addTriangle(&graph.getTriangle(graph.getNtriangles()-2));
    triangulation.addTriangle(&graph.getTriangle(graph.getNtriangles()-1));
}
