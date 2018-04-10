#ifndef DELAUNAYMANAGER_H
#define DELAUNAYMANAGER_H

#include <QFrame>

#include <cg3/viewer/mainwindow.h>

#include <cg3/viewer/drawable_objects/2d/drawable_bounding_box2d.h>

#include <dag.h>
#include <drawabletriangulation.h>
#include <algorithms.h>


namespace Ui {
    class DelaunayManager;
}

class DelaunayManager : public QFrame {
    Q_OBJECT

public:

    /* ----- Constructors/destructors ----- */

    explicit DelaunayManager(QWidget *parent = 0);
    ~DelaunayManager();


private:

    /* ----- Private fields ----- */

    //UI fields
    Ui::DelaunayManager *ui;
    cg3::viewer::MainWindow& mainWindow;    

    //It is const because, once defined and initialized, it will never change!
    const cg3::DrawableBoundingBox2D boundingBox;

    DAG dag;
    DrawableTriangulation triangulation;


    /* ----- Private methods ----- */

    void fitScene();


private slots:

    /* ----- UI slots ----- */

    void on_enablePickingCheckBox_stateChanged(int arg1);
    void on_resetScenePushButton_clicked();
    void on_loadPointsPushButton_clicked();

    void on_clearPointsPushButton_clicked();
    void on_showBoundingTriangleCheckBox_stateChanged(int arg1);

    void point2DClicked(const cg3::Point2Dd& p);

    void on_checkTriangulationPushButton_clicked();
    void on_generatePointsFilePushButton_clicked();
};

#endif // DELAUNAYMANAGER_H
