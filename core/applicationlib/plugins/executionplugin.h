#ifndef EXECUTIONPLUGIN_H
#define EXECUTIONPLUGIN_H
#include <QtPlugin>

using namespace std;

class ExecutionPlugin
{
public:
    virtual void load();
};

#define ExecutionPlugin_iid "application::Plugin/1.0"

Q_DECLARE_INTERFACE(ExecutionPlugin, ExecutionPlugin_iid)

#endif // EXECUTIONPLUGIN_H
