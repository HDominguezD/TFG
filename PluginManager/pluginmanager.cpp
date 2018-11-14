#include "pluginmanager.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

PluginManager::PluginManager()
{
    init();
}

void * PluginManager::init()
{
    void *handle;
    double (*cosine)(double);
    char *error;

    handle = dlopen ("Plugins/dinamiclibraryexample.so", RTLD_NOW);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }

    *(void **) (&cosine) = dlsym(handle, "cos");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
    printf("estoy en consola");
    double value = (*cosine)(2.0);
    printf ("%f\n", (*cosine)(2.0));
    dlclose(handle);
    loadPlugins();
}

void * PluginManager::loadPlugins()
{

}

void * PluginManager::getToolBar()
{

}
void * PluginManager::close()
{

}
const char * PluginManager::getType()
{

}
