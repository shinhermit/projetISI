#include "configurator.h"

const std::string my::Configurator::_defaultConfig =
        std::string("--cone --cone-height 1. --cone-aperture 26.5 --cone-slices 10 --cone-stacks 5 --cone-basediv 1 ")+
        std::string("--cylinder --cylinder-height 2. --cylinder-radius 1 --cylinder-slices 10 --cylinder-stacks 5 --cylinder-basediv 1 ")+
        std::string("--disk --disk-radius 1. --disk-slices 10 --disk-circ-div 1 --disk-center-x 0 --disk-center-y 0 --disk-center-z 0 ")+
        std::string("--diskhole --diskh-small-radius .3 --diskh-big-radius 1. --diskh-slices 10 --diskh-circ-div 1 --diskh-center-x 0 --diskh-center-y 0 --diskh-center-z 0 ")+
        std::string("--funcsurface --func expcos --func-sample-x 50 --func-sample-y 50 --func-min-x -3.14 --func-max-x 3.14 --func-min-y -3.14 --func-max-y 3.14 ")+
        std::string("--funcsurface --func sincos --func-sample-x 50 --func-sample-y 50 --func-min-x -3.14 --func-max-x 3.14 --func-min-y -3.14 --func-max-y 3.14 ")+
        std::string("--sphere --sphere-radius 1. --sphere-slices 2 --sphere-stacks 2 ")+
        std::string("--torus --torus-path-radius 0.6 --torus-tube-radius 0.4 --torus-slices 20 --torus-stacks 5 ")+
        std::string("--cubecorner --cubecorner-spread 0.5 ")+
        std::string("--off Venus ")+
        std::string("--off Tref ")+
        std::string("--off Abstr ")+
        std::string("--off Hdodec ")+
        std::string("--no-cube ")+
        std::string("--no-pyramid ")
        ;

const std::string my::Configurator::_defaultConfigFile = "isiproject.jconf";

