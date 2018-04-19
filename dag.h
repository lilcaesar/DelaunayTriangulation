#ifndef DAG_H
#define DAG_H

#include <dagnode.h>

class DAG
{
public:
    DAG();
    DAG(cg3::Point2Dd p1, cg3::Point2Dd p2, cg3::Point2Dd p3);

    /**
     * @brief Return a node.
     * @param index
     * @return Node in index position.
     *
     * Given a node DAG index returns the node.
     */
    inline const DagNode &getNode(int index) const{
        return nodes[index];
    }

    /**
     * @brief Return a point
     * @param index
     * @return Point in index position.
     *
     * Given a point index returns the point.
     */
    inline const cg3::Point2Dd &getPoint(int index) const{
        return points[index];
    }

    /**
     * @brief Return the number of triangle nodes in the DAG.
     * @return Integer corresponding to the number of nodes
     */
    inline int getNtriangles() const{
        return nTriangle;
    }

    const DagNode &getRootNode();
    void addNode(DagNode newNode);
    void addPoint(const cg3::Point2Dd& newPoint);
    void changeTriangleAdj(int triangle, int oldValue, int newValue);
    void addNodeChild(int triangle, int child);
    void setTriangleTriangulationIndex(int triangle, int index);
    void clearGraph();
    void initializeBounding();
    std::vector<cg3::Point2Dd> getPoints() const;
    int getNPoints() const;

private:
    cg3::Point2Dd bounding1;
    cg3::Point2Dd bounding2;
    cg3::Point2Dd bounding3;
    std::vector<cg3::Point2Dd> points;
    int nPoints;
    int nTriangle;
    std::vector<DagNode> nodes;
};

#endif // DAG_H
