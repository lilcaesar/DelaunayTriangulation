#include "triangulation.h"

Triangulation::Triangulation(): nTriangles(0){

}

Triangulation::Triangulation(Triangle *triangle): nTriangles(1){
    triangles.push_back(triangle);
    points.push_back(triangle->p1());
    points.push_back(triangle->p2());
    points.push_back(triangle->p3());
}

bool Triangulation::clearTriangulation(){
    triangles.clear();
    points.clear();
    if(triangles.empty()&&points.empty()){
        return true;
    }
    return false;
}

void Triangulation::insertVertex(const cg3::Point2Dd& point)
{
    points.push_back(point);
}

void Triangulation::swap(int oldTriangleIndex, Triangle *newTriangle){
    triangles[oldTriangleIndex]= newTriangle;
    triangles[oldTriangleIndex]->setTriangulationIndex(oldTriangleIndex);
}

void Triangulation::addTriangle(Triangle *triangle){
    triangle->setTriangulationIndex(nTriangles);
    triangles.push_back(triangle);
    nTriangles++;
}
