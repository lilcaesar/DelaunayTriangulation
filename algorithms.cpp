#include "algorithms.h"

#include <cg3/core/cg3/geometry/2d/utils2d.h>

int findTriangle(const cg3::Point2Dd& vertex,const Triangle& triangle, DAG& graph){
    int finalTriangle;
    finalTriangle = triangle.getTriangleDAGIndex();
    if(!triangle.isLeaf()){
        if(cg3::isPointLyingInTriangle(graph.getTriangle(triangle.getChild1()).p1(),
                                       graph.getTriangle(triangle.getChild1()).p2(),
                                       graph.getTriangle(triangle.getChild1()).p3(),
                                       vertex, true
                                       )){
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getChild1()), graph);
        }else if(cg3::isPointLyingInTriangle(graph.getTriangle(triangle.getChild2()).p1(),
                                             graph.getTriangle(triangle.getChild2()).p2(),
                                             graph.getTriangle(triangle.getChild2()).p3(),
                                             vertex, true
                                             )){
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getChild2()), graph);
        }else{
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getChild3()), graph);
        }
    }
    return finalTriangle;
}

void legalizeEdge(Triangle *triangle, DAG &graph, Triangulation& triangulation){
    /*The new inserted point is always in the first position and the index for the triangle adjacent to
    the opposing segment therefore is the second (look at the Triangle class for further information)*/
    if((cg3::isPointLyingInCircle(graph.getTriangle(triangle->getAdj2()).p1(),
                                 graph.getTriangle(triangle->getAdj2()).p2(),
                                 graph.getTriangle(triangle->getAdj2()).p3(),
                                 triangle->p1(), true))&&(triangle->getAdj2()!=-1)){
        if(graph.getTriangle(triangle->getAdj2()).getAdj2()!=-1){
            graph.edgeFlip(triangle->getTriangleDAGIndex(), triangle->getAdj2());
            triangulation.swap(triangle->getTriangleTriangulationIndex(), &graph.getTriangle(graph.getNtriangles()-2));
            triangulation.swap(graph.getTriangle(triangle->getAdj2()).getTriangleTriangulationIndex(), &graph.getTriangle(graph.getNtriangles()-1));
            legalizeEdge(&graph.getTriangle(graph.getNtriangles()-2), graph, triangulation);
            legalizeEdge(&graph.getTriangle(graph.getNtriangles()-1), graph, triangulation);
        }
    }
}

void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph){
    int triangle;
    triangle = findTriangle(newVertex, graph.getRootTriangle(), graph);
    graph.addNodes(triangle, newVertex);
    triangulation.insertVertex(newVertex);
    triangulation.swap(graph.getTriangle(triangle).getTriangleTriangulationIndex(), &graph.getTriangle(graph.getNtriangles()-3));
    triangulation.addTriangle(&graph.getTriangle(graph.getNtriangles()-2));
    triangulation.addTriangle(&graph.getTriangle(graph.getNtriangles()-1));
    //We need this variable since legalizeEdge could add triangles so we can't use the DAG method safely
    int nTriangles=graph.getNtriangles();
    legalizeEdge(&graph.getTriangle(nTriangles-3), graph, triangulation);
    legalizeEdge(&graph.getTriangle(nTriangles-2), graph, triangulation);
    legalizeEdge(&graph.getTriangle(nTriangles-1), graph, triangulation);
    //
}
