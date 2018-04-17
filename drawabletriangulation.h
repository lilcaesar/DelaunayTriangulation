#ifndef DRAWABLETRIANGULATION_H
#define DRAWABLETRIANGULATION_H

#include "triangulation.h"
#include <cg3/viewer/interfaces/drawable_object.h>

class DrawableTriangulation : public Triangulation ,public cg3::DrawableObject{
public:

    DrawableTriangulation(DAG *graph);

    //DrawableObject interface methods
    void draw() const;
    cg3::Pointd sceneCenter() const;
    double sceneRadius() const;
    void setDrawBounding(bool value);
    void setDrawVoronoi(bool value);

private:
    QColor coloreLinee;
    QColor colorePunti;
    bool drawBounding;
    bool drawVoronoi;
};

#endif // DRAWABLETRIANGULATION_H
