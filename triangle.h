#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

class Triangle
{
public:
    Triangle();
private:
    int triangleIndex;
    std::vector<Triangle*> adjacencies;
    std::vector<Triangle*> sons;
};

#endif // TRIANGLE_H