my::Configurator::Configurator(const std::string & argv)
{
    TCLAP::CmdLine cmd("Isi project Command line options - by Josuah Aron", ' ', "1.5");

    //charger un fichier de config
    TCLAP::ValueArg<std::string> configFileName("","config","Location of a config file",false,"","string", cmd);

    /***** exclusions  (switch --no-) *****/
    //exclure un type d'objet
    TCLAP::SwitchArg noProcedural("","no-procedural","Exclude procedural meshes from scene", cmd, false);
    TCLAP::SwitchArg noFunctional("","no-functional","Exclude functional meshes from scene", cmd, false);
    TCLAP::SwitchArg noOff("","no-off","Exclude off file loaded meshes from scene", cmd, false);

    //exclure un objet: --no-sphere --no-torus --no-cubecorner
    TCLAP::SwitchArg noCone("","no-cone","Exclude object Cone from scene", cmd, false);
    TCLAP::SwitchArg noCylinder("","no-cylinder","Exclude object Cylinder from scene", cmd, false);
    TCLAP::SwitchArg noDisk("","no-disk","Exclude object Disk from scene", cmd, false);
    TCLAP::SwitchArg noDiskhole("","no-diskhole","Exclude object DiskHole from scene", cmd, false);
    TCLAP::SwitchArg noSphere("","no-sphere","Exclude object Sphere from scene", cmd, false);
    TCLAP::SwitchArg noTorus("","no-torus","Exclude object Torus from scene", cmd, false);
    TCLAP::SwitchArg noCubecorner("","no-cubecorner","Exclude object CubeCorner from scene", cmd, false);
    TCLAP::SwitchArg noCube("","no-cube","Exclude object Cube from scene", cmd, true);
    TCLAP::SwitchArg noPyramid("","no-pyramid","Exclude object Pyramid from scene", cmd, true);

    /***** paramètres des objets *****/
    //Cone
    TCLAP::SwitchArg cone("","cube","Include object Cone in Scene", cmd, true);
    TCLAP::ValueArg<float> coneHeight("","cone-height","Height of the Cone in the scene",false,2.,"float", cmd);
    TCLAP::ValueArg<float> coneAperture("","cone-aperture","Aperture angle of the Cone in the scene",false,26.5,"float", cmd);
    TCLAP::ValueArg<int> coneSlices("","cone-slices","Number of vertical slices of the Cone in the scene",false,10,"int", cmd);
    TCLAP::ValueArg<int> coneStacks("","cone-stacks","Number of horizontal stacks of the Cone in the scene",false,5,"int", cmd);
    TCLAP::ValueArg<int> coneBaseDiv("","cone-basediv","Number of circular division of the base disk of the Cone in the scene",false,1,"int", cmd);

    //cylinder
    TCLAP::SwitchArg cylinder("","cylinder","Include object Cylinder in Scene", cmd, true);
    TCLAP::ValueArg<float> cylinderHeight("","cylinder-height","Height of the Cylinder in the scene",false,2.,"float", cmd);
    TCLAP::ValueArg<float> cylinderRadius("","cylinder-radius","Radius of the Cylinder in the scene",false,1.,"float", cmd);
    TCLAP::ValueArg<int> cylinderSlices("","cylinder-slices","Number of vertical slices of the Cylinder in the scene",false,10,"int", cmd);
    TCLAP::ValueArg<int> cylinderStacks("","cylinder-stacks","Number of horizontal stacks of the Cylinder in the scene",false,5,"int", cmd);
    TCLAP::ValueArg<int> cylinderBaseDiv("","cylinder-basediv","Number of circular division of the base disk of the Cylinder in the scene",false,1,"int", cmd);

    //disk
    TCLAP::SwitchArg disk("","disk","Include object Disk in Scene", cmd, true);
    TCLAP::ValueArg<float> diskRadius("","disk-radius","Radius of the Disk in the scene",false,1.,"float", cmd);
    TCLAP::ValueArg<int> diskSlices("","disk-slices","Number of vertical slices of the Disk in the scene",false,10,"int", cmd);
    TCLAP::ValueArg<int> diskCircDiv("","disk-basediv","Number of circular division of the Disk in the scene",false,1,"int", cmd);
    TCLAP::ValueArg<float> diskCenterX("","disk-center-x","x-coordinate of the center of the Disk in the scene",false,0.,"int", cmd);
    TCLAP::ValueArg<float> diskCenterY("","disk-center-y","y-coordinate of the center of the Disk in the scene",false,0.,"int", cmd);
    TCLAP::ValueArg<float> diskCenterZ("","disk-center-z","z-coordinate of the center of the Disk in the scene",false,0.,"int", cmd);

    //diskhole
    TCLAP::SwitchArg diskhole("","diskhole","Include object DiskHole in Scene", cmd, true);
    TCLAP::ValueArg<float> diskhSmallRadius("","diskh-small-radius","Small radius of the Disk in the scene",false,.3,"float", cmd);
    TCLAP::ValueArg<float> diskhBigRadius("","diskh-big-radius","Big radius of the Disk in the scene",false,1.,"float", cmd);
    TCLAP::ValueArg<int> diskhSlices("","diskh-slices","Number of vertical slices of the Disk in the scene",false,10,"int", cmd);
    TCLAP::ValueArg<int> diskhCircDiv("","diskh-basediv","Number of circular division of the Disk in the scene",false,1,"int", cmd);
    TCLAP::ValueArg<float> diskhCenterX("","diskh-center-x","x-coordinate of the center of the Disk in the scene",false,0.,"int", cmd);
    TCLAP::ValueArg<float> diskhCenterY("","diskh-center-y","y-coordinate of the center of the Disk in the scene",false,0.,"int", cmd);
    TCLAP::ValueArg<float> diskhCenterZ("","diskh-center-z","z-coordinate of the center of the Disk in the scene",false,0.,"int", cmd);

    //sphere
    TCLAP::SwitchArg sphere("","sphere","Include object Sphere in Scene", cmd, true);
    TCLAP::ValueArg<float> sphereRadius("","sphere-radius","Radius of the Sphere in the scene",false,1.,"float", cmd);
    TCLAP::ValueArg<int> sphereSlices("","sphere-slices","Number of vertical slices of the Sphere in the scene",false,10,"int", cmd);
    TCLAP::ValueArg<int> sphereStacks("","sphere-stacks","Number of horizontal stacks of the Sphere in the scene",false,10,"int", cmd);

    //torus
    TCLAP::SwitchArg torus("","torus","Include object Torus in Scene", cmd, true);
    TCLAP::ValueArg<float> torusPathRadius("","torus-path-radius","Radius of path of the Torus in the scene",false,.6,"float", cmd);
    TCLAP::ValueArg<float> torusTubeRadius("","torus-tube-radius","Radius of the tube of the Torus in the scene",false,.4,"float", cmd);
    TCLAP::ValueArg<int> torusSlices("","torus-slices","Number of vertical slices of the Torus in the scene",false,20,"int", cmd);
    TCLAP::ValueArg<int> torusStacks("","torus-stacks","Number of horizontal stacks of the Torus in the scene",false,5,"int", cmd);

    //cubecorner
    TCLAP::SwitchArg cubecorner("","cubecorner","Include object CubeCorner in Scene", cmd, true);
    TCLAP::ValueArg<float> cornerSpread("","cubecorner-spread","Spread of the corned vertice of the CubeCorner int the Scene",false,.5,"float", cmd);

    //cube
    TCLAP::SwitchArg cube("","cube","Include object Cube in Scene", cmd, false);

    //pyramid
    TCLAP::SwitchArg pyramid("","pyramid","Include object Pyramid in Scene", cmd, false);

    //funcsurface
    TCLAP::SwitchArg funcsurface("","funcsurface","Include object FuncSurface in Scene", cmd, true);
    //multiswitch à valeurs limitées !!!
    TCLAP::MultiArg<std::string> torusSlices("","torus-slices","Number of vertical slices of the Torus in the scene",false,20,"int", cmd);
    TCLAP::ValueArg<int> torusSlices("","torus-slices","Number of vertical slices of the Torus in the scene",false,20,"int", cmd);
    TCLAP::ValueArg<int> torusSlices("","torus-slices","Number of vertical slices of the Torus in the scene",false,20,"int", cmd);
    TCLAP::ValueArg<float> torusPathRadius("","torus-path-radius","Radius of path of the Torus in the scene",false,.6,"float", cmd);
    TCLAP::ValueArg<float> torusPathRadius("","torus-path-radius","Radius of path of the Torus in the scene",false,.6,"float", cmd);
    TCLAP::ValueArg<float> torusPathRadius("","torus-path-radius","Radius of path of the Torus in the scene",false,.6,"float", cmd);
    TCLAP::ValueArg<float> torusPathRadius("","torus-path-radius","Radius of path of the Torus in the scene",false,.6,"float", cmd);
    std::string("--funcsurface --func expcos --func-sample-x 50 --func-sample-y 50 --func-min-x -3.14 --func-max-x 3.14 --func-min-y -3.14 --func-max-y 3.14 ");
    std::string("--funcsurface --func sincos --func-sample-x 50 --func-sample-y 50 --func-min-x -3.14 --func-max-x 3.14 --func-min-y -3.14 --func-max-y 3.14 ");

    //off
    TCLAP::MultiArg<std::string> off("", "off", "Specify an OFF file to load a mesh from", false, 20, "string", cmd);
}
