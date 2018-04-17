#include "drawabletriangulation.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

DrawableTriangulation::DrawableTriangulation(DAG *graph): Triangulation(graph), coloreLinee(), colorePunti(), drawBounding(false), drawVoronoi(false){

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
    if(drawVoronoi){
        for(unsigned int i=0; i<voronoiEdges.size(); i=i+2){
            cg3::viewer::drawLine2D(voronoiEdges[i], voronoiEdges[i+1], QColor(255,0,0),1);
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

void DrawableTriangulation::setDrawVoronoi(bool value){
    drawVoronoi=value;
}

