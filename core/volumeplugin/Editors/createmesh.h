#ifndef CREATEMESH_H
#define CREATEMESH_H
#include "QWidget"
#include "objectclasses/tifvolumeobject.h"
#include "Labels/clickablelabel.h"
#include "QPushButton"
#include "qlineedit.h"
#include "QGridLayout"


class CreateMesh: public QWidget
{
    Q_OBJECT
public:
    CreateMesh(QWidget *parent, TifVolumeObject *object);

private:
    TifVolumeObject *object;
    QPushButton *createMesh;
    QPushButton *addIsovalue;
    QList<QLineEdit *> *isovalues;
    ClickableLabel *label;
    QWidget *editor;
    QGridLayout *gridLayout;

    QLineEdit* createIsoLine();

private slots:
    void labelClicked();
    void createMeshCLicked();
    void addIsoLine();
    void removeIsoLine();

};


#endif // CREATEMESH_H
