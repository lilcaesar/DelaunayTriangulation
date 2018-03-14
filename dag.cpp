#include "dag.h"

DAG::DAG(): nTriangle(0)
{
}

Triangle* DAG::getRootTriangle(){
    return nodes[0];
}

void DAG::addNode(Triangle* newNode){
    nTriangle++;
    nodes.push_back(newNode);
}
