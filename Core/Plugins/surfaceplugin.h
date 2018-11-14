#ifndef SURFACEPLUGIN_H
#define SURFACEPLUGIN_H
#include "plugin.h"

class surfacePlugin : Plugin
{
public:
    surfacePlugin();
    void init();
    void load();
    QMenu* getMenu(QMenuBar* bar);
    const char* getType();
    void close();

private slots:
    void open();
};

#endif // SURFACEPLUGIN_H
