#include "volumeplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/tifvolumeobject.h"
#include "objectclasses/objobject.h"
#include "QDockWidget"
#include "QVBoxLayout"
#include "QPushButton"
#include "QDesktopWidget"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkActorCollection.h"
#include "vtkTransform.h"
#include "vtkMatrix4x4.h"
#include "boost/algorithm/string.hpp"


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
            string nameDock = string("Dock ") + to_string(docks.size());
            dock->setObjectName(nameDock.c_str());
        }
        else
        {
            renderingWindow->addDockWidget(Qt::TopDockWidgetArea, dock);
            renderingWindow->tabifyDockWidget(docks.last(), dock);
            dock->setVisible(true);
            dock->setFocus();
            dock->raise();
            string nameDock = string("Dock ") + to_string(docks.size());
            dock->setObjectName(nameDock.c_str());
        }

        QVTKWidget *vtkWidget = new QVTKWidget();
        string nameWidget = string("QVTKWidget ") + to_string(docks.size());
        vtkWidget->setObjectName(nameWidget.c_str());
        vtkWidget->objectName();

        window = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->setGeometry(window->geometry());
        layout->addWidget(vtkWidget);

        QPushButton *compare = new QPushButton();
        string nameButton = string("CompareObj ") + to_string(docks.size());
        compare->setObjectName(nameButton.c_str());
        compare->setText("Compare with 3D Model");
        layout->addWidget(compare);
        connect(compare, SIGNAL(clicked()), this, SLOT(openObjFile()));

        QSlider *slider = new QSlider(Qt::Orientation::Horizontal);
        string nameSlider = string("ScaleObj ") + to_string(docks.size());
        slider->setObjectName(nameSlider.c_str());
        compare->setText("scale 3D model");
        layout->addWidget(slider);
        slider->hide();

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
        QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());

        string buttonName = buttonSender->objectName().toStdString();

        vector<string> splitName;
        boost::split(splitName, buttonName, [](char c){return c == ' ';});
        string number = splitName.at(splitName.size() - 1);
        int dockNumber = atoi(number.c_str());

        string nameDock = string("Dock ") + to_string(dockNumber);
        QDockWidget* dock = renderingWindow->findChild<QDockWidget*>(nameDock.c_str());

        string nameWidget = string("QVTKWidget ") + to_string(dockNumber);
        QVTKWidget *vtkWidget = dock->findChild<QVTKWidget*>(nameWidget.c_str());

        core->addObject(object);

        object->printObject(vtkWidget);

        vtkRenderer *renderer = vtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

        vtkVolumeCollection *volumes = renderer->GetVolumes();
        volumes->InitTraversal();
        vtkVolume *volume = volumes->GetNextItem();
        if(volume != nullptr)
        {
            vtkActorCollection *actors = renderer->GetActors();
            actors->InitTraversal();
            vtkActor *actualActor = actors->GetLastActor();

            if(actualActor != nullptr)
            {
                //scale actor to be equal to the volume actor
//                double yrange = *actualActor->GetYRange();
//                double yrange2 = *volume->GetYRange();
//                double zrange = *actualActor->GetZRange();
//                double zrange2 = *volume->GetZRange();
//                double xrange = *actualActor->GetXRange();
//                double xrange2 = *volume->GetXRange();

                //scale rotate traslate
                vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
                transform->Scale(14, -14, 14);
                vtkSmartPointer<vtkTransform> transform2 = vtkSmartPointer<vtkTransform>::New();
                transform2->Translate(-actualActor->GetCenter()[0], -actualActor->GetCenter()[1], -actualActor->GetCenter()[2]);
                transform->Concatenate(transform2->GetMatrix());

                double *o = actualActor->GetCenter();
                actualActor->SetUserTransform(transform);

                string nameButton = string("CompareObj ") + to_string(dockNumber);
                QPushButton *compare = dock->findChild<QPushButton *>(nameButton.c_str());
                if(compare){
                    compare->hide();
                    string nameSlider = string("ScaleObj ") + to_string(dockNumber);
                    QSlider *slider = dock->findChild<QSlider *>(nameSlider.c_str());
                    initializeSlider(slider);
                }
            }
       }
    }
}


void VolumePlugin::initializeSlider(QSlider *slider)
{
    if(slider){
        slider->show();
        slider->setMaximum(200);
        slider->setMinimum(0);
        slider->setValue(100);
        lastValue = 100;
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeObjScale(int)));
    }
}


void VolumePlugin::changeObjScale(int value)
{
        QSlider* sliderSender = qobject_cast<QSlider*>(sender());

        string sliderName = sliderSender->objectName().toStdString();

        vector<string> splitName;
        boost::split(splitName, sliderName, [](char c){return c == ' ';});
        string number = splitName.at(splitName.size() - 1);
        int dockNumber = atoi(number.c_str());

        string nameDock = string("Dock ") + to_string(dockNumber);
        QDockWidget* dock = renderingWindow->findChild<QDockWidget*>(nameDock.c_str());

        string nameWidget = string("QVTKWidget ") + to_string(dockNumber);
        QVTKWidget *vtkWidget = dock->findChild<QVTKWidget*>(nameWidget.c_str());
        vtkRenderer *renderer = vtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

        vtkActorCollection *actors = renderer->GetActors();
        actors->InitTraversal();
        vtkActor *actualActor = actors->GetLastActor();

        if(actualActor)
        {
            //scale rotate traslate
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();

            if(lastValue < value){
                transform->Scale(pow(1.01 , (value - lastValue)), pow(1.01 , (value - lastValue)),pow(1.01 , (value - lastValue)));
            } else {
                transform->Scale(pow(0.99 , (lastValue - value)), pow(0.99 , (lastValue - value)), pow(0.99 , (lastValue - value)));
            }

            double po = pow(0.9 , (value - lastValue));
            transform->Concatenate(actualActor->GetUserMatrix());
            double *o = actualActor->GetCenter();
            vtkMatrix4x4* mat = actualActor->GetUserMatrix();
            int matr[4][4];
            for(int i = 0; i < 4; i++){
                for(int j = 0; j <4; j++){
                    matr[i][j] = mat->Element[i][j];
                }
            }
            actualActor->SetUserTransform(transform);

            vtkMatrix4x4* mat2 = actualActor->GetUserMatrix();
            int matr2[4][4];
            for(int i = 0; i < 4; i++){
                for(int j = 0; j <4; j++){
                    matr2[i][j] = mat2->Element[i][j];
                }
            }
        }
         vtkWidget->GetRenderWindow()->Render();
         lastValue = value;
}
