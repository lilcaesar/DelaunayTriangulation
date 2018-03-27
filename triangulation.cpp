#include "triangulation.h"

Triangulation::Triangulation(): nTriangles(0){

}

Triangulation::Triangulation(Triangle *triangle, std::vector<Triangle> *trianglesVector): nTriangles(1), DAGtriangles(trianglesVector){
    triangles.push_back(triangle->getTriangleDAGIndex());
    points.push_back(triangle->p1());
    points.push_back(triangle->p2());
    points.push_back(triangle->p3());
}

Triangulation::~Triangulation(){
}

bool Triangulation::clearTriangulation(){
    triangles.clear();
    points.clear();
    return (triangles.empty()&&points.empty());
}

void Triangulation::insertVertex(const cg3::Point2Dd& point)
{
    points.push_back(point);
}

void Triangulation::swap(int oldTriangleIndex, Triangle *newTriangle){
    triangles[oldTriangleIndex]= newTriangle->getTriangleDAGIndex();
    (*DAGtriangles)[triangles[oldTriangleIndex]].setTriangulationIndex(oldTriangleIndex);
}

void Triangulation::addTriangle(Triangle *triangle){
    triangle->setTriangulationIndex(nTriangles);
    triangles.push_back(triangle->getTriangleDAGIndex());
    nTriangles++;
}
