#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <string>
#include <tclap/CmdLine.h>

namespace my{

class Configurator
{
private:
    std::string _cmd;

    static const std::string _defaultConfig;
    static const std::string _defaultConfigFile;

    public:
    Configurator(const std::string & argv="");

    void parse();

    void loadConfig(const std::string & filename="");

    void saveRunningConfig(const std::string & filename="");

};

}

#endif // CONFIGURATOR_H
