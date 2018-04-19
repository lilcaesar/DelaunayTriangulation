#include "algorithms.h"

#include <Eigen/Geometry>
#include <cg3/core/cg3/geometry/2d/utils2d.h>

/**
 * @brief Find triangle from point.
 * @param vertex
 * @param graph
 * @return index of the node in the DAG
 *
 * This method finds the leaf triangle where the given
 * point lies on.
 */
int findTriangle(const cg3::Point2Dd& vertex, const DAG& graph){
    int finalTriangle=0;

    //If the current node is not a leaf we search in which of the children the vertex lies
    while(!(graph.getNode(finalTriangle).isLeaf())){
        int child1 = graph.getNode(finalTriangle).getChild1();
        int child2 = graph.getNode(finalTriangle).getChild2();
        if(cg3::isPointLyingInTriangle(graph.getPoint(graph.getNode(child1).p1()),
                                       graph.getPoint(graph.getNode(child1).p2()),
                                       graph.getPoint(graph.getNode(child1).p3()),
                                       vertex, true
                                       ))
        {
            finalTriangle = child1;
        }
        else if(cg3::isPointLyingInTriangle(graph.getPoint(graph.getNode(child2).p1()),
                                             graph.getPoint(graph.getNode(child2).p2()),
                                             graph.getPoint(graph.getNode(child2).p3()),
                                             vertex, true
                                             ))
        {
            finalTriangle = child2;
        }
        else{
            finalTriangle = graph.getNode(finalTriangle).getChild3();
        }
    }

    return finalTriangle;
}

/**
 * @brief Performs the edge flip of two adjacent triangles.
 * @param triangle1
 * @param triangle2
 * @param graph
 *
 * This method creates two new nodes corrisponding to result of
 * flipping the common edge of the two given triangle indices.
 * Then it adds the new nodes to the list of children inside the
 * original nodes.
 */
