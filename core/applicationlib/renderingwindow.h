#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QtWidgets/QMainWindow>
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

private:
    void showOnlyToolBar();
    Ui::RenderingWindow *ui;
    Core *core;
    QToolBar *toolBar;
};

#endif // RENDERINGWINDOW_H
