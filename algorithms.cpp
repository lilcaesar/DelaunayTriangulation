#include "algorithms.h"

#include <Eigen/Geometry>
#include <cg3/core/cg3/geometry/2d/utils2d.h>

int findTriangle(const cg3::Point2Dd& vertex,const Triangle& triangle,const DAG& graph){
    int finalTriangle;
    finalTriangle = triangle.getTriangleDAGIndex();

    while(!(graph.getTriangle(finalTriangle).isLeaf())){
        if(cg3::isPointLyingInTriangle(graph.getPoint(graph.getTriangle(graph.getTriangle(finalTriangle).getChild1()).p1()),
                                       graph.getPoint(graph.getTriangle(graph.getTriangle(finalTriangle).getChild1()).p2()),
                                       graph.getPoint(graph.getTriangle(graph.getTriangle(finalTriangle).getChild1()).p3()),
                                       vertex, true
                                       )){
            finalTriangle = graph.getTriangle(finalTriangle).getChild1();
        }else if(cg3::isPointLyingInTriangle(graph.getPoint(graph.getTriangle(graph.getTriangle(finalTriangle).getChild2()).p1()),
                                             graph.getPoint(graph.getTriangle(graph.getTriangle(finalTriangle).getChild2()).p2()),
                                             graph.getPoint(graph.getTriangle(graph.getTriangle(finalTriangle).getChild2()).p3()),
                                             vertex, true
                                             )){
            finalTriangle = graph.getTriangle(finalTriangle).getChild2();
        }else{
            finalTriangle = graph.getTriangle(finalTriangle).getChild3();
        }
    }

    return finalTriangle;
}

void edgeFlip(int triangle1, int triangle2, DAG &graph){
    int nTriangle= graph.getNtriangles()+2;
    int oppositePointPosition= graph.getTriangle(triangle2).getPointIndex(graph.getTriangle(triangle1).p2(),graph.getTriangle(triangle1).p3());

    if(oppositePointPosition==1){
        graph.addNode(Triangle(graph.getTriangle(triangle1).p1(), graph.getTriangle(triangle1).p2(), graph.getTriangle(triangle2).p1(),
                                 nTriangle-2, graph.getTriangle(triangle1).getAdj1(), graph.getTriangle(triangle2).getAdj3(), nTriangle-1));
        graph.addNode(Triangle(graph.getTriangle(triangle1).p1(), graph.getTriangle(triangle2).p1(), graph.getTriangle(triangle2).p2(),
                                 nTriangle-1, nTriangle-2, graph.getTriangle(triangle2).getAdj1(), graph.getTriangle(triangle1).getAdj3()));
        if(graph.getTriangle(triangle2).getAdj1()!=-1){
            graph.changeTriangleAdj(graph.getTriangle(triangle2).getAdj1(), triangle2, nTriangle-1);
        }
        if(graph.getTriangle(triangle2).getAdj3()!=-1){
            graph.changeTriangleAdj(graph.getTriangle(triangle2).getAdj3(), triangle2, nTriangle-2);
        }

    }else if(oppositePointPosition==2){
        graph.addNode(Triangle(graph.getTriangle(triangle1).p1(), graph.getTriangle(triangle1).p2(), graph.getTriangle(triangle2).p2(),
                                 nTriangle-2, graph.getTriangle(triangle1).getAdj1(), graph.getTriangle(triangle2).getAdj1(), nTriangle-1));
        graph.addNode(Triangle(graph.getTriangle(triangle1).p1(), graph.getTriangle(triangle2).p2(), graph.getTriangle(triangle2).p3(),
                                 nTriangle-1, nTriangle-2, graph.getTriangle(triangle2).getAdj2(), graph.getTriangle(triangle1).getAdj3()));
        if(graph.getTriangle(triangle2).getAdj2()!=-1){
            graph.changeTriangleAdj(graph.getTriangle(triangle2).getAdj2(), triangle2, nTriangle-1);
        }
        if(graph.getTriangle(triangle2).getAdj1()!=-1){
            graph.changeTriangleAdj(graph.getTriangle(triangle2).getAdj1(), triangle2, nTriangle-2);
        }
    }else if(oppositePointPosition==3){
        graph.addNode(Triangle(graph.getTriangle(triangle1).p1(), graph.getTriangle(triangle1).p2(), graph.getTriangle(triangle2).p3(),
                                 nTriangle-2, graph.getTriangle(triangle1).getAdj1(), graph.getTriangle(triangle2).getAdj2(), nTriangle-1));
        graph.addNode(Triangle(graph.getTriangle(triangle1).p1(), graph.getTriangle(triangle2).p3(), graph.getTriangle(triangle2).p1(),
                                 nTriangle-1, nTriangle-2, graph.getTriangle(triangle2).getAdj3(), graph.getTriangle(triangle1).getAdj3()));
        if(graph.getTriangle(triangle2).getAdj3()!=-1){
            graph.changeTriangleAdj(graph.getTriangle(triangle2).getAdj3(), triangle2, nTriangle-1);
        }
        if(graph.getTriangle(triangle2).getAdj2()!=-1){
            graph.changeTriangleAdj(graph.getTriangle(triangle2).getAdj2(), triangle2, nTriangle-2);
        }
    }

    graph.changeTriangleAdj(graph.getTriangle(triangle1).getAdj1(), triangle1, nTriangle-2);
    graph.changeTriangleAdj(graph.getTriangle(triangle1).getAdj3(), triangle1, nTriangle-1);

    graph.addTriangleChild(triangle1, nTriangle-2);
    graph.addTriangleChild(triangle1, nTriangle-1);
    graph.addTriangleChild(triangle2, nTriangle-2);
    graph.addTriangleChild(triangle2, nTriangle-1);
}

