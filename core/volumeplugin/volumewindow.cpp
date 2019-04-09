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
#include "Editors/transformeditorObject.h"
#include "TreeWidgetItems/cameratreewidgetitem.h"
#include "TreeWidgetItems/objecttreewidgetitem.h"
#include "Editors/transformeditorcamera.h"
#include "QTreeWidget"
#include "Editors/objecteditor.h"
#include "vtkAxesActor.h"
#include "vtkOrientationMarkerWidget.h"
#include "QSizePolicy"
#include "vtkPolyDataMapper.h"
#include "vtkMarchingCubes.h"
#include "vtkOBJExporter.h"
#include "Editors/applyconversionseditor.h"
#include "vtkAbstractVolumeMapper.h"

VolumeWindow::VolumeWindow(QWidget *parent) : QDockWidget(parent)
{
    setParent(parent);
    objectPropertiesPairs = new QVector<ObjectPropertiesPair *>();
    objectTreeWidgets = new QVector<ObjectTreeWidgetItem *>();
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
        connect(volAction, SIGNAL(triggered()), this, SLOT(openTifVolume()));
        connect(capture, SIGNAL(triggered()), this, SLOT(captureImage()));

        window->layout()->setMenuBar(menuBar);

        hierarchy = new QDockWidget(tr("Hierarchy"), window);
        hierarchy->setMinimumWidth(275);
        hierarchy->setMinimumHeight(200);
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

        this->setWidget(tab);

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        this->setMinimumSize(min);
        QSize max(desktop->width(), desktop->height());
        this->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);

        vtkSmartPointer<vtkCamera> camera = vtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera();
        cameraPropertiesPair = createCameraPropertiesPanel(camera);

        ObjectPropertiesPair *objectPropertiesPair = createVolumePropertiesPanel(vol);
        objectPropertiesPairs->append(objectPropertiesPair);

        objectPropertiesPair->getPropertiesDock()->show();

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

//        vtkRenderer *renderer = vtkWidget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
//        vtkVolumeCollection *volumes = renderer->GetVolumes();
//        volumes->InitTraversal();
//        vtkVolume *volume = volumes->GetNextItem();

//        if(volume != nullptr)
//        {
//            vtkActorCollection *actors = renderer->GetActors();
//            actors->InitTraversal();
//            vtkActor *actualActor = actors->GetLastActor();

//            if(actualActor != nullptr)
//            {

//            //scale rotate traslate

////            double pos[3] = {0, 0, 0};
////            double sca[3] = {1, -1, 1};
////            actualActor->SetPosition(pos);
////            actualActor->SetScale(sca);

//            string nameButton = string("CompareObj");
//            QPushButton *compare = this->findChild<QPushButton *>(nameButton.c_str());
//            if(compare)
//            {
//                compare->hide();
////                string nameSlider = string("ScaleObj ") + to_string(dockNumber);
////                QSlider *slider = dock->findChild<QSlider *>(nameSlider.c_str());
////                initializeSlider(slider);
//            }
//            }
//        }
        addObjectToHierarchyPanel(objectPropertiesPair);
        changeFocusedToObject(objectPropertiesPair);
        vtkWidget->GetRenderWindow()->Render();
    }
}

void VolumeWindow::openTifVolume()
{
    TifVolumeObject *object = new TifVolumeObject();
    if(object->readObject())
    {
        core->addObject(object);
        object->printObject(vtkWidget);
        ObjectPropertiesPair *objectPropertiesPair = createVolumePropertiesPanel(object);

        addObjectToHierarchyPanel(objectPropertiesPair);
        changeFocusedToObject(objectPropertiesPair);
        vtkWidget->GetRenderWindow()->Render();
    }
}


//void VolumeWindow::initializeSlider(QSlider *slider)
//{
//    if(slider)
//    {
//        slider->show();
//        slider->setMaximum(200);
//        slider->setMinimum(0);
//        slider->setValue(100);
//        //lastValue = 100;

//        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeObjScale(int)));
//    }
//}

