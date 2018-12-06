#include "volumeplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/tifvolumeobject.h"

void VolumePlugin::load()
{
    QMainWindow *window = this->getRenderingWindow();
    QMenu *menu = new QMenu("volume", window);
    QAction *action = new QAction("open tifs directory");
    menu->addAction(action);

    widget = renderingWindow->findChild<QWidget *>("centralwidget");
    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);
    tab = renderingWindow->findChild<QTabWidget *>("tabWidget");
    tab->setMinimumHeight(602);
    tab->setMinimumWidth(811);

    connect(action, SIGNAL(triggered()), this, SLOT(openTifStack()));
}

const char* VolumePlugin::getType()
{
    return "volumePlugin";
}

void VolumePlugin::close()
{

}

VolumePlugin::~VolumePlugin()
{

}

void VolumePlugin::openTifStack()
{
    Object *object = new TifVolumeObject();
    if(object->readObject())
    {
        window = new QWidget();
        widget->show();

        QVTKWidget *vtkWidget = new QVTKWidget(window, 0);
        vtkWidget->setObjectName("qvtkWidget");
        vtkWidget->setFixedHeight(580);
        vtkWidget->setFixedWidth(789);

        const QString name = QObject::tr("Volume object");
        tab->addTab(window, name);

        core->addObject(object);
        core->addTab(window);

        object->printObject(vtkWidget);
    }
}
