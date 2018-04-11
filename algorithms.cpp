#include "algorithms.h"

#include <Eigen/Geometry>
#include <cg3/core/cg3/geometry/2d/utils2d.h>

int findTriangle(const cg3::Point2Dd& vertex,const Triangle& triangle, DAG& graph){
    int finalTriangle;
    finalTriangle = triangle.getTriangleDAGIndex();
    if(!triangle.isLeaf()){
        if(cg3::isPointLyingInTriangle(graph.getPoint(graph.getTriangle(triangle.getChild1()).p1()),
                                       graph.getPoint(graph.getTriangle(triangle.getChild1()).p2()),
                                       graph.getPoint(graph.getTriangle(triangle.getChild1()).p3()),
                                       vertex, true
                                       )){
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getChild1()), graph);
        }else if(cg3::isPointLyingInTriangle(graph.getPoint(graph.getTriangle(triangle.getChild2()).p1()),
                                             graph.getPoint(graph.getTriangle(triangle.getChild2()).p2()),
                                             graph.getPoint(graph.getTriangle(triangle.getChild2()).p3()),
                                             vertex, true
                                             )){
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getChild2()), graph);
        }else{
            finalTriangle = findTriangle(vertex, graph.getTriangle(triangle.getChild3()), graph);
        }
    }
    return finalTriangle;
}

void legalizeEdge(int triangle, DAG &graph, Triangulation& triangulation){
    /*The new inserted point is always in the first position and the index for the triangle adjacent to
    the opposing segment therefore is the second (look at the Triangle class for further information)*/
    if(graph.getTriangle(triangle).getAdj2()!=-1){
        if(cg3::isPointLyingInCircle(graph.getPoint(graph.getTriangle(graph.getTriangle(triangle).getAdj2()).p1()),
                                     graph.getPoint(graph.getTriangle(graph.getTriangle(triangle).getAdj2()).p2()),
                                     graph.getPoint(graph.getTriangle(graph.getTriangle(triangle).getAdj2()).p3()),
                                     graph.getPoint(graph.getTriangle(triangle).p1()), true)){
            graph.edgeFlip(graph.getTriangle(triangle).getTriangleDAGIndex(), graph.getTriangle(triangle).getAdj2());
            triangulation.swap(graph.getTriangle(triangle).getTriangleTriangulationIndex(), graph.getNtriangles()-2);
            triangulation.swap(graph.getTriangle(graph.getTriangle(triangle).getAdj2()).getTriangleTriangulationIndex(), graph.getNtriangles()-1);
            int nTriangles = graph.getNtriangles();
            legalizeEdge(nTriangles-2, graph, triangulation);
            legalizeEdge(nTriangles-1, graph, triangulation);
        }
    }
}

void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph){
    int triangle;
    triangle = findTriangle(newVertex, graph.getRootTriangle(), graph);
    graph.addNodes(triangle, newVertex);
    triangulation.swap(graph.getTriangle(triangle).getTriangleTriangulationIndex(), graph.getNtriangles()-3);
    triangulation.addTriangle(graph.getNtriangles()-2);
    triangulation.addTriangle(graph.getNtriangles()-1);
    //We need this variable since legalizeEdge could add triangles so we can't use the DAG method safely
    int nTriangles=graph.getNtriangles();
    legalizeEdge(nTriangles-3, graph, triangulation);
    legalizeEdge(nTriangles-2, graph, triangulation);
    legalizeEdge(nTriangles-1, graph, triangulation);
    //
}
