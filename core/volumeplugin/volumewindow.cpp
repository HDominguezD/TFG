#include "volumewindow.h"
#include "objectclasses/tifvolumeobject.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
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
#include "Editors/transferFunctionEditor.h"
#include "QHBoxLayout"
#include "QRect"
#include "QMainWindow"
#include "Editors/transformeditor.h"
#include "Buttons/objectbutton.h"
#include "Buttons/camerabutton.h"

VolumeWindow::VolumeWindow(QWidget *parent) : QDockWidget(parent)
{
    setParent(parent);
    objectPropertiesPairs = new QVector<ObjectPropertiesPair *>();
    setWindowTitle("Volume Scene");
}

bool VolumeWindow::initialize()
{
    TifVolumeObject *vol = new TifVolumeObject();
    bool initialized = vol->readObject();

    if(initialized)
    {
        QTabWidget *tab = new QTabWidget(this);
        window = new QMainWindow(tab);
        window->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
        tab->addTab(window, "Scene");

        QMenuBar* menuBar = new QMenuBar(window);
        QMenu *fileMenu = new QMenu("Add Object");
        menuBar->addMenu(fileMenu);
        QAction *objAction = new QAction("Obj object");
        fileMenu->addAction(objAction);
        QAction *volAction = new QAction("Tiff volume");
        fileMenu->addAction(volAction);
        QAction *capture = new QAction("Capture Scene");
        menuBar->addAction(capture);

        connect(objAction, SIGNAL(triggered()), this, SLOT(openObjFile()));
        connect(capture, SIGNAL(triggered()), this, SLOT(captureImage()));

        window->layout()->setMenuBar(menuBar);

        hierarchy = new QDockWidget(tr("Hierarchy"), window);
        hierarchy->setAllowedAreas(Qt::AllDockWidgetAreas);

        vtkWidget = new QVTKWidget(window);
        vol->printObject(vtkWidget);

        QMenuBar* bar = new QMenuBar(vtkWidget);
        QMenu *translate = new QMenu("Translate");
        bar->addMenu(translate);
        QMenu *rotate = new QMenu("Rotate");
        bar->addMenu(rotate);
        QMenu *scalate = new QMenu("Scalate");
        bar->addMenu(scalate);

        QVBoxLayout *vtkLayout = new QVBoxLayout(vtkWidget);
        vtkLayout->setAlignment(Qt::AlignTop);
        vtkLayout->setMenuBar(bar);

        window->setCentralWidget(vtkWidget);

        ObjectPropertiesPair *objectPropertiesPair = createVolumePropertiesPanel(vol);
        objectPropertiesPairs->append(objectPropertiesPair);

        objectPropertiesPair->getPropertiesDock()->show();

        this->setWidget(tab);

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        this->setMinimumSize(min);
        QSize max(desktop->width(), desktop->height());
        this->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);

        //vtkCamera *camera = vtkWidget->GetRenderWindow()->GetRenderers()->GetNextItem()->GetActiveCamera();
        vtkCamera *camera = vtkSmartPointer<vtkCamera>::New();
        cameraPropertiesPair = createCameraPropertiesPanel(camera);

        core->addObject(vol);

        initializeHierarchyPanel();
        addObjectToHierarchyPanel(objectPropertiesPair);
    }

    return initialized;
}

void VolumeWindow::setCore(Core *value)
{
    core = value;
    core->addTab(this);
}

void VolumeWindow::openObjFile()
{
    ObjObject *object = new ObjObject();
    if(object->readObject())
    {
        core->addObject(object);
        object->printObject(vtkWidget);
        ObjectPropertiesPair *objectPropertiesPair = createObjectPropertiesPanel(object);

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
            transform->Scale(1, -1, 1);
            vtkSmartPointer<vtkTransform> transform2 = vtkSmartPointer<vtkTransform>::New();
            transform2->Translate(-actualActor->GetCenter()[0] + 8, -actualActor->GetCenter()[1], -actualActor->GetCenter()[2]);
            transform->Concatenate(transform2->GetMatrix());

            actualActor->SetUserTransform(transform);

            string nameButton = string("CompareObj");
            QPushButton *compare = this->findChild<QPushButton *>(nameButton.c_str());
            if(compare)
            {
                compare->hide();
//                string nameSlider = string("ScaleObj ") + to_string(dockNumber);
//                QSlider *slider = dock->findChild<QSlider *>(nameSlider.c_str());
//                initializeSlider(slider);
            }
            }
        }
        addObjectToHierarchyPanel(objectPropertiesPair);
        createObjectPropertiesPanel(object);
        changeFocusedToObject(objectPropertiesPair);
        vtkWidget->GetRenderWindow()->Render();
    }
}


