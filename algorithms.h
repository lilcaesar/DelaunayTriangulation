#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <triangulation.h>
#include <dag.h>

int findTriangle(const cg3::Point2Dd& vertex,Triangle* triangle);
void legalizeEdge(Triangle* triangle, DAG& graph, Triangulation &triangulation);
void insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph);

#endif // ALGORITHMS_H
