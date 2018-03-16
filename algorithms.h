#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <triangulation.h>
#include <dag.h>

Triangle* findTriangle(const cg3::Point2Dd& vertex,Triangle* triangle);
void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph);

#endif // ALGORITHMS_H
