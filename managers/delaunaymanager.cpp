#include "delaunaymanager.h"
#include "ui_delaunaymanager.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

#include <ctime>

#include "utils/fileutils.h"
#include "utils/delaunay_checker.h"

#include <cg3/data_structures/arrays/arrays.h>
#include <cg3/utilities/timer.h>

#include<algorithm> //std::random_shuffle


//Limits for the bounding box
//It defines where points can be added
const double BOUNDINGBOX = 1e+6;
const double SCENERADIUS = BOUNDINGBOX;
const cg3::Pointd SCENECENTER(0,0,0);


//Coordinates of the bounding triangle.
//Use these coordinates to initialize the bounding triangle
//of your triangulation.
//Do not change these coordinates, they are made to avoid
//numeric errors with the test input files.
const cg3::Point2Dd BT_P1(1e+10, 0);
const cg3::Point2Dd BT_P2(0, 1e+10);
const cg3::Point2Dd BT_P3(-1e+10, -1e+10);




/* ----- Constructors/Destructors ----- */

/**
 * @brief Default constructor of the manager
 */
DelaunayManager::DelaunayManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DelaunayManager),
    mainWindow((cg3::viewer::MainWindow&)*parent),
    boundingBox(cg3::Point2Dd(-BOUNDINGBOX, -BOUNDINGBOX),
                cg3::Point2Dd(BOUNDINGBOX, BOUNDINGBOX)),
    dag(BT_P1, BT_P2, BT_P3),
    triangulation(&dag.getRootTriangle(), &dag)
{
    //UI setup
    ui->setupUi(this);
    connect(&mainWindow, SIGNAL(point2DClicked(cg3::Point2Dd)), this, SLOT(point2DClicked(cg3::Point2Dd)));

    //Setting options to use the canvas
    mainWindow.disableRotation();
    mainWindow.setSelectLeftButton();

    //Add the drawable object to the mainWindow.
    //The mainWindow will take care of the rendering of the bounding box
    mainWindow.pushObj(&boundingBox, "Bounding box");
    mainWindow.pushObj(&triangulation, "Triangulation");

    //This updates the canvas (call it whenever you change or
    //add some drawable object)
    mainWindow.updateGlCanvas();

    fitScene();
}


/**
 * @brief Destructor of the manager
 */
DelaunayManager::~DelaunayManager() {
    //In case you allocated dynamic objects in this manager, you
    //should delete (deallocate) all of them when the application
    //closes.
    //Remember that each class which allocates dynamic objects
    //should implement a destructor which deallocates them.
    /******/

    /******/

    //When the manager is destroyed, the mainWindow should
    //not have any reference to drawable objects.
    /******/

    /******/

    //Delete the bounding box drawable object
    mainWindow.deleteObj(&boundingBox);
    mainWindow.deleteObj(&triangulation);

    delete ui;
}



/* ----- Private methods ----- */

/**
 * @brief Change camera of the canvas to fit the scene
 * on the bounding box in which the points can be added.
 */
void DelaunayManager::fitScene() {
    //Do not write code here
    mainWindow.fitScene(SCENECENTER, SCENERADIUS);
}



/* ----- UI slots ----- */


/**
 * @brief Enable picking checkbox handler.
 *
 * Checkbox to enable/disable the point clicking on the canvas.
 *
 * @param[in] arg1 It contains Qt::Checked if the checkbox is checked,
 * Qt::Unchecked otherwise
 */
void DelaunayManager::on_enablePickingCheckBox_stateChanged(int arg1) {
    //Do not write code here
    if (arg1 == Qt::Checked){
        mainWindow.setSelectLeftButton();
    }
    else {
        mainWindow.disableRotation();
    }
}

/**
 * @brief Reset scene event handler.
 *
 * It allows us to reset the camera of the canvas to
 * show/center the scene in the bounding box.
 */
void DelaunayManager::on_resetScenePushButton_clicked() {
    //Do not write code here
    fitScene();
}





/**
 * @brief Clear points button event handler.
 *
 * It allows us to clear our triangulation.
 */
void DelaunayManager::on_clearPointsPushButton_clicked() {

    //Clear here your triangulation
    /******/
    triangulation.clearTriangulation();
    dag.clearGraph();
    /******/


    //Remove the triangulation drawable object from the
    //canvas (mainWindow.deleteObj() which takes a reference).
    //Deallocate if necessary (you allocated it dynamically).
    /****/

    /****/

    mainWindow.updateGlCanvas(); //Canvas update
    ui->timeLabel->setText("");
}


/**
 * @brief Show bounding triangle checkbox event handler.
 *
 * It allows us to choose if bounding triangle should be drawn or not.
 *
 * @param[in] arg1 It contains Qt::Checked if the checkbox is checked,
 * Qt::Unchecked otherwise
 */
