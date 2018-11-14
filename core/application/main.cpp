#include "../applicationlib/renderingwindow.h"
#include "../applicationlib/core.h"
#include <QApplication>
#include <qsurfaceformat.h>
#include <QVTKOpenGLWidget.h>
#include "../applicationlib/pluginmanager/pluginmanager.h"

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());
    Core *core = new Core();
    QWidget *parent = nullptr;
    QApplication a(argc, argv);
    RenderingWindow* w = new RenderingWindow(parent, core);
    w->setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    w->show();

    return a.exec();
}
