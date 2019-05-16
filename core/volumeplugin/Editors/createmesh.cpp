#include "createmesh.h"
#include "QVBoxLayout"
#include "QValidator"
#include <iomanip>
#include <sstream>
#include "QFileDialog"
#include "vtkAbstractVolumeMapper.h"
#include "QPushButton"
#include "QDesktopWidget"
#include "vtkRenderWindow.h"
#include "vtkTransform.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkMarchingCubes.h"
#include "vtkOBJExporter.h"
#include "vtkAbstractVolumeMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"



CreateMesh::CreateMesh(QWidget *parent, TifVolumeObject *object)
{
    this->setParent(parent);
    this->object = object;
    isovalues = new QList<QLineEdit*>();

    label = new ClickableLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("Marching cubes");
    label->setAlignment(Qt::AlignCenter);
    label->setFixedHeight(20);

    editor = new QWidget(this);
    gridLayout = new QGridLayout(editor);

    QLineEdit *isovalue = createIsoLine();
    stringstream stream;
    float value = (object->getMinValue() +  object->getMaxValue()) / 2;
    stream << fixed << setprecision(2) << value;
    isovalue->setText(stream.str().c_str());
    stream.str(std::string());
    isovalues->append(isovalue);

    addIsovalue = new QPushButton(tr("Add Isovalue"), this);
    createMesh = new QPushButton(tr("Create Mesh"), this);

    QPushButton *removeButton = new QPushButton();
    removeButton->setIcon(QIcon::fromTheme("window-close"));

    gridLayout->addWidget(isovalue, 0, 0);
    gridLayout->addWidget(removeButton, 0, 1);
    gridLayout->addWidget(addIsovalue, 1, 0);
    gridLayout->addWidget(createMesh, 2, 0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(label);
    layout->addWidget(editor);

    this->setLayout(layout);

    connect(addIsovalue, SIGNAL(pressed()), this, SLOT(addIsoLine()));
    connect(label, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(createMesh, SIGNAL(pressed()), this, SLOT(createMeshCLicked()));
    connect(removeButton, SIGNAL(pressed()), this, SLOT(removeIsoLine()));
}

QLineEdit *CreateMesh::createIsoLine()
{
    QRegExpValidator *val = new QRegExpValidator(QRegExp("[--+]?[0-9]+.[0-9][0-9]"));
    QLineEdit *isovalue = new QLineEdit(this);
    isovalue->setValidator(val);
    return isovalue;
}

void CreateMesh::labelClicked()
{
    if(editor->isVisible())
    {
        editor->setVisible(false);
        label->setStyleSheet("QLabel { background-color : #C4C4C0  ; }");
    }
    else
    {
        editor->setVisible(true);
        label->setStyleSheet("");
    }
}

void CreateMesh::addIsoLine()
{
    QLineEdit *isoLine = createIsoLine();
    QPushButton *removeButton = new QPushButton();
    removeButton->setIcon(QIcon::fromTheme("window-close"));

    gridLayout->removeWidget(addIsovalue);
    gridLayout->removeWidget(createMesh);
    gridLayout->addWidget(isoLine, isovalues->length() + 1, 0);
    gridLayout->addWidget(removeButton, isovalues->length() + 1, 1);
    gridLayout->addWidget(addIsovalue, isovalues->length() + 2, 0);
    gridLayout->addWidget(createMesh, isovalues->length() + 3, 0);
    isovalues->append(isoLine);

    connect(removeButton, SIGNAL(pressed()), this, SLOT(removeIsoLine()));
}

void CreateMesh::removeIsoLine()
{
    QPushButton* removeArgument = qobject_cast<QPushButton*>(sender());
    int row;
    int index = gridLayout->indexOf(removeArgument);
    row = index / gridLayout->columnCount();
    QLineEdit *line = isovalues->at(row);
    gridLayout->removeWidget(line);
    line->deleteLater();
    isovalues->removeOne(line);
    gridLayout->removeWidget(removeArgument);
    removeArgument->deleteLater();

}

void CreateMesh::createMeshCLicked()
{
    //marching cubes
    vtkSmartPointer<vtkMarchingCubes> surface = vtkSmartPointer<vtkMarchingCubes>::New();
    surface->SetInputData(object->getData());
    surface->ComputeNormalsOn();


    for(int i = 0; i < isovalues->length(); i++)
    {
        surface->SetValue(i, isovalues->at(i)->text().toDouble());
    }

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(surface->GetOutputPort());
    mapper->ScalarVisibilityOff();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save File"), "marchingCubes",tr("Images (*.obj)"));
    std::string filename = fileName.toStdString();

    QFile f( fileName );
    f.open( QIODevice::WriteOnly );

    //Write OBJ File
    vtkOBJExporter* objExporter = vtkOBJExporter::New();
    objExporter->SetFilePrefix(filename.c_str());
    objExporter->SetRenderWindow(renderWindow);
    objExporter->Write();

    renderWindow->Delete();
}
