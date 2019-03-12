#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include "core.h"
#include "renderingwindow.h"
#include "QSlider"

class ImageWindow: public QDockWidget
{
    Q_OBJECT
public:
    ImageWindow(QWidget *parent = nullptr);
    bool initializeTif();
    bool initializeTifStack();
    void setCore(Core *value);
    RenderingWindow *getRenderingWindow() const;
    void setRenderingWindow(RenderingWindow *value);

private:
    void initializeSlider();

    QSlider *slider;
    QVTKWidget *vtkWidget;
    Core *core;
    Object *object;
    RenderingWindow *renderingWindow;

private slots:
    void changeImageShowed(int value);
};

#endif // IMAGEWINDOW_H
