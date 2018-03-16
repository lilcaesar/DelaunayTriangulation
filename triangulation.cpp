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
    //points.push_back(point);
}
