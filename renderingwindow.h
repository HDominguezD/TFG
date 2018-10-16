#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QMainWindow>
#include <ObjectClasses/objobject.h>
#include <ObjectClasses/tifobject.h>
#include <core.h>

namespace Ui {
class RenderingWindow;
}

class RenderingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RenderingWindow(QWidget *parent, Core *core);
    ~RenderingWindow();
    void printObjObject(Object3D* obj);
    void printTifObject(Object2D* obj);
    void printObjects3D();
    void printObjects2D();

private slots:
    void on_actionopen_file_triggered();

    void on_actionopen_stack_of_files_triggered();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::RenderingWindow *ui;
    Core *core;
};

#endif // RENDERINGWINDOW_H