ObjectPropertiesPair* VolumeWindow::createVolumePropertiesPanel(TifVolumeObject *vol)
{
    QDockWidget *properties = new QDockWidget(tr("Properties"), window);
    properties->setAllowedAreas(Qt::AllDockWidgetAreas);
    properties->setObjectName("Properties Dock");
//    properties->setFixedWidth(330);
    //properties->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    properties->hide();

    QWidget *propertiesWidget = new QWidget(properties);
    QVBoxLayout *propertiesLayout = new QVBoxLayout(propertiesWidget);
    propertiesLayout->setAlignment(Qt::AlignTop);

    //object  widget
    QWidget *objectWidget = new QWidget(propertiesWidget);
    QVBoxLayout *objectLayout = new QVBoxLayout(objectWidget);
    objectLayout->setAlignment(Qt::AlignTop);

    QLabel *objectLabel = new QLabel(objectWidget);
    objectLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    objectLabel->setText("Object");
    objectLabel->setAlignment(Qt::AlignCenter);
    objectLabel->setFixedHeight(20);

    ObjectEditor *objectEditor = new ObjectEditor(objectWidget, vol, vtkWidget);
    objectEditor->setMinimumWidth(300);
    objectEditor->setMaximumWidth(300);

    objectLayout->addWidget(objectLabel);
    objectLayout->addWidget(objectEditor);

    propertiesLayout->addWidget(objectWidget);
    connect(objectEditor, SIGNAL(changeObjectName(ObjectEditor*, QString)), this, SLOT(changeName(ObjectEditor*, QString)));

    //transform widget
    QWidget *transformWidget = new QWidget(propertiesWidget);
    QVBoxLayout *transformLayout = new QVBoxLayout(transformWidget);
    transformLayout->setAlignment(Qt::AlignTop);

    QLabel *transformLabel = new QLabel(transformWidget);
    transformLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    transformLabel->setText("Transform");
    transformLabel->setAlignment(Qt::AlignCenter);
    transformLabel->setFixedHeight(20);

    TransformEditorObject *transformEditor = new TransformEditorObject(transformWidget, vol, vtkWidget, cameraPropertiesPair);
    transformEditor->setMinimumWidth(300);
    transformEditor->setMaximumWidth(300);

    transformLayout->addWidget(transformLabel);
    transformLayout->addWidget(transformEditor);

    propertiesLayout->addWidget(transformWidget);

    //transfer function widget
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
    transferEditor->setMinimumWidth(300);
    transferEditor->setMaximumWidth(300);
    connect(transferEditor, SIGNAL(colorsChanged()), this, SLOT(updateWidget()));

    transferFunctionLayout->addWidget(transferFuncitonLabel);
    transferFunctionLayout->addWidget(transferEditor);

    propertiesLayout->addWidget(transferFunctionWidget);


    //apply conversions widget
    QWidget *applyConversionsWidget = new QWidget(propertiesWidget);
    QVBoxLayout *applyConversionsLayout = new QVBoxLayout(applyConversionsWidget);
    applyConversionsLayout->setAlignment(Qt::AlignTop);

    QLabel *applyConversionsLabel = new QLabel(applyConversionsWidget);
    applyConversionsLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    applyConversionsLabel->setText("Apply conversions");
    applyConversionsLabel->setAlignment(Qt::AlignCenter);
    applyConversionsLabel->setFixedHeight(20);

    ApplyConversionsEditor *applyConversionsEditor = new ApplyConversionsEditor(applyConversionsWidget, vol);
    applyConversionsEditor->setMinimumWidth(300);
    applyConversionsEditor->setMaximumWidth(300);
    connect(applyConversionsEditor, SIGNAL(createMeshClicked(TifVolumeObject*)), this, SLOT(createMesh(TifVolumeObject*)));
    connect(applyConversionsEditor, SIGNAL(createSegmentationClicked(TifVolumeObject*)), this, SLOT(createSegmentation(TifVolumeObject*)));

    applyConversionsLayout->addWidget(applyConversionsLabel);
    applyConversionsLayout->addWidget(applyConversionsEditor);

    propertiesLayout->addWidget(applyConversionsWidget);

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

    //object  widget
    QWidget *objectWidget = new QWidget(propertiesWidget);
    QVBoxLayout *objectLayout = new QVBoxLayout(objectWidget);
    objectLayout->setAlignment(Qt::AlignTop);

    QLabel *objectLabel = new QLabel(objectWidget);
    objectLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    objectLabel->setText("Object");
    objectLabel->setAlignment(Qt::AlignCenter);
    objectLabel->setFixedHeight(20);

    ObjectEditor *objectEditor = new ObjectEditor(objectWidget, obj, vtkWidget);
    objectEditor->setMinimumWidth(300);
    objectEditor->setMaximumWidth(300);

    objectLayout->addWidget(objectLabel);
    objectLayout->addWidget(objectEditor);

    propertiesLayout->addWidget(objectWidget);
    connect(objectEditor, SIGNAL(changeObjectName(ObjectEditor*, QString)), this, SLOT(changeName(ObjectEditor*, QString)));

    //transform editor widget
    QWidget *transformWidget = new QWidget(propertiesWidget);
    QVBoxLayout *transformLayout = new QVBoxLayout(transformWidget);
    transformLayout->setAlignment(Qt::AlignTop);

    QLabel *transformLabel = new QLabel(transformWidget);
    transformLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    transformLabel->setText("Transform");
    transformLabel->setAlignment(Qt::AlignCenter);
    transformLabel->setFixedHeight(20);

    TransformEditorObject *transformEditor = new TransformEditorObject(transformWidget, obj, vtkWidget, cameraPropertiesPair);
    transformEditor->setMinimumWidth(300);
    transformEditor->setMaximumWidth(300);

    transformLayout->addWidget(transformLabel);
    transformLayout->addWidget(transformEditor);

    propertiesLayout->addWidget(transformWidget);

    //open mesh widget
    QWidget *openMeshWidget = new QWidget(propertiesWidget);
    QVBoxLayout *openMeshLayout = new QVBoxLayout(openMeshWidget);
    openMeshLayout->setAlignment(Qt::AlignTop);

    QLabel *openMeshLabel = new QLabel(openMeshWidget);
    openMeshLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    openMeshLabel->setText("Open Mesh");
    openMeshLabel->setAlignment(Qt::AlignCenter);
    openMeshLabel->setFixedHeight(20);

    QPushButton *openMesh = new QPushButton(tr("Open Mesh"), openMeshWidget);

    openMeshLayout->addWidget(openMeshLabel);
    openMeshLayout->addWidget(openMesh);

    connect(openMesh, SIGNAL(pressed()), this, SLOT(openMesh()));

    propertiesLayout->addWidget(openMeshWidget);

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

    TransformEditorCamera *transformEditor = new TransformEditorCamera(transformWidget, camera, vtkWidget);
    transformEditor->setObjectName("Transform Editor Camera");
    transformEditor->setMinimumWidth(300);
    transformEditor->setMaximumWidth(300);

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

    QTreeWidget *treeWidget = new QTreeWidget(hierarchyWidget);
    treeWidget->setObjectName("Tree Widget");
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabel("Scene Tree");
    cameraTreeWidget = new CameraTreeWidgetItem(cameraPropertiesPair, "Camera");
    treeWidget->insertTopLevelItem(0,cameraTreeWidget);

    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeWidgetItemClicked(QTreeWidgetItem*,int)));

    hierarchy->setWidget(hierarchyWidget);
    window->addDockWidget(Qt::LeftDockWidgetArea, hierarchy);
}