void VolumeWindow::initializeSlider(QSlider *slider)
{
    if(slider)
    {
        slider->show();
        slider->setMaximum(200);
        slider->setMinimum(0);
        slider->setValue(100);
        //lastValue = 100;

        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeObjScale(int)));
    }
}

ObjectPropertiesPair* VolumeWindow::createVolumePropertiesPanel(TifVolumeObject *vol)
{
    QDockWidget *properties = new QDockWidget(tr("Properties"), window);
    properties->setAllowedAreas(Qt::AllDockWidgetAreas);
    properties->setObjectName("Properties Dock");
    properties->setFixedWidth(330);
    properties->hide();

    QWidget *propertiesWidget = new QWidget(properties);
    QVBoxLayout *propertiesLayout = new QVBoxLayout(propertiesWidget);
    propertiesLayout->setAlignment(Qt::AlignTop);

    QWidget *transformWidget = new QWidget(propertiesWidget);
    QVBoxLayout *transformLayout = new QVBoxLayout(transformWidget);
    transformLayout->setAlignment(Qt::AlignTop);

    QLabel *transformLabel = new QLabel(transformWidget);
    transformLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    transformLabel->setText("Transform");
    transformLabel->setAlignment(Qt::AlignCenter);
    transformLabel->setFixedHeight(20);

    TransformEditor *transformEditor = new TransformEditor(transformWidget);
    transformEditor->setMinimumWidth(300);

    transformLayout->addWidget(transformLabel);
    transformLayout->addWidget(transformEditor);

    propertiesLayout->addWidget(transformWidget);

    QWidget *transferFunctionWidget = new QWidget(propertiesWidget);
    QVBoxLayout *transferFunctionLayout = new QVBoxLayout(transferFunctionWidget);
    transferFunctionLayout->setAlignment(Qt::AlignTop);

    QLabel *transferFuncitonLabel = new QLabel(transferFunctionWidget);
    transferFuncitonLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    transferFuncitonLabel->setText("Transference function");
    transferFuncitonLabel->setAlignment(Qt::AlignCenter);
    transferFuncitonLabel->setFixedHeight(20);

    TransferFunctionEditor *transferEditor = new TransferFunctionEditor(transferFunctionWidget, vol);
    transferEditor->setFixedHeight(80);
    transferEditor->setMinimumWidth(200);
    connect(transferEditor, SIGNAL(colorsChanged()), this, SLOT(updateWidget()));

    transferFunctionLayout->addWidget(transferFuncitonLabel);
    transferFunctionLayout->addWidget(transferEditor);

    propertiesLayout->addWidget(transferFunctionWidget);

    properties->setWidget(propertiesWidget);

    ObjectPropertiesPair *objectPropertiesPair = new ObjectPropertiesPair(vol, properties);
    window->addDockWidget(Qt::RightDockWidgetArea, objectPropertiesPair->getPropertiesDock());
    return objectPropertiesPair;
}

