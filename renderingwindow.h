#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QWidget>
#include <ObjectClasses/objobject.h>
#include <core.h>

namespace Ui {
class RenderingWindow;
}

class RenderingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RenderingWindow(QWidget *parent, Core *core);
    ~RenderingWindow();
    void printObjObject(Object3D* obj);
    void printObjects();

private:
    Ui::RenderingWindow *ui;
    Core *core;
};

#endif // RENDERINGWINDOW_H
