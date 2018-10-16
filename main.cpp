#include "renderingwindow.h"
#include "core.h"
#include <QApplication>
#include <qsurfaceformat.h>
#include <QVTKOpenGLWidget.h>

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
    Core *core = new Core();
    QWidget *parent = 0;
    QApplication a(argc, argv);
    RenderingWindow* w = new RenderingWindow(parent, core);
    w->show();

    return a.exec();
}
