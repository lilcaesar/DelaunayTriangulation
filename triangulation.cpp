#include "triangulation.h"

Triangulation::Triangulation(Triangle *triangle, DAG *graph): DAGtriangles(graph){
    bounding1=triangle->p1();
    bounding2=triangle->p2();
    bounding3=triangle->p3();
    triangulationTriangles.push_back(0);
    triangle->setTriangulationIndex(0);
    points.push_back(bounding1);
    points.push_back(bounding2);
    points.push_back(bounding3);
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

void Triangulation::getPoints(std::vector<cg3::Point2Dd>* checkerArray){
    checkerArray->push_back(bounding1);
    checkerArray->push_back(bounding2);
    checkerArray->push_back(bounding3);
    for(cg3::Point2Dd p : points){
        checkerArray->push_back(p);
    }
}

void Triangulation::getTriangles(cg3::Array2D<unsigned int>* checkerArray){
    checkerArray->resize(triangulationTriangles.size(), 3);
    for(unsigned int i=0; i<triangulationTriangles.size(); i++){
    }
}
