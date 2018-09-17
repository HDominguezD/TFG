#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include <ObjectClasses/object3d.h>
#include <qvector.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>


class ObjObject : public Object3D
{
public:
    ObjObject();
    bool readObjectFromFile(std::string fileName);

    QVector<vtkSmartPointer<vtkPoints> > *getVertexes() const;
    void setVertexes(QVector<vtkSmartPointer<vtkPoints> > *value);

    QVector<vtkSmartPointer<vtkPolyData> > *getFaces() const;
    void setFaces(QVector<vtkSmartPointer<vtkPolyData> > *value);

private:
    QVector<vtkSmartPointer<vtkPoints>>* vertexes;
    QVector<vtkSmartPointer<vtkPolyData>>* faces;
};

#endif // OBJOBJECT_H
