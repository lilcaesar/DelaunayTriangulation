#include "triangulation.h"

Triangulation::Triangulation()
{

}

bool Triangulation::clearTriangulation(){
    //RIFARE
    if(triangles.empty()){
        return true;
    }
    return false;
}

void Triangulation::insertVertex(const cg3::Point2Dd& point)
{
    points.push_back(point);
}

std::vector<cg3::Point2Dd*> Triangulation::getTriangleVertices(Triangle& triangle){
    std::vector<cg3::Point2Dd*> vertices;
    vertices.push_back(&triangle.p1());
    vertices.push_back(&triangle.p1());
    vertices.push_back(&triangle.p1());
    return vertices;
}
