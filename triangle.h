#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>

class Triangle
{
public:
    Triangle();
    cg3::Point2Dd p1() const;
    cg3::Point2Dd p2() const;
    cg3::Point2Dd p3() const;
    Triangle* getSon1() const;
    Triangle* getSon2() const;
    Triangle* getSon3() const;
    bool isLeaf();

private:
    //int triangleIndex;
    const cg3::Point2Dd p_1;
    const cg3::Point2Dd p_2;
    const cg3::Point2Dd p_3;
    std::vector<Triangle*> adjacencies;
    std::vector<Triangle*> sons;
};

#endif // TRIANGLE_H
