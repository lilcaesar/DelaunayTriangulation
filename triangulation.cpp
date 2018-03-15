#include "triangulation.h"

Triangulation::Triangulation()
{

}

bool Triangulation::clearTriangulation(){
    points.clear();
    triangles.clear();
    if(points.empty()&&triangles.empty()){
        return true;
    }
    return false;
}

void Triangulation::insertVertex(const cg3::Point2Dd& point)
{
    points.push_back(point);
}

std::vector<cg3::Point2Dd*> Triangulation::getTriangleVertices(int triangleIndex){
    std::vector<cg3::Point2Dd*> vertices;
    vertices.push_back(&points[triangleIndex*3]);
    vertices.push_back(&points[(triangleIndex*3)+1]);
    vertices.push_back(&points[(triangleIndex*3)+2]);
    return vertices;
}
