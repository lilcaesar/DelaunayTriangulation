#include "algorithms.h"

#include <cg3/core/cg3/geometry/2d/utils2d.h>

Triangle& findTriangle(const cg3::Point2Dd& vertex,const Triangle& triangle) const {

}

void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph){
    int triangleIndex;
    triangulation.insertVertex(newVertex);
    triangleIndex = findTriangle(newVertex, graph);
}
