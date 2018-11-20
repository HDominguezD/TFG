#include "../applicationlib/renderingwindow.h"
#include "../applicationlib/core.h"
#include <QApplication>
#include <qsurfaceformat.h>
#include <QVTKOpenGLWidget.h>
#include "pluginmanager/pluginmanager.h"

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

    QApplication a(argc, argv);

    Core *core = new Core();
    QWidget *parent = nullptr;

    RenderingWindow *w = new RenderingWindow(parent, core);
    w->setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    w->show();

    return a.exec();
}
