#include "drawabletriangulation.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

DrawableTriangulation::DrawableTriangulation(){

}

void DrawableTriangulation::draw() const{
    for(int j=0; j < points.size(); j++){
        cg3::viewer::drawPoint2D(points[j], QColor(), 3);
    }
    /*for(int i = 0; i < triangles.size(); i++){
        cg3::viewer::drawTriangle2D(points[triangles[i]], points[triangles[i+1]], points[triangles[i+2]], QColor());
    }*/
}

cg3::Pointd DrawableTriangulation::sceneCenter() const{
    return cg3::Pointd(0,0);
}

double DrawableTriangulation::sceneRadius() const{
    return 1e+7;
}

