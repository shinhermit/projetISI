#ifndef ISICOMMANDLINE_H
#define ISICOMMANDLINE_H

#include <string>
#include <vector>

#include <tclap/CmdLine.h>

namespace my{

class IsiCommandLine
{
private:
    const int & _argc;
    const char *const*_argv;

public:
    IsiCommandLine(const int & argc, const char *const*argv);

    void getParams(std::vector<std::string> & filenames, bool & noProcedural, bool & noFunctional);
};

}

#endif // ISICOMMANDLINE_H
