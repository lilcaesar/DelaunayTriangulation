#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>

class Triangle
{
public:

    Triangle(int p1, int p2, int p3);

    /**
     * @brief Return the index in the point vector of the first vertex
     */
    inline int p1() const{
        return p_1;
    }
    /**
     * @brief Return the index in the point vector of the second vertex
     */
    inline int p2() const{
        return p_2;
    }
    /**
     * @brief Return the index in the point vector of the third vertex
     */
    inline int p3() const{
        return p_3;
    }

    int getOppositePointIndex(const int point1, const int point2) const;

private:
    const int p_1;
    const int p_2;
    const int p_3;
};

#endif // TRIANGLE_H
