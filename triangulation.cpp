#include "triangulation.h"

Triangulation::Triangulation(){

}

Triangulation::Triangulation(Triangle *triangle, DAG *graph): DAGtriangles(graph){
    bounding1=triangle->p1();
    bounding2=triangle->p2();
    bounding3=triangle->p3();
    triangulationTriangles.push_back(0);
    triangle->setTriangulationIndex(0);
}

void Triangulation::clearTriangulation(){
    triangulationTriangles.clear();
    points.clear();
    triangulationTriangles.push_back(0);
}

void Triangulation::insertVertex(const cg3::Point2Dd& point)
{
    points.push_back(point);
}

void Triangulation::swap(int oldTriangleIndex, Triangle *newTriangle){
    triangulationTriangles[oldTriangleIndex]= newTriangle->getTriangleDAGIndex();
    newTriangle->setTriangulationIndex(oldTriangleIndex);
}

void Triangulation::addTriangle(Triangle *triangle){
    triangle->setTriangulationIndex(triangulationTriangles.size());
    triangulationTriangles.push_back(triangle->getTriangleDAGIndex());
}
