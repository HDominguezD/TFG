#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H

#include "objectclasses/abstractclasses/object.h"
#include "QLineEdit"
#include "QCheckBox"
#include "QVTKWidget.h"

class ObjectEditor : public QWidget
{
    Q_OBJECT
public:
    ObjectEditor(QWidget *parent, Object *object, QVTKWidget *widget);

private:
    Object *object;
    QLineEdit *objectName;
    QCheckBox *visible;
    QVTKWidget *widget;


private slots:
    void updateObject();
    void visibleChanged(int status);
    void changeName();

signals:
    void changeObjectName(QString name);

};

#endif // OBJECTEDITOR_H
