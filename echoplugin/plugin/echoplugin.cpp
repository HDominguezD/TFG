//#include <QtWidgets>

// #include "echoplugin.h"

// QString EchoPlugin::echo(const QString &message)
// {
//     return message;
// }

#include "echoplugin.h"
#include "QApplication"
#include "QAction"
#include "qdebug.h"

void EchoPlugin::load()
{
    /// Opens a model/project
    ///
        QAction *action = new QAction("Open Obj File");

    /// Reacts to changes in mode
    connect(action, SIGNAL(triggered()), this, SLOT(open()));
}

const char* EchoPlugin::getType()
{
    return "surfacePlugin";
}

void EchoPlugin::close()
{

}

void EchoPlugin::open(){
    char *a = "has pulsado surface";
    qDebug() << a;
}

