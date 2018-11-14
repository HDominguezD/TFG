#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QtWidgets/QMainWindow>
#include "objectclasses/objobject.h"
#include "objectclasses/tifobject.h"
#include "core.h"

namespace Ui {
class RenderingWindow;
}

class RenderingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RenderingWindow(QWidget *parent, Core *core);
    ~RenderingWindow();

    void printObjects3D();
    void printObjects2D();
    void printVolObjects();

    Ui::RenderingWindow *getUi() const;

    QMenuBar *getToolBar() const;

private slots:
    void on_actionopen_file_triggered();

    void on_actionopen_stack_of_files_triggered();

    void on_horizontalSlider_valueChanged(int value);

    void on_actionopen_tif_Volume_triggered();

    void on_actionopen_tif_file_triggered();

private:
    void initializateSlider();
    void showOnlyToolBar();
    Ui::RenderingWindow *ui;
    Core *core;
    QToolBar *toolBar;
};

#endif // RENDERINGWINDOW_H
