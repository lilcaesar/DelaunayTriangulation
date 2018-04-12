#include "triangulation.h"

Triangulation::Triangulation(Triangle *triangle, DAG *graph): DAGtriangles(graph){
    triangulationTriangles.push_back(0);
    triangle->setTriangulationIndex(0);
}

void Triangulation::clearTriangulation(){
    triangulationTriangles.clear();
    triangulationTriangles.push_back(0);
}

void Triangulation::swap(int oldTriangleIndex, int newTriangle){
    triangulationTriangles[oldTriangleIndex]= newTriangle;
    DAGtriangles->getTriangle(newTriangle).setTriangulationIndex(oldTriangleIndex);
}

void Triangulation::addTriangle(int triangle){
    DAGtriangles->getTriangle(triangle).setTriangulationIndex(triangulationTriangles.size());
    triangulationTriangles.push_back(triangle);
}

std::vector<int> Triangulation::getTriangles(){
    return triangulationTriangles;
}

void Triangulation::computeBisector(cg3::Point2Dd &p1, cg3::Point2Dd &p2, double &a, double &b, double &c){
    //First compute the equation of the line passing through p1 and p2
    a=p2.y()-p1.y();
    b=p1.x()-p2.x();
    c=a*(p1.x())+b*(p1.y());
    //Then compute its perpendicular passing through the midpoint of p1p2
    double midx=(p1.x()+p2.x())/2;
    double midy=(p1.y()+p2.y())/2;
    double aux=a;
    c=(-b*(midx))+(a*(midy));
    a=-b;
    b=aux;
}

cg3::Point2Dd Triangulation::computeCircumcenter(int Triangle){
    //The circumcenter is the point where all the bisectors intersect
    //in our case the intersection of two bisectors is enough
    double a1,b1,c1,a2,b2,c2;
    computeBisector(DAGtriangles->getPoint(DAGtriangles->getTriangle(Triangle).p1()),
                    DAGtriangles->getPoint(DAGtriangles->getTriangle(Triangle).p2()),a1,b1,c1);
    computeBisector(DAGtriangles->getPoint(DAGtriangles->getTriangle(Triangle).p2()),
                    DAGtriangles->getPoint(DAGtriangles->getTriangle(Triangle).p3()),a2,b2,c2);
    return(cg3::Point2Dd((b2*c1-b1*c2)/(a1*b2-a2*b1),
                         (a1*c2-a2*c1)/(a1*b2-a2*b1)));
}


void Triangulation::computeVoronoiPoints(){
    voronoiEdges.clear();
    for(int i : triangulationTriangles){
        cg3::Point2Dd currentCircumcenter=computeCircumcenter(i);
        if(DAGtriangles->getTriangle(i).getAdj1()!=-1){
            voronoiEdges.push_back(currentCircumcenter);
            voronoiEdges.push_back(computeCircumcenter(DAGtriangles->getTriangle(i).getAdj1()));
        }
        if(DAGtriangles->getTriangle(i).getAdj2()!=-1){
            voronoiEdges.push_back(currentCircumcenter);
            voronoiEdges.push_back(computeCircumcenter(DAGtriangles->getTriangle(i).getAdj2()));
        }
        if(DAGtriangles->getTriangle(i).getAdj3()!=-1){
            voronoiEdges.push_back(currentCircumcenter);
            voronoiEdges.push_back(computeCircumcenter(DAGtriangles->getTriangle(i).getAdj3()));
        }
    }
}

void Triangulation::clearVoronoi(){
    voronoiEdges.clear();
}
