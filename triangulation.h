#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <cg3/geometry/2d/point2d.h>
#include <triangle.h>

class Triangulation
{
public:
    Triangulation();
    bool clearTriangulation();
    void insertVertex(const cg3::Point2Dd& point);
    std::vector<cg3::Point2Dd*> getTriangleVertices(int triangleIndex);

protected:
    std::vector<cg3::Point2Dd> points;
    std::vector<Triangle*> triangles;
};

#endif // TRIANGULATION_H