void legalizeEdge(int triangle, DAG &graph, Triangulation& triangulation){
    /*The new inserted point is always in the first position and the index for the triangle adjacent to
    the opposing segment therefore is the second (look at the Triangle class for further information)*/
    if(graph.getTriangle(triangle).getAdj2()!=-1){
        if(cg3::isPointLyingInCircle(graph.getPoint(graph.getTriangle(graph.getTriangle(triangle).getAdj2()).p1()),
                                     graph.getPoint(graph.getTriangle(graph.getTriangle(triangle).getAdj2()).p2()),
                                     graph.getPoint(graph.getTriangle(graph.getTriangle(triangle).getAdj2()).p3()),
                                     graph.getPoint(graph.getTriangle(triangle).p1()), true)){
            edgeFlip(graph.getTriangle(triangle).getTriangleDAGIndex(), graph.getTriangle(triangle).getAdj2(), graph);
            triangulation.swap(graph.getTriangle(triangle).getTriangleTriangulationIndex(), graph.getNtriangles()-2);
            triangulation.swap(graph.getTriangle(graph.getTriangle(triangle).getAdj2()).getTriangleTriangulationIndex(), graph.getNtriangles()-1);
            int nTriangles = graph.getNtriangles();
            legalizeEdge(nTriangles-2, graph, triangulation);
            legalizeEdge(nTriangles-1, graph, triangulation);
        }
    }
}

void addNodes(int triangle,const cg3::Point2Dd& newPoint, DAG& graph){
    graph.addPoint(newPoint);
    //store the adjacency values of the father node in order to give them to the child and update all the relatives triangles
    int adj1=graph.getTriangle(triangle).getAdj1();
    int adj2=graph.getTriangle(triangle).getAdj2();
    int adj3=graph.getTriangle(triangle).getAdj3();
    int nPoints=graph.getNPoints();
    int nTriangles= graph.getNtriangles()+3;
    //adj==-1 means outside the bounding triangle
    if(adj1>=0){
        graph.addNode(Triangle(nPoints-1, graph.getTriangle(triangle).p1(), graph.getTriangle(triangle).p2(), nTriangles-3,
                               nTriangles-1, adj1, nTriangles-2));
        graph.changeTriangleAdj(adj1, triangle, nTriangles-3);
    }else{
        graph.addNode(Triangle(nPoints-1, graph.getTriangle(triangle).p1(), graph.getTriangle(triangle).p2(), nTriangles-3,
                               nTriangles-1, adj1, nTriangles-2));
    }

    if(adj2>=0){
        graph.addNode(Triangle(nPoints-1, graph.getTriangle(triangle).p2(), graph.getTriangle(triangle).p3(), nTriangles-2,
                                 nTriangles-3, adj2, nTriangles-1));
        graph.changeTriangleAdj(adj2, triangle, nTriangles-2);
    }else{
        graph.addNode(Triangle(nPoints-1, graph.getTriangle(triangle).p2(), graph.getTriangle(triangle).p3(), nTriangles-2,
                                 nTriangles-3, adj2, nTriangles-1));
    }

    if(adj3>=0){
        graph.addNode(Triangle(nPoints-1, graph.getTriangle(triangle).p3(), graph.getTriangle(triangle).p1(), nTriangles-1,
                                 nTriangles-2, adj3, nTriangles-3));
        graph.changeTriangleAdj(adj3, triangle, nTriangles-1);
    }else{
        graph.addNode(Triangle(nPoints-1, graph.getTriangle(triangle).p3(), graph.getTriangle(triangle).p1(), nTriangles-1,
                                 nTriangles-2, adj3, nTriangles-3));
    }

    graph.addTriangleChild(triangle, nTriangles-3);
    graph.addTriangleChild(triangle, nTriangles-2);
    graph.addTriangleChild(triangle, nTriangles-1);
}

void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph){
    int triangle;
    triangle = findTriangle(newVertex, graph.getRootTriangle(), graph);
    addNodes(triangle, newVertex, graph);
    triangulation.swap(graph.getTriangle(triangle).getTriangleTriangulationIndex(),  graph.getNtriangles()-3);
    triangulation.addTriangle(graph.getTriangle(graph.getNtriangles()-2));
    triangulation.addTriangle(graph.getTriangle(graph.getNtriangles()-1));
    //We need this variable since legalizeEdge could add triangles so we can't use the DAG method safely
    int nTriangles=graph.getNtriangles();
    legalizeEdge(nTriangles-3, graph, triangulation);
    legalizeEdge(nTriangles-2, graph, triangulation);
    legalizeEdge(nTriangles-1, graph, triangulation);
}
