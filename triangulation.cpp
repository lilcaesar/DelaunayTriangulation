#include "triangulation.h"

Triangulation::Triangulation(DAG *graph): DAGtriangles(graph){
    triangulationTriangles.push_back(0);
}

void Triangulation::clearTriangulation(){
    triangulationTriangles.clear();
}

void Triangulation::initializeBounding(){
    triangulationTriangles.push_back(0);
}

void Triangulation::swap(int oldTriangleIndex, int newTriangle){
    triangulationTriangles[oldTriangleIndex]= newTriangle;
    DAGtriangles->setTriangleTriangulationIndex(newTriangle, oldTriangleIndex);
}

void Triangulation::addTriangle(const Triangle &triangle){
    DAGtriangles->setTriangleTriangulationIndex(triangle.getTriangleDAGIndex(), triangulationTriangles.size());
    triangulationTriangles.push_back(triangle.getTriangleDAGIndex());
}

std::vector<int> Triangulation::getTriangles() const{
    return triangulationTriangles;
}

void Triangulation::computeBisector(const cg3::Point2Dd &p1,  const cg3::Point2Dd &p2, double &a, double &b, double &c) const{
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

cg3::Point2Dd Triangulation::computeCircumcenter(int Triangle) const{
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
