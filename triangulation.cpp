#include "triangulation.h"

Triangulation::Triangulation(Triangle *triangle, DAG *graph): DAGtriangles(graph){
    triangulationTriangles.push_back(0);
    triangle->setTriangulationIndex(0);
}

void Triangulation::clearTriangulation(){
    triangulationTriangles.clear();
    triangulationTriangles.push_back(0);
}

void Triangulation::swap(int oldTriangleIndex, int newTriangle){
    triangulationTriangles[oldTriangleIndex]= newTriangle;
    DAGtriangles->getTriangle(newTriangle).setTriangulationIndex(oldTriangleIndex);
}

void Triangulation::addTriangle(int triangle){
    DAGtriangles->getTriangle(triangle).setTriangulationIndex(triangulationTriangles.size());
    triangulationTriangles.push_back(triangle);
}

std::vector<int> Triangulation::getTriangles(){
    return triangulationTriangles;
}
