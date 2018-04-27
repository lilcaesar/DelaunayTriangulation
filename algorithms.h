#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <triangulation.h>
#include <dag.h>

int findTriangle(const cg3::Point2Dd& vertex, const DAG& graph);
void edgeFlip(int triangle1, int triangle2, DAG &graph);
void legalizeEdge(int triangle, DAG& graph, Triangulation &triangulation);
void addNodes(int triangle,const cg3::Point2Dd& newPoint, DAG& graph);
bool insertVertex(const cg3::Point2Dd& newVertex, Triangulation& triangulation, DAG& graph);
void computeBisector(const cg3::Point2Dd &p1, const cg3::Point2Dd &p2, double &a, double &b, double &c);
cg3::Point2Dd computeCircumcenter(int Triangle, DAG &dag);
void computeVoronoiPoints(Triangulation& triangulation, DAG &dag);

#endif // ALGORITHMS_H
