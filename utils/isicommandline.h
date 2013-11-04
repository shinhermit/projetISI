#ifndef ISICOMMANDLINE_H
#define ISICOMMANDLINE_H

#include <string>
#include <vector>

#include <tclap/CmdLine.h>

namespace my{

class IsiCommandLine
{
private:
    const std::string _argv;

public:
    IsiCommandLine(const std::string & argv);

    void getParams(std::vector<std::string> & filenames, bool & noProcedural, bool & noFunctional);
};

}

#endif // ISICOMMANDLINE_H
