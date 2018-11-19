#ifndef PLUGIN_H
#define PLUGIN_H

#include "../renderingwindow.h"
#include "QtPlugin"

class Plugin
{
public:
    virtual void load() = 0;
    virtual const char * getType() = 0;
    virtual void close() = 0;
    virtual void setRenderingWindow(RenderingWindow *value){ renderingWindow = value;}
    virtual RenderingWindow *getRenderingWindow() const { return renderingWindow;}
    Core *getCore() const {return core;}
    void setCore(Core *value){core = value;}

    RenderingWindow *renderingWindow;
    Core *core;
};

#define PluginInterface_iid "application::Plugin/2.0"

Q_DECLARE_INTERFACE(Plugin, PluginInterface_iid)

#endif // PLUGIN_H