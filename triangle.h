#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>

class Triangle
{
public:
    Triangle();
    cg3::Point2Dd* p1() const;
    cg3::Point2Dd* p2() const;
    cg3::Point2Dd* p3() const;
private:
    int triangleIndex;
    const cg3::Point2Dd p1;
    const cg3::Point2Dd p2;
    const cg3::Point2Dd p3;
    std::vector<Triangle*> adjacencies;
    std::vector<Triangle*> sons;
};

#endif // TRIANGLE_H
