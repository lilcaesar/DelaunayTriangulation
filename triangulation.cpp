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
