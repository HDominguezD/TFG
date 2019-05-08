#include "../applicationlib/renderingwindow.h"
#include "../applicationlib/core.h"
#include <QApplication>
#include <qsurfaceformat.h>
#include <QVTKOpenGLWidget.h>
#include <qtabwidget.h>
#include "pluginmanager/pluginmanager.h"
#include "qdir.h"

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

    QApplication a(argc, argv);

    Core *core = new Core();
    QWidget *parent = nullptr;

    RenderingWindow *w = new RenderingWindow(parent, core);
   // w->setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    w->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);

    string script = "~/Desktop/PythonScripts/evaluation_NN.py";
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("Scripts");
    string code = "ssh h.dominguez@212.128.1.49 '~/shared/anaconda3/bin/python3 ~/Desktop/PythonScripts/evaluation_NN.py'";

    //string code = "ssh h.dominguez@212.128.1.49  'nvcc --version'";

    //system(code.c_str());
    w->show();
    return a.exec();
}
