#include "drawabletriangulation.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

DrawableTriangulation::DrawableTriangulation(): coloreLinee(), colorePunti(){

}

DrawableTriangulation::DrawableTriangulation(Triangle* triangle): Triangulation(triangle), coloreLinee(), colorePunti(){

}

void DrawableTriangulation::draw() const{
    for(int i = 0; i < triangles.size(); i++){
        cg3::viewer::drawTriangle2D(triangles[i]->p1(), triangles[i]->p2(), triangles[i]->p3(), coloreLinee);
    }
}

cg3::Pointd DrawableTriangulation::sceneCenter() const{
    return cg3::Pointd(0,0);
}

double DrawableTriangulation::sceneRadius() const{
    return 1e+7;
}

