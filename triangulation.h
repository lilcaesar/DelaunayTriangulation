#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <cg3/geometry/2d/point2d.h>

class Triangulation
{
public:
    Triangulation();

protected:
    std::vector<cg3::Point2Dd> points;
    std::vector<unsigned int> triangles;

    int pNum, tNum;
};

#endif // TRIANGULATION_H
