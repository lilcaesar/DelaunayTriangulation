#include "triangulation.h"

/**
 * @brief Triangulation constructor.
 * @param graph: The pointer to the associated DAG.
 */
Triangulation::Triangulation(DAG *graph): DAGtriangles(graph){
    triangulationTriangles.push_back(0);
}

/**
 * @brief Clear the triangulation vector.
 */
void Triangulation::clearTriangulation(){
    triangulationTriangles.clear();
}

/**
 * @brief Initialize the triangulation vector with the index of the bounding triangle.
 */
void Triangulation::initializeBounding(){
    triangulationTriangles.push_back(0);
}

/**
 * @brief Swap the value of a index of the triangulation vector.
 * @param oldTriangleIndex.
 * @param newTriangle.
 */
void Triangulation::swap(int oldTriangleIndex, int newTriangle){
    triangulationTriangles[oldTriangleIndex]= newTriangle;
    DAGtriangles->setTriangleTriangulationIndex(newTriangle, oldTriangleIndex);
}

/**
 * @brief Add a triangle to the triangulation
 * @param triangle: A Triangle object.
 *
 * Adds a new triangle to the triangulation and sets the triangulation index of the triangle.
 */
void Triangulation::addTriangle(const DagNode &triangle){
    DAGtriangles->setTriangleTriangulationIndex(triangle.getTriangleDAGIndex(), triangulationTriangles.size());
    triangulationTriangles.push_back(triangle.getTriangleDAGIndex());
}

/**
 * @brief Return the vector of triangulation indices
 */
std::vector<int> Triangulation::getTriangles() const{
    return triangulationTriangles;
}

/**
 * @brief Computes the equation variables for the bisector of a segment.
 * @param p1: First point of the segment.
 * @param p2: Second point of the segment.
 * @param a: First equation variable.
 * @param b: Second equation variable.
 * @param c: Third equation variable.
 *
 * The method set a, b and c (as in ax+by=c) corresponding to the bisector of p1p2.
 */
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

/**
 * @brief Compute the circumcenter of a triangle.
 * @param Triangle: DAG index of the triangle.
 * @return Point associated with the circumcenter of the input triangle.
 *
 * This method computes the bisector of two edges of the triangle first
 * and returns the intersection point of the two bisectors.
 */
cg3::Point2Dd Triangulation::computeCircumcenter(int Triangle) const{
    //The circumcenter is the point where all the bisectors intersect
    //in our case the intersection of two bisectors is enough
    double a1,b1,c1,a2,b2,c2;
    computeBisector(DAGtriangles->getPoint(DAGtriangles->getNode(Triangle).p1()),
                    DAGtriangles->getPoint(DAGtriangles->getNode(Triangle).p2()),a1,b1,c1);
    computeBisector(DAGtriangles->getPoint(DAGtriangles->getNode(Triangle).p2()),
                    DAGtriangles->getPoint(DAGtriangles->getNode(Triangle).p3()),a2,b2,c2);
    return(cg3::Point2Dd((b2*c1-b1*c2)/(a1*b2-a2*b1),
                         (a1*c2-a2*c1)/(a1*b2-a2*b1)));
}

/**
 * @brief Compute the Voronoi graph from the triangulation.
 *
 * The method fills the voronoiEdges vector with couples of points associated to the edges of the
 * Voronoi graph itself. The for loop computes the edges from the circumcenter of each triangle
 * in the triangulation vector to the circumcenter of the adjacent triangles.
 */
void Triangulation::computeVoronoiPoints(){
    voronoiEdges.clear();
    for(int i : triangulationTriangles){
        cg3::Point2Dd currentCircumcenter=computeCircumcenter(i);
        if(DAGtriangles->getNode(i).getAdj1()!=-1){
            voronoiEdges.push_back(currentCircumcenter);
            voronoiEdges.push_back(computeCircumcenter(DAGtriangles->getNode(i).getAdj1()));
        }
        if(DAGtriangles->getNode(i).getAdj2()!=-1){
            voronoiEdges.push_back(currentCircumcenter);
            voronoiEdges.push_back(computeCircumcenter(DAGtriangles->getNode(i).getAdj2()));
        }
        if(DAGtriangles->getNode(i).getAdj3()!=-1){
            voronoiEdges.push_back(currentCircumcenter);
            voronoiEdges.push_back(computeCircumcenter(DAGtriangles->getNode(i).getAdj3()));
        }
    }
}

/**
 * @brief Clear the Voronoi graph.
 */
void Triangulation::clearVoronoi(){
    voronoiEdges.clear();
}
