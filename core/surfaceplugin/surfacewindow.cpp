#include "surfacewindow.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/objobject.h"
#include "QDockWidget"
#include "QVBoxLayout"
#include "QDesktopWidget"

SurfaceWindow::SurfaceWindow(QWidget *parent) : QDockWidget(parent)
{
    setParent(parent);
    setWindowTitle("Surface Scene");
}

bool SurfaceWindow::initialize()
{
    Object *object = new ObjObject();
    bool initialized = object->readObject();

    if(initialized)
    {
        QVTKWidget *vtkWidget = new QVTKWidget();

        QWidget *window = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->setGeometry(window->geometry());
        layout->addWidget(vtkWidget);

        this->setWidget(window);

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        this->setMinimumSize(min);
        QSize max(desktop->width(), desktop->height());
        this->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);

        core->addObject(object);

        object->printObject(vtkWidget);
    }

    return initialized;
}

void SurfaceWindow::setCore(Core *value)
{
    core = value;
    core->addTab(this);
}

RenderingWindow *SurfaceWindow::getRenderingWindow() const
{
    return renderingWindow;
}

void SurfaceWindow::setRenderingWindow(RenderingWindow *value)
{
    renderingWindow = value;
}