void edgeFlip(int triangle1, int triangle2, DAG &graph){
    int nTriangle= graph.getNtriangles()+2;

    //Search which is the position of the point of triangle2 not in common with the triangle1
    //since we need to know if it is p1, p2 or p3
    int oppositePointPosition= graph.getNode(triangle2).getOppositePointIndex(graph.getNode(triangle1).p2(),graph.getNode(triangle1).p3());

    //Then create the new nodes based on the value we have on the initial triangles
    if(oppositePointPosition==1){
        graph.addNode(DagNode(graph.getNode(triangle1).p1(), graph.getNode(triangle1).p2(), graph.getNode(triangle2).p1(),
                                 nTriangle-2, graph.getNode(triangle1).getAdj1(), graph.getNode(triangle2).getAdj3(), nTriangle-1));
        graph.addNode(DagNode(graph.getNode(triangle1).p1(), graph.getNode(triangle2).p1(), graph.getNode(triangle2).p2(),
                                 nTriangle-1, nTriangle-2, graph.getNode(triangle2).getAdj1(), graph.getNode(triangle1).getAdj3()));
        if(graph.getNode(triangle2).getAdj1()!=-1){
            graph.changeTriangleAdj(graph.getNode(triangle2).getAdj1(), triangle2, nTriangle-1);
        }
        if(graph.getNode(triangle2).getAdj3()!=-1){
            graph.changeTriangleAdj(graph.getNode(triangle2).getAdj3(), triangle2, nTriangle-2);
        }

    }else if(oppositePointPosition==2){
        graph.addNode(DagNode(graph.getNode(triangle1).p1(), graph.getNode(triangle1).p2(), graph.getNode(triangle2).p2(),
                                 nTriangle-2, graph.getNode(triangle1).getAdj1(), graph.getNode(triangle2).getAdj1(), nTriangle-1));
        graph.addNode(DagNode(graph.getNode(triangle1).p1(), graph.getNode(triangle2).p2(), graph.getNode(triangle2).p3(),
                                 nTriangle-1, nTriangle-2, graph.getNode(triangle2).getAdj2(), graph.getNode(triangle1).getAdj3()));
        if(graph.getNode(triangle2).getAdj2()!=-1){
            graph.changeTriangleAdj(graph.getNode(triangle2).getAdj2(), triangle2, nTriangle-1);
        }
        if(graph.getNode(triangle2).getAdj1()!=-1){
            graph.changeTriangleAdj(graph.getNode(triangle2).getAdj1(), triangle2, nTriangle-2);
        }
    }else if(oppositePointPosition==3){
        graph.addNode(DagNode(graph.getNode(triangle1).p1(), graph.getNode(triangle1).p2(), graph.getNode(triangle2).p3(),
                                 nTriangle-2, graph.getNode(triangle1).getAdj1(), graph.getNode(triangle2).getAdj2(), nTriangle-1));
        graph.addNode(DagNode(graph.getNode(triangle1).p1(), graph.getNode(triangle2).p3(), graph.getNode(triangle2).p1(),
                                 nTriangle-1, nTriangle-2, graph.getNode(triangle2).getAdj3(), graph.getNode(triangle1).getAdj3()));
        if(graph.getNode(triangle2).getAdj3()!=-1){
            graph.changeTriangleAdj(graph.getNode(triangle2).getAdj3(), triangle2, nTriangle-1);
        }
        if(graph.getNode(triangle2).getAdj2()!=-1){
            graph.changeTriangleAdj(graph.getNode(triangle2).getAdj2(), triangle2, nTriangle-2);
        }
    }

    //Update the adjacencies
    graph.changeTriangleAdj(graph.getNode(triangle1).getAdj1(), triangle1, nTriangle-2);
    graph.changeTriangleAdj(graph.getNode(triangle1).getAdj3(), triangle1, nTriangle-1);

    //Add the new nodes as children of the original nodes
    graph.addNodeChild(triangle1, nTriangle-2);
    graph.addNodeChild(triangle1, nTriangle-1);
    graph.addNodeChild(triangle2, nTriangle-2);
    graph.addNodeChild(triangle2, nTriangle-1);
}

/**
 * @brief Compute the legalization checking.
 * @param triangle
 * @param graph
 * @param triangulation
 *
 * The method checks if the first point of the triangle
 * (which corresponds to the new vertex) is inside the
 * circle built using the points of the adjacent triangle.
 * If so the edgeFlip funtion is called and the triangulation
 * is updated.
 */
void legalizeEdge(int triangle, DAG &graph, Triangulation& triangulation){
    /*The new inserted point is always in the first position and the index for the triangle adjacent to
    the opposing segment therefore is the second (look at the Triangle class for further information)*/
    if(graph.getNode(triangle).getAdj2()!=-1){
        //If the first vertex of the triangle (the new vertex) is inside the circle built from the vertices
        //of the triangle adjacent to the opposite edge we compute the edge flip
        if(cg3::isPointLyingInCircle(graph.getPoint(graph.getNode(graph.getNode(triangle).getAdj2()).p1()),
                                     graph.getPoint(graph.getNode(graph.getNode(triangle).getAdj2()).p2()),
                                     graph.getPoint(graph.getNode(graph.getNode(triangle).getAdj2()).p3()),
                                     graph.getPoint(graph.getNode(triangle).p1()), true)){

            //Call the edgeFlip function to create the new nodes
            edgeFlip(graph.getNode(triangle).getTriangleDAGIndex(), graph.getNode(triangle).getAdj2(), graph);

            //Substitute the triangles in the triangulation
            triangulation.swap(graph.getNode(triangle).getTriangleTriangulationIndex(), graph.getNtriangles()-2);
            triangulation.swap(graph.getNode(graph.getNode(triangle).getAdj2()).getTriangleTriangulationIndex(), graph.getNtriangles()-1);

            //Call the legalization for the new triangles
            int nTriangles = graph.getNtriangles();
            legalizeEdge(nTriangles-2, graph, triangulation);
            legalizeEdge(nTriangles-1, graph, triangulation);
        }
    }
}

