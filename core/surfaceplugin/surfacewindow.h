#ifndef SURFACEWINDOW_H
#define SURFACEWINDOW_H

#include "renderingwindow.h"
#include "QVTKWidget.h"
#include "core.h"

class SurfaceWindow : public QDockWidget
{
    Q_OBJECT
public:
    SurfaceWindow(QWidget *parent = nullptr);
    bool initialize();
    void setCore(Core *value);
    RenderingWindow *getRenderingWindow() const;
    void setRenderingWindow(RenderingWindow *value);

private:
    QVTKWidget *vtkWidget;
    Core *core;
    RenderingWindow *renderingWindow;
};

#endif // SURFACEWINDOW_H
