#include "drawabletriangulation.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

DrawableTriangulation::DrawableTriangulation(DAG *graph): Triangulation(graph), coloreLinee(), colorePunti(), drawBounding(false), drawVoronoi(false){

}

/**
 * @brief Draws the triangles and the Voronoi edges
 *
 * This method calls the cg3::viewer functions for drawing the edges of the triangles
 * and the edges of the Voronoi graph if requested.
 */
void DrawableTriangulation::draw() const{
    for(unsigned int i =0 ; i < triangulationTriangles.size(); i++){
        if(drawBounding){
            cg3::viewer::drawTriangle2D(DAGtriangles->getPoint(DAGtriangles->getNode(triangulationTriangles[i]).p1()),
                                        DAGtriangles->getPoint(DAGtriangles->getNode(triangulationTriangles[i]).p2()),
                                        DAGtriangles->getPoint(DAGtriangles->getNode(triangulationTriangles[i]).p3()),
                                        coloreLinee, 1);
        }else{
            int currentTriangle=triangulationTriangles[i];
            //Draw only the triangles completely inside the bounding box
            if((DAGtriangles->getNode(currentTriangle).p1()>2)
                    &&(DAGtriangles->getNode(currentTriangle).p2()>2)
                    &&(DAGtriangles->getNode(currentTriangle).p3()>2)){
                cg3::viewer::drawTriangle2D(DAGtriangles->getPoint(DAGtriangles->getNode(triangulationTriangles[i]).p1()),
                                            DAGtriangles->getPoint(DAGtriangles->getNode(triangulationTriangles[i]).p2()),
                                            DAGtriangles->getPoint(DAGtriangles->getNode(triangulationTriangles[i]).p3()),
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

/**
 * @brief Return the center of the object
 */
cg3::Pointd DrawableTriangulation::sceneCenter() const{
    return cg3::Pointd(0,0);
}

/**
 * @brief Return the scene radius
 */
double DrawableTriangulation::sceneRadius() const{
    return 1e+7;
}

/**
 * @brief Set if drawing the bounding triangle is wanted
 * @param value: boolean
 */
void DrawableTriangulation::setDrawBounding(bool value){
    drawBounding=value;
}

/**
 * @brief Set if drawing the Voronoi graph is wanted
 * @param value: boolean
 */
void DrawableTriangulation::setDrawVoronoi(bool value){
    drawVoronoi=value;
}