/**
 * @brief Add new nodes to the DAG.
 * @param triangle
 * @param newPoint
 * @param graph
 *
 * The funcion take in input the new point and the leaf in which
 * we want to create the new nodes. AddNodes modifies the DAG
 * adding three new triangles as children of the given triangle.
 */
void addNodes(int triangle,const cg3::Point2Dd& newPoint, DAG& graph){
    graph.addPoint(newPoint);
    //store the adjacency values of the father node in order to give them to the child and update all the relatives triangles
    int adj1=graph.getNode(triangle).getAdj1();
    int adj2=graph.getNode(triangle).getAdj2();
    int adj3=graph.getNode(triangle).getAdj3();
    int nPoints=graph.getNPoints();
    int nTriangles= graph.getNtriangles()+3;
    //adj==-1 means outside the bounding triangle
    if(adj1>=0){
        graph.addNode(DagNode(nPoints-1, graph.getNode(triangle).p1(), graph.getNode(triangle).p2(), nTriangles-3,
                               nTriangles-1, adj1, nTriangles-2));
        graph.changeTriangleAdj(adj1, triangle, nTriangles-3);
    }else{
        graph.addNode(DagNode(nPoints-1, graph.getNode(triangle).p1(), graph.getNode(triangle).p2(), nTriangles-3,
                               nTriangles-1, adj1, nTriangles-2));
    }

    if(adj2>=0){
        graph.addNode(DagNode(nPoints-1, graph.getNode(triangle).p2(), graph.getNode(triangle).p3(), nTriangles-2,
                                 nTriangles-3, adj2, nTriangles-1));
        graph.changeTriangleAdj(adj2, triangle, nTriangles-2);
    }else{
        graph.addNode(DagNode(nPoints-1, graph.getNode(triangle).p2(), graph.getNode(triangle).p3(), nTriangles-2,
                                 nTriangles-3, adj2, nTriangles-1));
    }

    if(adj3>=0){
        graph.addNode(DagNode(nPoints-1, graph.getNode(triangle).p3(), graph.getNode(triangle).p1(), nTriangles-1,
                                 nTriangles-2, adj3, nTriangles-3));
        graph.changeTriangleAdj(adj3, triangle, nTriangles-1);
    }else{
        graph.addNode(DagNode(nPoints-1, graph.getNode(triangle).p3(), graph.getNode(triangle).p1(), nTriangles-1,
                                 nTriangles-2, adj3, nTriangles-3));
    }

    graph.addNodeChild(triangle, nTriangles-3);
    graph.addNodeChild(triangle, nTriangles-2);
    graph.addNodeChild(triangle, nTriangles-1);
}

/**
 * @brief Insert new vertex and derived nodes.
 * @param newVertex
 * @param triangulation
 * @param graph
 *
 * This method handles the creation of all the new nodes
 * and triangle of the DAG and the triangulation given
 * a new vertex.
 */
void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph){
    int triangle;
    //Find in which leaf the new vertex lies on
    triangle = findTriangle(newVertex, graph);

    //Add the new nodes as child of the found leaf
    addNodes(triangle, newVertex, graph);

    //Update the triangulation with the nes nodes
    triangulation.swap(graph.getNode(triangle).getTriangleTriangulationIndex(),  graph.getNtriangles()-3);
    triangulation.addTriangle(graph.getNode(graph.getNtriangles()-2));
    triangulation.addTriangle(graph.getNode(graph.getNtriangles()-1));

    //Compute the edge legalization for the new triangles
    //We need the variable nTriangles since legalizeEdge could add triangles so we can't use the DAG method safely
    int nTriangles=graph.getNtriangles();
    legalizeEdge(nTriangles-3, graph, triangulation);
    legalizeEdge(nTriangles-2, graph, triangulation);
    legalizeEdge(nTriangles-1, graph, triangulation);
}
