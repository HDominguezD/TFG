#include "readpythonplugin.h"
#include "qmenubar.h"
#include "pythonscriptswindow.h"

void ReadPythonPlugin::load()
{

//    string pythonCode2 = "/home/hector/Desktop/Python/script.py";
//    string code2 = "python3 " + pythonCode2;
//    system(code2.c_str());

//    string pythonCode = "/home/hector/Desktop/Python/evaluation_NN.py";
//    string code = "python3 " + pythonCode;
//    //system(code.c_str());

    QMainWindow *window = this->getRenderingWindow();
    QMenu *menu = new QMenu("Scripts", window);
    QAction *action = new QAction("Open Python Script");
    menu->addAction(action);

    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

    connect(action, SIGNAL(triggered()), this, SLOT(openPythonScript()));
}

const char *ReadPythonPlugin::getType()
{
    return "ExecutionPlugin";
}

void ReadPythonPlugin::close()
{

}

ReadPythonPlugin::~ReadPythonPlugin()
{

}

void ReadPythonPlugin::openPythonScript()
{
    window = new PythonScriptsWindow(nullptr);
    window->show();
}
