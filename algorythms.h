#ifndef ALGORYTHMS_H
#define ALGORYTHMS_H

#include <triangulation.h>
#include <dag.h>

int findTriangle(const cg3::Point2Dd& vertex,const DAG& graph);
void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph);

#endif // ALGORYTHMS_H
