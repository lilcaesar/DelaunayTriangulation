#include "drawabletriangulation.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

DrawableTriangulation::DrawableTriangulation(Triangle* triangle, DAG *graph): Triangulation(triangle, graph), coloreLinee(), colorePunti(){

}

void DrawableTriangulation::draw() const{
    cg3::viewer::drawTriangle2D(bounding1, bounding2, bounding3, coloreLinee, 1);
    for(unsigned int i =0 ; i < triangulationTriangles.size(); i++){
        cg3::viewer::drawTriangle2D(DAGtriangles->getTriangle(triangulationTriangles[i]).p1(),
                                    DAGtriangles->getTriangle(triangulationTriangles[i]).p2(),
                                    DAGtriangles->getTriangle(triangulationTriangles[i]).p3(),
                                    coloreLinee, 1);
    }
}

cg3::Pointd DrawableTriangulation::sceneCenter() const{
    return cg3::Pointd(0,0);
}

double DrawableTriangulation::sceneRadius() const{
    return 1e+7;
}

