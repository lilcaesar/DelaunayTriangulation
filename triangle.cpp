#include "triangle.h"

Triangle::Triangle()
{

}

cg3::Point2Dd Triangle::p1() const{
    return p_1;
}

cg3::Point2Dd Triangle::p2() const{
    return p_2;
}

cg3::Point2Dd Triangle::p3() const{
    return p_3;
}

Triangle* Triangle::getSon1() const{
    return sons[0];
}

Triangle* Triangle::getSon2() const{
    return sons[1];
}

Triangle* Triangle::getSon3() const{
    return sons[2];
}

bool Triangle::isLeaf(){
    return sons.empty();
}