ObjectPropertiesPair *VolumeWindow::createObjectPropertiesPanel(ObjObject *obj)
{
    QDockWidget *properties = new QDockWidget(tr("Properties"), window);
    properties->setObjectName("Properties Dock");
    properties->setFixedWidth(330);
    properties->setAllowedAreas(Qt::AllDockWidgetAreas);
    properties->hide();

    QWidget *propertiesWidget = new QWidget(properties);
    QVBoxLayout *propertiesLayout = new QVBoxLayout(propertiesWidget);
    propertiesLayout->setAlignment(Qt::AlignTop);

    QWidget *transformWidget = new QWidget(propertiesWidget);
    QVBoxLayout *transformLayout = new QVBoxLayout(transformWidget);
    transformLayout->setAlignment(Qt::AlignTop);

    QLabel *transformLabel = new QLabel(transformWidget);
    transformLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    transformLabel->setText("Transform");
    transformLabel->setAlignment(Qt::AlignCenter);
    transformLabel->setFixedHeight(20);

    TransformEditor *transformEditor = new TransformEditor(transformWidget);
    transformEditor->setMinimumWidth(300);

    transformLayout->addWidget(transformLabel);
    transformLayout->addWidget(transformEditor);

    propertiesLayout->addWidget(transformWidget);

    properties->setWidget(propertiesWidget);

    ObjectPropertiesPair *objectPropertiesPair = new ObjectPropertiesPair(obj, properties);
    window->addDockWidget(Qt::RightDockWidgetArea, objectPropertiesPair->getPropertiesDock());
    return objectPropertiesPair;
}

CameraPropertiesPair *VolumeWindow::createCameraPropertiesPanel(vtkCamera *camera)
{
    QDockWidget *properties = new QDockWidget(tr("Properties"), window);
    properties->setObjectName("Properties Dock");
    properties->setFixedWidth(330);
    properties->setAllowedAreas(Qt::AllDockWidgetAreas);
    properties->hide();

    QWidget *propertiesWidget = new QWidget(properties);
    QVBoxLayout *propertiesLayout = new QVBoxLayout(propertiesWidget);
    propertiesLayout->setAlignment(Qt::AlignTop);

    QWidget *transformWidget = new QWidget(propertiesWidget);
    QVBoxLayout *transformLayout = new QVBoxLayout(transformWidget);
    transformLayout->setAlignment(Qt::AlignTop);

    QLabel *transformLabel = new QLabel(transformWidget);
    transformLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    transformLabel->setText("Transform");
    transformLabel->setAlignment(Qt::AlignCenter);
    transformLabel->setFixedHeight(20);

    TransformEditor *transformEditor = new TransformEditor(transformWidget);
    transformEditor->setMinimumWidth(300);

    transformLayout->addWidget(transformLabel);
    transformLayout->addWidget(transformEditor);

    propertiesLayout->addWidget(transformWidget);

    //camera center widget

    properties->setWidget(propertiesWidget);

    CameraPropertiesPair *cameraPropertiesPair = new CameraPropertiesPair(camera, properties);
    window->addDockWidget(Qt::RightDockWidgetArea, cameraPropertiesPair->getPropertiesDock());
    return cameraPropertiesPair;
}

void VolumeWindow::initializeHierarchyPanel()
{
    QWidget *hierarchyWidget = new QWidget(hierarchy);
    hierarchyWidget->setObjectName("Hierarchy Widget");

    QVBoxLayout *hierarchyLayout = new QVBoxLayout(hierarchyWidget);
    hierarchyLayout->setAlignment(Qt::AlignTop);
    hierarchyLayout->setObjectName("Hierarchy Layout");

    CameraButton *cameraButton = new CameraButton(cameraPropertiesPair, hierarchyWidget);
    cameraButton->setText("Camera");
    hierarchyLayout->addWidget(cameraButton);
    connect(cameraButton, SIGNAL(cameraButtonClicked(CameraPropertiesPair*)), this, SLOT(changeFocusedToCamera(CameraPropertiesPair*)));

    //connect(camera, SIGNAL(clicked(bool)), this, SLOT(updateWidget());


//    vtkRendererCollection * renderers = vtkWidget->GetRenderWindow()->GetRenderers();
//    vtkRenderer *renderer = renderers->GetFirstRenderer();

//    vtkVolumeCollection volumes = renderer->GetVolumes();
//    vtkActorCollection actors = renderer->GetActors();

//    for(vtkVolume *vol : volumes)
//    {
//        QPushButton *volume = new QPushButton("VolumeObject", hierarchyWidget);
//        hierarchyLayout->addWidget(volume);
//        connect(volume, SIGNAL(clicked(bool)), this, SLOT(updateWidget());
//    }

//    for(vtkActor *obj : actors)
//    {
//        QPushButton *obj = new QPushButton("Obj Object", hierarchyWidget);
//        hierarchyLayout->addWidget(obj);
//        connect(obj, SIGNAL(clicked(bool)), this, SLOT(updateWidget());
//    }

    hierarchy->setWidget(hierarchyWidget);
    window->addDockWidget(Qt::LeftDockWidgetArea, hierarchy);
}

