#include "drawabletriangulation.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

DrawableTriangulation::DrawableTriangulation(Triangle* triangle, DAG *graph): Triangulation(triangle, graph), coloreLinee(), colorePunti(), drawBounding(false){

}

void DrawableTriangulation::draw() const{
    for(unsigned int i =0 ; i < triangulationTriangles.size(); i++){
        if(drawBounding){
            cg3::viewer::drawTriangle2D(DAGtriangles->getPoint(DAGtriangles->getTriangle(triangulationTriangles[i]).p1()),
                                        DAGtriangles->getPoint(DAGtriangles->getTriangle(triangulationTriangles[i]).p2()),
                                        DAGtriangles->getPoint(DAGtriangles->getTriangle(triangulationTriangles[i]).p3()),
                                        coloreLinee, 1);
        }else{
            int currentTriangle=triangulationTriangles[i];
            if((DAGtriangles->getTriangle(currentTriangle).p1()>2)
                    &&(DAGtriangles->getTriangle(currentTriangle).p2()>2)
                    &&(DAGtriangles->getTriangle(currentTriangle).p3()>2)){
                cg3::viewer::drawTriangle2D(DAGtriangles->getPoint(DAGtriangles->getTriangle(triangulationTriangles[i]).p1()),
                                            DAGtriangles->getPoint(DAGtriangles->getTriangle(triangulationTriangles[i]).p2()),
                                            DAGtriangles->getPoint(DAGtriangles->getTriangle(triangulationTriangles[i]).p3()),
                                            coloreLinee, 1);
            }
        }
    }
}

cg3::Pointd DrawableTriangulation::sceneCenter() const{
    return cg3::Pointd(0,0);
}

double DrawableTriangulation::sceneRadius() const{
    return 1e+7;
}

void DrawableTriangulation::setDrawBounding(bool value){
    drawBounding=value;
}

bool DrawableTriangulation::getDrawBounding(){
    return drawBounding;
}