void VolumeWindow::addObjectToHierarchyPanel(ObjectPropertiesPair * objectPropertiesPair)
{
    ObjObject *obj = dynamic_cast<ObjObject*>(objectPropertiesPair->getObject());
    QWidget *hierarchyWidget = hierarchy->findChild<QWidget *>("Hierarchy Widget");
    QTreeWidget *treeWidget = hierarchyWidget->findChild<QTreeWidget *>("Tree Widget");

    if(obj != nullptr)
    {
        ObjectTreeWidgetItem *object = new ObjectTreeWidgetItem(objectPropertiesPair, "Object");
        treeWidget->insertTopLevelItem(treeWidget->topLevelItemCount(),object);
        objectTreeWidgets->append(object);
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(objectPropertiesPair->getObject());
        if(vol != nullptr)
        {
            ObjectTreeWidgetItem *object = new ObjectTreeWidgetItem(objectPropertiesPair, "Object");
            treeWidget->insertTopLevelItem(treeWidget->topLevelItemCount(),object);
            objectTreeWidgets->append(object);
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

void VolumeWindow::treeWidgetItemClicked(QTreeWidgetItem * item, int col)
{
    CameraTreeWidgetItem * cameraItem = dynamic_cast<CameraTreeWidgetItem*>(item);
    if(cameraItem)
    {
        changeFocusedToCamera(cameraItem->getCameraPropertiesPair());
    }
    else
    {
        ObjectTreeWidgetItem * objectItem = dynamic_cast<ObjectTreeWidgetItem*>(item);
        if(objectItem)
        {
            changeFocusedToObject(objectItem->getObjectPropertiesPair());
        }
    }
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

    double *center;

    ObjObject *obj = dynamic_cast<ObjObject*>(objectPropertiesPair->getObject());
    if(obj != nullptr)
    {
        center = obj->getActor()->GetCenter();
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(objectPropertiesPair->getObject());
        if(vol != nullptr)
        {
            center = vol->getVolume()->GetCenter();
        }
    }
    cameraPropertiesPair->getCamera()->SetFocalPoint(center[0], center[1], center[2]);
    TransformEditorCamera *editorCamera = cameraPropertiesPair->getPropertiesDock()->findChild<TransformEditorCamera *>("Transform Editor Camera");
    editorCamera->updateFocalPoint(center);
    updateWidget();
}

void VolumeWindow::updateWidget()
{
    vtkWidget->GetRenderWindow()->Render();
}

void VolumeWindow::changeName(ObjectEditor *editor, QString name)
{
    for(int i = 0; i < objectTreeWidgets->length(); i++)
    {
        if(editor->getObject() == objectTreeWidgets->at(i)->getObjectPropertiesPair()->getObject())
        {
            objectTreeWidgets->at(i)->setText(0,  name.toStdString().c_str());
        }
    }
}

void VolumeWindow::createMesh(TifVolumeObject *vol)
{
    //marching cubes
    vtkSmartPointer<vtkMarchingCubes> surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface->SetInputData(vol->getData());
    surface->ComputeNormalsOn();
    float isoValue = 1000;
    surface->SetValue(0, isoValue);

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(surface->GetOutputPort());
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"), "/home/Desktop/PruebasMarchingCubesmarchingCubes.obj",tr("Images (*.obj)"));
    std::string filename = fileName.toStdString();

    QFile f( fileName );
    f.open( QIODevice::WriteOnly );

    //Write OBJ File
    vtkOBJExporter* objExporter = vtkOBJExporter::New();
    objExporter->SetFilePrefix(filename.c_str());
    objExporter->SetRenderWindow(renderWindow);
    objExporter->Write();

    renderWindow->Delete();

//    addObjectToHierarchyPanel(objectPropertiesPair);
//    changeFocusedToObject(objectPropertiesPair);
//    vtkWidget->GetRenderWindow()->Render();
}

void VolumeWindow::createSegmentation(TifVolumeObject * vol)
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("Scripts");
    string script = pluginsDir.absolutePath().toStdString() + "/evaluation_NN.py";
    string code = "python3 " + script;
    string fileName = std::tmpnam(nullptr);
    code = code + " > " + fileName;
    system(code.c_str());
}

void VolumeWindow::openMesh()
{

}