void DelaunayManager::on_showBoundingTriangleCheckBox_stateChanged(int arg1) {

    //If arg1 is Qt::Checked, then you must set the drawable triangulation
    //to draw the bounding triangle as well
    /******/
    triangulation.setDrawBounding(false);
    if (arg1 == Qt::Checked) {
        triangulation.setDrawBounding(true);
    }

    /******/

    mainWindow.updateGlCanvas(); //Canvas update
}

/**
 * @brief Load point event handler.
 *
 * Load input points from a file.
 */
void DelaunayManager::on_loadPointsPushButton_clicked() {
    //File selector
    QString filename = QFileDialog::getOpenFileName(nullptr,
                       "Open points",
                       ".",
                       "*.txt");

    if (!filename.isEmpty()) {

        //Clear here your triangulation
        /******/
        triangulation.clearTriangulation();
        dag.clearGraph();
        /******/

        std::vector<cg3::Point2Dd> points = FileUtils::getPointsFromFile(filename.toStdString());
        cg3::Timer t("Delaunay Triangulation");

        //Launch your triangulation algorithm here
        /****/

        std::random_shuffle(points.begin(), points.end());
        for(cg3::Point2Dd p : points){
            insertVertex(p, triangulation, dag);
        }
        /****/

        t.stopAndPrint();
        ui->timeLabel->setNum(t.delay());

        //Draw your triangulation here
        /****/

        /****/

        mainWindow.updateGlCanvas(); //Canvas update
    }
}

/**
 * @brief Point 2D clicked handler.
 *
 * This method is called whenever the user clicks the canvas.
 * The coordinates (x and y) of the clicked point are given by
 * the 2D point p.
 *
 * @param[in] p Point clicked
 */
void DelaunayManager::point2DClicked(const cg3::Point2Dd& p) {
    if (!boundingBox.isInside(p)) {
        //Error message if the point is not inside the bounding box
        QMessageBox::warning(this, "Cannot insert point", "Point [" +
                             QString::number(p.x()) + "," + QString::number(p.y()) +
                             "] is not contained in the bounding box.");
        return;
    }
    else {
        //Comment the next line, the following is a debug message
        /*QMessageBox::information(this, "Point clicked", "Point [" +
                                 QString::number(p.x()) + "," + QString::number(p.y()) +
                                 "].");*/

        //Manage here the insertion of the point inside the triangulation
        /******/
        insertVertex(p, triangulation, dag);
        /******/

    }

    mainWindow.updateGlCanvas();
}


/**
 * @brief Check triangulation event handler.
 *
 * It allows us to check if the triangulation is a Delaunay one.
 */
void DelaunayManager::on_checkTriangulationPushButton_clicked() {
    std::vector<cg3::Point2Dd> points;
    cg3::Array2D<unsigned int> triangles;

    //Get your triangulation here and save the data in the vector of
    //points and in the matrix of triangles (respectively "points" and
    //"triangles").
    //"points" is a vector which contains all the points of the triangulation.
    //"triangle" is a 2D matrix with n rows (n = number of triangles) and
    //3 columns.
    //The i-th row represents the i-th triangle, which is composed of three
    //unsigned integers which are the indices of the points in the vector
    //"points" that belong to the i-th triangle. Note that the points of each
    //triangle must be in counter-clockwise order.
    //You should initially resize the matrix "triangles" by calling
    //triangles.resize(n, 3), and then fill the matrix using the
    //assignment operator: triangles(i,j) = a;
    /****/
    points=dag.getPoints();
    std::vector<int> indices = triangulation.getTriangles();
    triangles.resize(indices.size(),3);
    for(unsigned int i=0; i < indices.size(); i++){
        triangles(i,0)=dag.getTriangle(indices[i]).p1();
        triangles(i,1)=dag.getTriangle(indices[i]).p2();
        triangles(i,2)=dag.getTriangle(indices[i]).p3();
    }
    /****/

    if (points.size() > 0) {
        if (DelaunayTriangulation::Checker::isDeulaunayTriangulation(points, triangles)) {
            QMessageBox::information(this, "Triangulation checking", "Success: it is a Delaunay triangulation!");
        }
        else {
            QMessageBox::warning(this, "Triangulation checking", "Error: it is NOT a Delaunay triangulation!");
        }
    }
}

/**
 * @brief Generate random points handler.
 *
 * With this button we can generate files that contains
 * points which are inside the bounding box.
 */
void DelaunayManager::on_generatePointsFilePushButton_clicked() {
    //Do not write code here
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(nullptr,
                       "File containing points",
                       ".",
                       "TXT(*.txt)", &selectedFilter);

    if (!filename.isEmpty()){
        int number = QInputDialog::getInt(this, tr("Generate file"),
                                                 tr("Number of random points:"), 1000, 0, 1000000000, 1);

        //Generate points and save them in the chosen file
        FileUtils::generateRandomPointFile(filename.toStdString(), BOUNDINGBOX, number);
    }
}
