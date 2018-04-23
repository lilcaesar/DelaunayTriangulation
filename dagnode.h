#ifndef DAGNODE_H
#define DAGNODE_H

#include <vector>
#include <cg3/geometry/2d/point2d.h>
#include "triangle.h"

class DagNode: public Triangle{
public:
    DagNode(int p1, int p2, int p3, int DAGIndex, int adj1, int adj2, int adj3);

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

    void addChild(int child);
    void changeAdj(int oldValue, int newValue);
    int getTriangleDAGIndex() const;
    int getTriangulationIndex() const;
    bool isLeaf() const;
    void setTriangulationIndex(int index);

private:
    int triangleDAGIndex;
    int triangulationIndex;

    //adj1 is related to p_1-p_2, adj2 to p_2-p_3 and adj3 to p_3-p_1
    std::vector<int> adjacencies;

    std::vector<int> children;
};

#endif // DAGNODE_H
