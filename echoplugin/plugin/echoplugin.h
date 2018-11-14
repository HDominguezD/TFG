#ifndef ECHOPLUGIN_H
#define ECHOPLUGIN_H

//#include <QObject>
//#include <QtPlugin>
//#include "echointerface.h"

//class EchoPlugin : public QObject, EchoInterface
//{
//    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Examples.EchoInterface" FILE "echoplugin.json")
//    Q_INTERFACES(EchoInterface)

////public:
////    QString echo(const QString &message);
//public:
//    void load();
////    const char* getType();
////    void close();

//private slots:
//    void open();
//};

#include "plugin.h"

class EchoPlugin : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application::Plugin/2.0" FILE "echoplugin.json")
    Q_INTERFACES(Plugin)
public:
    void load();
    const char* getType();
    void close();

private slots:
    void open();
};



#endif
