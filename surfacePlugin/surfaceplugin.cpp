#include "surfaceplugin.h"
#include "QApplication"
#include "qdebug.h"

surfacePlugin::surfacePlugin()
{

}

void surfacePlugin::init()
{

}

void surfacePlugin::load()
{
    /// Opens a model/project
    ///

        QMenu *menu = new QMenu("Surface", this->getUi()->menubar);
        QAction *action = new QAction("Open Obj File");
        menu->addAction(action);

        /// Reacts to changes in mode
        connect(action, SIGNAL(triggered()), this, SLOT(open()));

        this->getUi()->menubar->addMenu(menu);
}

const char* surfacePlugin::getType()
{
    return "surfacePlugin";
}

void surfacePlugin::close()
{

}

void surfacePlugin::open(){
    char *a = "has pulsado surface";
    qDebug() << a;
}
