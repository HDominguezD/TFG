#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QWidget>
#include <ObjectClasses/objobject.h>

namespace Ui {
class RenderingWindow;
}

class RenderingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RenderingWindow(QWidget *parent = 0);
    ~RenderingWindow();
    void printObjObject(ObjObject* obj);

private:
    Ui::RenderingWindow *ui;
};

#endif // RENDERINGWINDOW_H
