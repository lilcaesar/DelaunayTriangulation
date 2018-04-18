#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>

class Triangle
{
public:

    Triangle(int p1, int p2, int p3, int DAGIndex, int adj1, int adj2, int adj3);

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

    /**
     * @brief Return the index in the DAG vector of the first child
     */
    inline int getChild1() const{
        return children[0];
    }
    /**
     * @brief Return the index in the DAG vector of the second child
     */
    inline int getChild2() const{
        return children[1];
    }
    /**
     * @brief Return the index in the DAG vector of the third child
     */
    inline int getChild3() const{
        return children[2];
    }

    /**
     * @brief Return the index in the DAG vector of the first adjacency
     */
    inline int getAdj1() const{
        return adjacencies[0];
    }

    /**
     * @brief Return the index in the DAG vector of the second adjacency
     */
    inline int getAdj2() const{
        return adjacencies[1];
    }

    /**
     * @brief Return the index in the DAG vector of the third adjacency
     */
    inline int getAdj3() const{
        return adjacencies[2];
    }

    int getOppositePointIndex(const int point1, const int point2) const;
    void addChild(int child);
    void changeAdj(int oldValue, int newValue);
    int getTriangleDAGIndex() const;
    int getTriangleTriangulationIndex() const;
    bool isLeaf() const;
    void setTriangulationIndex(int index);

private:
    int triangleDAGIndex;
    int triangleTriangulationIndex;

    const int p_1;
    const int p_2;
    const int p_3;

    //adj1 is related to p_1-p_2, adj2 to p_2-p_3 and adj3 to p_3-p_1
    std::vector<int> adjacencies;

    std::vector<int> children;
};

#endif // TRIANGLE_H
