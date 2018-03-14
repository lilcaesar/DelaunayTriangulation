#include "algorythms.h"

#include <cg3/core/cg3/geometry/2d/utils2d.h>

int findTriangle(const cg3::Point2Dd& vertex, Triangulation& triangulation,const DAG& graph){
    Triangle* triangle=graph.getRootTriangle();
    while(!cg3::isPointLyingInTriangle(
              ))
}

void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph){
    int triangleIndex;
    triangulation.insertVertex(newVertex);
    triangleIndex = findTriangle(newVertex, graph);
}
