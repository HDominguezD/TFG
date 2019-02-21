#include "readpythonplugin.h"
//#include "Python.h"

void ReadPythonPlugin::load()
{

    string pythonCode2 = "/home/hector/Desktop/Python/script.py";
    string code2 = "python3 " + pythonCode2;
    //Py_Initialize();
    system(code2.c_str());
    string pythonCode = "/home/hector/Desktop/Python/evaluation_NN.py";
    string code = "python3 " + pythonCode;
    //Py_Initialize();
    system(code.c_str());
}

const char *ReadPythonPlugin::getType()
{
    return "Execution";
}

void ReadPythonPlugin::close()
{

}

ReadPythonPlugin::~ReadPythonPlugin()
{

}
