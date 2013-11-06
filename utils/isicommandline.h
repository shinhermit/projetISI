/**
 * @author Josuah Aron
 * @date   Oct 2013
 *
 * Parses the command line for the ISI project.
 *
 */
#ifndef ISICOMMANDLINE_H
#define ISICOMMANDLINE_H

#include <string>
#include <vector>

#include <tclap/CmdLine.h>

namespace my{

/**
  *This class allows change the command line policy with no need to modify that 'main' file.
 *
 */
class IsiCommandLine
{
private:
    const int & _argc; /**< holds the main() function argc parameter */
    const char *const*_argv; /**< holds the main() function argv parameter */

public:
    /**
      *Constructor
      *@param argc the main() function argc parameter
      *@param argv the main() function argv parameter
      */
    IsiCommandLine(const int & argc, const char *const*argv);

    /**
      *Uses the TCLAP library to define and parse the command line arguments.
      *@param filenames will contain the list off files to be loaded, if option -o is specified
      *@param noProcedural will contain true if option --no-procedural has been specified, false elsewise
      *@param noFunctional will contain true if option --no-functionnal has been specified, false elsewise
      */
    void getParams(std::vector<std::string> & filenames, bool & noProcedural, bool & noFunctional);
};

}

#endif // ISICOMMANDLINE_H
