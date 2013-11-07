/**
 * @file   main.cpp
 * @author Bruno Jobard
 * @author Author1
 * @author Author2
 * @date   Sep 2012
 *
 * @brief  Declares an application, a main window and a 3D scene
 *
 *
 */

#include <tclap/CmdLine.h>

#include <QApplication>
#include <QMessageBox>
#include "my_main_window.h"


#include "my_object3d.h"
#include "objects/cube.h"
#include "objects/pyramid.h"

#include "my_objects.h"
#include "utils/isicommandline.h"

#include "my_scene.h"


int main(int argc, char *argv[]){
    TriMesh * off;
    std::vector<std::string> filenames;
    bool noProcedural, noFunctional;

    //parse commandline
    my::IsiCommandLine cmd(argc, argv);
    try{
        cmd.getParams(filenames, noProcedural, noFunctional);
    }
    catch(TCLAP::ArgException &e){
        QPointer<QMessageBox> msgbox = new QMessageBox(QMessageBox::Critical, "Exception caught", e.what(), QMessageBox::Ok);
        msgbox->show();
    }

    QApplication app(argc, argv);

    // initialize custom 3D scene
    float objectRadius = 1.;
    QPointer<MyScene> myScene = new MyScene(objectRadius);

    //add simple objects
    if(!noProcedural){
        try{
            myScene->addObject(new my::IsoSphere(1., 3));
            myScene->addObject(new my::Octahedron());
            myScene->addObject(new my::Cone(2., 26.5, 10, 10, 1));
            myScene->addObject(new my::Cylinder(2., 1., 10, 10, 1));
            myScene->addObject(new my::Torus(0.6, 0.4, 20, 5));
            myScene->addObject(new my::Sphere(1., 20, 20));
            myScene->addObject(new my::Disk(1., 10, 1));
            myScene->addObject(new my::DiskHole(1., 0.3, 20, 3));
            myScene->addObject(new my::CubeCorner(0.5));

            myScene->addObject(new Cube());
            myScene->addObject(new Pyramid());
        }
        catch(const std::invalid_argument & e){
            QPointer<QMessageBox> msgbox = new QMessageBox(QMessageBox::Critical, "Exception caught", e.what(), QMessageBox::Ok);
            msgbox->show();
        }
    }

    // add surface functions
    if(!noFunctional){
        try{
            myScene->addObject(new my::FuncSurface(50,50, -3.14, 3.14, -3.14, 3.14));
            myScene->addObject(new my::FuncSurface(50,50, -3.14, 3.14, -3.14, 3.14, my::FuncSinCos()));
            myScene->addObject(new my::FuncSurface(50,50, -2, 2, -2, 2, my::FuncParabolic()));
        }
        catch(const std::invalid_argument & e){
            QPointer<QMessageBox> msgbox = new QMessageBox(QMessageBox::Critical, "Exception caught", e.what(), QMessageBox::Ok);
            msgbox->show();
        }
    }

    // add user defined OFF files
    try{
        for(int i=0; i < filenames.size(); ++i){
            off = new TriMesh(filenames[i]);
            off->loadOffFile(filenames[i]);
            myScene->addObject(off);
        }
    }
    catch(const std::exception & e){
        QPointer<QMessageBox> msgbox = new QMessageBox(QMessageBox::Critical, "Exception caught", e.what(), QMessageBox::Ok);
        msgbox->show();
    }

    // initialize my custom main window
    QPointer<MyMainWindow> myMainWindow = new MyMainWindow(myScene);
    // display the window
    myMainWindow->show();
    // enter in the main loop
    return app.exec();
}

