#include "isicommandline.h"

my::IsiCommandLine::IsiCommandLine(const int & argc, const char *const*argv)
    :_argc(argc),
      _argv(argv)
{}

void my::IsiCommandLine::getParams(std::vector<std::string> & filenames, bool & noProcedural, bool & noFunctional)
{
    TCLAP::CmdLine cmd("Isi project Command line options - by Josuah Aron", ' ', "1.5");

    //off
    TCLAP::MultiArg<std::string> off("o", "off", "Specify an OFF file to load a mesh from", false, "string", cmd);

    //exclure un type d'objet
    TCLAP::SwitchArg noProceduralSwitch("","no-procedural","Exclude procedural meshes from scene", cmd, false);
    TCLAP::SwitchArg noFunctionalSwitch("","no-functional","Exclude functional meshes from scene", cmd, false);

    cmd.parse(_argc, _argv);

    filenames = off.getValue();
    noProcedural = noProceduralSwitch.getValue();
    noFunctional = noFunctionalSwitch.getValue();
}
