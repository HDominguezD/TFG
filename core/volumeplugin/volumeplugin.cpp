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
#include "boost/algorithm/string.hpp"
#include "QKeyEvent"
#include "myqvtkwidget.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPNGWriter.h"
#include "qfiledialog.h"
#include "transferFunctionEditor.h"
#include "QHBoxLayout"
#include "QRect"

void VolumePlugin::load()
{
    //setFocusPolicy(Qt::StrongFocus);
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

        QVTKWidget *vtkWidget = new MyQVTKWidget();
        string nameWidget = string("QVTKWidget ") + to_string(docks.size());
        vtkWidget->setObjectName(nameWidget.c_str());
        vtkWidget->objectName();
        vtkWidget->setToolTip("Press the arrow keys to move the camera around the object");

        object->printObject(vtkWidget);

        QPushButton *compare = new QPushButton();
        string nameCompare = string("CompareObj ") + to_string(docks.size());
        compare->setObjectName(nameCompare.c_str());
        compare->setText("Compare with 3D Model");
        connect(compare, SIGNAL(clicked()), this, SLOT(openObjFile()));

        QPushButton *capture = new QPushButton();
        string nameCapture = string("CaptureImg ") + to_string(docks.size());
        capture->setObjectName(nameCapture.c_str());
        capture->setText("Capture Image");
        connect(capture, SIGNAL(clicked()), this, SLOT(captureImage()));

        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(object);

        TransferFunctionEditor *transferEditor = new TransferFunctionEditor(nullptr, vol);
        string nameEditor = string("TransferEditor ") + to_string(docks.size());
        transferEditor->setObjectName(nameEditor.c_str());
        transferEditor->setMaximumHeight(80);
        transferEditor->setMinimumWidth(300);

        connect(transferEditor, SIGNAL(colorsChanged()), this, SLOT(updateWidget()));

        QSlider *slider = new QSlider(Qt::Orientation::Horizontal);
        string nameSlider = string("ScaleObj ") + to_string(docks.size());
        slider->setObjectName(nameSlider.c_str());
        compare->setText("scale 3D model");
        slider->hide();

        window = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->setGeometry(window->geometry());

        QHBoxLayout *featuresLayout = new QHBoxLayout(nullptr);

        QVBoxLayout *buttonsLayout = new QVBoxLayout(nullptr);
        buttonsLayout->addWidget(capture);
        buttonsLayout->addWidget(compare);
        buttonsLayout->addWidget(slider);

        featuresLayout->addLayout(buttonsLayout);
        featuresLayout->addWidget(transferEditor);
        layout->addLayout(featuresLayout);
        layout->addWidget(vtkWidget);

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

        //core->addObject(object);

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

            //scale rotate traslate
            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            transform->Scale(14, -14, 14);
            vtkSmartPointer<vtkTransform> transform2 = vtkSmartPointer<vtkTransform>::New();
            transform2->Translate(-actualActor->GetCenter()[0] + 8, -actualActor->GetCenter()[1], -actualActor->GetCenter()[2]);
            transform->Concatenate(transform2->GetMatrix());

            actualActor->SetUserTransform(transform);

            string nameButton = string("CompareObj ") + to_string(dockNumber);
            QPushButton *compare = dock->findChild<QPushButton *>(nameButton.c_str());
            if(compare)
            {
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
    if(slider)
    {
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
        transform->Scale(pow(1.01 , (value - lastValue)), pow(1.01 , (value - lastValue)),pow(1.01 , (value - lastValue)));
        transform->Concatenate(actualActor->GetUserMatrix());
        actualActor->SetUserTransform(transform);
    }
     vtkWidget->GetRenderWindow()->Render();
     lastValue = value;
}

void VolumePlugin::captureImage()
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

    // Screenshot
      vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
        vtkSmartPointer<vtkWindowToImageFilter>::New();
      windowToImageFilter->SetInput(vtkWidget->GetRenderWindow());
      windowToImageFilter->SetMagnification(3); //set the resolution of the output image (3 times the current resolution of vtk render window)
      windowToImageFilter->Update();

      QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"), "/home/Desktop/newImage.png",tr("Images (*.png)"));
      std::string filename = fileName.toStdString();

      QFile f( fileName );
      f.open( QIODevice::WriteOnly );

      vtkSmartPointer<vtkPNGWriter> writer =
        vtkSmartPointer<vtkPNGWriter>::New();
      writer->SetFileName(filename.c_str());
      writer->SetInputConnection(windowToImageFilter->GetOutputPort());
      writer->Write();

      vtkWidget->GetRenderWindow()->Render();
}

void VolumePlugin::updateWidget()
{
    TransferFunctionEditor* editorSender = qobject_cast<TransferFunctionEditor*>(sender());
    string editorName = editorSender->objectName().toStdString();
    vector<string> splitName;
    boost::split(splitName, editorName, [](char c){return c == ' ';});
    string number = splitName.at(splitName.size() - 1);
    int dockNumber = atoi(number.c_str());

    string nameDock = string("Dock ") + to_string(dockNumber);
    QDockWidget* dock = renderingWindow->findChild<QDockWidget*>(nameDock.c_str());

    string nameWidget = string("QVTKWidget ") + to_string(dockNumber);
    QVTKWidget *vtkWidget = dock->findChild<QVTKWidget*>(nameWidget.c_str());

    vtkWidget->GetRenderWindow()->Render();
}
