#include "objreader.h"
#include <vtkOBJReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <string>
#include <qstringlist.h>
#include <qfiledialog.h>
#include <QObject>

using namespace std;
ObjReader::ObjReader()
{

   QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open File"),"/path/to/file/",QObject::tr("Mesh Files (*.obj)"));

  string filename = fileNames.at(0).toStdString();
  vtkSmartPointer<vtkOBJReader> reader =
  vtkSmartPointer<vtkOBJReader>::New();
  reader->SetFileName(filename.c_str());
  reader->Update();

  // Visualize
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(.3, .6, .3); // Background color green

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindowInteractor->Start();
}
