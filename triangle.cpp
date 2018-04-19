#include "triangle.h"
#include <algorithm>

/**
 * @brief Triangle constructor.
 * @param p1: index of the first vertex in the points vector.
 * @param p2: index of the second vertex in the points vector.
 * @param p3: index of the third vertex in the points vector.
 */
Triangle::Triangle(int p1, int p2, int p3) :  p_1(p1), p_2(p2), p_3(p3){
}

/**
 * @brief Get opposite point index given the vertices of one edge.
 * @param point1: first vertex of the edge.
 * @param point2: second vertex of the edge.
 * @return index of the opposite edge.
 */
int Triangle::getOppositePointIndex(const int point1, const int point2) const{
    if((p_1==point1 && p_2==point2)||(p_2==point1 && p_1==point2))
        return 3;
    if((p_2==point1 && p_3==point2)||(p_3==point1 && p_2==point2))
        return 1;
    if((p_3==point1 && p_1==point2)||(p_1==point1 && p_3==point2))
        return 2;
    return -1;
}