void VolumeWindow::addObjectToHierarchyPanel(ObjectPropertiesPair * objectPropertiesPair)
{
    ObjObject *obj = dynamic_cast<ObjObject*>(objectPropertiesPair->getObject());
    QWidget *hierarchyWidget = hierarchy->findChild<QWidget *>("Hierarchy Widget");
    QVBoxLayout *hierarchyLayout = hierarchyWidget->findChild<QVBoxLayout *>("Hierarchy Layout");

    if(obj != nullptr)
    {
        ObjectButton *objButton = new ObjectButton(objectPropertiesPair, hierarchyWidget);
        objButton->setText("Obj Object");
        hierarchyLayout->addWidget(objButton);
        connect(objButton, SIGNAL(objectButtonClicked(ObjectPropertiesPair*)), this, SLOT(changeFocusedToObject(ObjectPropertiesPair*)));

    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(objectPropertiesPair->getObject());
        if(vol != nullptr)
        {
            ObjectButton *volumeButton = new ObjectButton(objectPropertiesPair, hierarchyWidget);
            volumeButton->setText("Volume Object");
            hierarchyLayout->addWidget(volumeButton);
                    connect(volumeButton, SIGNAL(objectButtonClicked(ObjectPropertiesPair*)), this, SLOT(changeFocusedToObject(ObjectPropertiesPair*)));

        }
    }
}

RenderingWindow *VolumeWindow::getRenderingWindow() const
{
    return renderingWindow;
}

void VolumeWindow::setRenderingWindow(RenderingWindow *value)
{
    renderingWindow = value;
}


void VolumeWindow::changeObjScale(int value)
{
    vtkRenderer *renderer = vtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();

    vtkActorCollection *actors = renderer->GetActors();
    actors->InitTraversal();
    vtkActor *actualActor = actors->GetLastActor();

    if(actualActor)
    {
        //scale rotate traslate
        vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
        //transform->Scale(pow(1.01 , (value - lastValue)), pow(1.01 , (value - lastValue)),pow(1.01 , (value - lastValue)));
        transform->Concatenate(actualActor->GetUserMatrix());
        actualActor->SetUserTransform(transform);
    }
     vtkWidget->GetRenderWindow()->Render();
     //lastValue = value;
}

void VolumeWindow::captureImage()
{
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

void VolumeWindow::changeFocusedToCamera(CameraPropertiesPair *cameraPropertiesPair)
{
    QList<QDockWidget *> propertiesPanels = window->findChildren<QDockWidget *>("Properties Dock");
    for(QDockWidget* panel : propertiesPanels)
    {
        if(panel != cameraPropertiesPair->getPropertiesDock())
        {
            panel->hide();
        }
    }
    cameraPropertiesPair->getPropertiesDock()->show();
}

void VolumeWindow::changeFocusedToObject(ObjectPropertiesPair *objectPropertiesPair)
{

    QList<QDockWidget *> propertiesPanels = window->findChildren<QDockWidget *>("Properties Dock");
    for(QDockWidget* panel : propertiesPanels)
    {
        if(panel != objectPropertiesPair->getPropertiesDock())
        {
            panel->hide();
        }
    }
    objectPropertiesPair->getPropertiesDock()->show();
    ObjObject *obj = dynamic_cast<ObjObject*>(objectPropertiesPair->getObject());
    if(obj != nullptr)
    {
        double *center = obj->getCenter();
        //cameraPropertiesPair->getCamera()->SetFocalPoint(center[0], center[1], center[2]);

    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(objectPropertiesPair->getObject());
        if(vol != nullptr)
        {
            double *center = vol->getCenter();
            //cameraPropertiesPair->getCamera()->SetFocalPoint(center[0], center[1], center[2]);
        }
    }
}

void VolumeWindow::updateWidget()
{
    vtkWidget->GetRenderWindow()->Render();
}
