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
#include <QApplication>
#include <QMessageBox>
#include "my_main_window.h"


#include "my_object3d.h"
#include "objects/cube.h"
#include "objects/pyramid.h"

#include "my_objects.h"

#include "my_scene.h"

/**
* Program usage
* Should be handled with the tclap library
*/
void usage(char* name){
  cout<< "usage: " << name << " [options]" <<endl;
  cout<< "options:" <<endl;
  cout<< "  -h, --help                 shows this message" <<endl;
  cout<< "  --off file                 loads OFF file" <<endl;
}

int main(int argc, char *argv[]){
  QApplication app(argc, argv);

  // Parse program arguments here
  // with the tclap library
  // http://tclap.sourceforge.net/manual.html
  //

  // initialize my custom 3D scene
  float objectRadius = 1.;
  QPointer<MyScene> myScene = new MyScene(objectRadius);

  //add simple objects
  try{
      myScene->addObject(new my::FuncSurface(50,50, -3.14, 3.14, -3.14, 3.14, my::FuncSinCos()));
      myScene->addObject(new my::FuncSurface(50,50, -3.14, 3.14, -3.14, 3.14));
//      myScene->addObject(new my::GridCube());
//      myScene->addObject(new my::Grid());
//      myScene->addObject(new my::Cone(2., 26.5, 10, 10, 1));
//      //  myScene->addObject(new my::ConicMesh(2., 26.5, 10, 5));
//      myScene->addObject(new my::Cylinder(2., 1., 10, 10, 1));
//      //  myScene->addObject(new my::CylindricMesh(2., 1., 10, 5));
//      myScene->addObject(new my::Torus(0.6, 0.4, 20, 5));
//      myScene->addObject(new my::Sphere(1., 20, 20));
//      myScene->addObject(new my::Disk(1., 10, 1));
//      myScene->addObject(new my::DiskHole(1., 0.3, 20, 3));
//      myScene->addObject(new my::CubeCorner());
  }
  catch(const std::invalid_argument & e){
      QPointer<QMessageBox> msgbox = new QMessageBox(QMessageBox::Critical, "Exception caught", e.what(), QMessageBox::Ok);
      msgbox->show();
  }

  myScene->addObject(new Cube());
  myScene->addObject(new Pyramid());

  // add surface functions
  // ...

  // add user defined OFF files
  // ...

  // initialize my custom main window
  QPointer<MyMainWindow> myMainWindow = new MyMainWindow(myScene);
  // display the window
  myMainWindow->show();
  // enter in the main loop
  return app.exec();
}

