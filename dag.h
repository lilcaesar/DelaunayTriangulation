#ifndef DAG_H
#define DAG_H

#include <triangle.h>

class DAG
{
public:
    DAG();
    Triangle* getRootTriangle();
    void addNode(Triangle* newNode);

private:
    int nTriangle;
    std::vector<Triangle*> nodes;
};

#endif // DAG_H
