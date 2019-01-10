#include "volumeplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/tifvolumeobject.h"
#include "objectclasses/objobject.h"
#include "QDockWidget"
#include "QHBoxLayout"
#include "QPushButton"
#include "QDesktopWidget"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkActorCollection.h"
#include "vtkTransform.h"


void VolumePlugin::load()
{
    QMenu *menu = new QMenu("volume", renderingWindow);
    QAction *action = new QAction("open tifs directory");
    menu->addAction(action);

    widget = renderingWindow->findChild<QWidget *>("centralwidget");
    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

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
        QList<QDockWidget*> docks = renderingWindow->findChildren<QDockWidget*>();

        QDockWidget *dock = new QDockWidget(tr("Volume Object"), renderingWindow);
        dock->setAllowedAreas(Qt::AllDockWidgetAreas);

        if(docks.isEmpty())
        {
            renderingWindow->addDockWidget(Qt::RightDockWidgetArea, dock);
        }
        else
        {
            renderingWindow->addDockWidget(Qt::TopDockWidgetArea, dock);
            renderingWindow->tabifyDockWidget(docks.at(docks.size() -1), dock);
            dock->setVisible(true);
            dock->setFocus();
            dock->raise();
        }

        QVTKWidget *vtkWidget = new QVTKWidget();
        vtkWidget->setObjectName("QVTKWidget");

        window = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(window);
        layout->setGeometry(window->geometry());
        layout->addWidget(vtkWidget);

        QPushButton *compare = new QPushButton();
        compare->setText("Compare with 3D Model");
        layout->addWidget(compare);
        connect(compare, SIGNAL(clicked()), this, SLOT(openObjFile()));

        dock->setWidget(window);

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        dock->setMinimumSize(min);
        QSize max(desktop->width() -200, desktop->height() -200);
        dock->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);

        core->addObject(object);
        core->addTab(window);

        object->printObject(vtkWidget);
    }
}

void VolumePlugin::openObjFile()
{
    Object *object = new ObjObject();
    if(object->readObject())
    {
        QVTKWidget *vtkWidget = window->findChild<QVTKWidget*>("QVTKWidget");

        core->addObject(object);

        object->printObject(vtkWidget);

        vtkRenderer *renderer = vtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

        vtkVolumeCollection *volumes = renderer->GetVolumes();
        volumes->InitTraversal();
        vtkVolume *volume = volumes->GetNextItem();
        if(volume != nullptr){
            vtkActorCollection *actors = renderer->GetActors();
            actors->InitTraversal();
            vtkActor *actualActor = actors->GetLastActor();
            if(actualActor != nullptr){
                int act = actors->GetNumberOfItems();
                actors->RemoveItem(actors->GetNumberOfItems()-1);
                //scale actor to be equal to the volume actor
                double yrange = *actualActor->GetYRange();
                double yrange2 = *volume->GetYRange();
                double zrange = *actualActor->GetZRange();
                double zrange2 = *volume->GetZRange();
                double xrange = *actualActor->GetXRange();
                double xrange2 = *volume->GetXRange();

                 double *o = actualActor->GetCenter();

                 //scale rotate traslate
                 vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
                transform->Scale(yrange2 / yrange, yrange2 / yrange, yrange2 / yrange);
                vtkSmartPointer<vtkTransform> transform2 = vtkSmartPointer<vtkTransform>::New();
                transform2->Translate(-actualActor->GetCenter()[0], -actualActor->GetCenter()[1], -actualActor->GetCenter()[2]);

                transform->Concatenate(transform2->GetMatrix());
                int i = transform->GetNumberOfConcatenatedTransforms();

                actualActor->SetUserTransform(transform);


                renderer->AddActor(actualActor);

                double *center = actualActor->GetCenter();
//                vtkWidget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
//                vtkWidget->GetRenderWindow()->AddRenderer(renderer);
                vtkWidget->GetRenderWindow()->Render();
//                int hola = 2;
            }
       }
    }
}

