#ifndef PLUGIN_H
#define PLUGIN_H

#include <qmenu.h>
#include <QMenuBar>
#include <QMainWindow>
#include "../renderingwindow.h"
#include "ui_renderingwindow.h"

class Plugin : public QObject
{
    Q_OBJECT
public:
    virtual void init() = 0;
    virtual QString description() = 0;
    virtual QString name() = 0; 
    virtual void load() = 0;
    //virtual QMenu* getMenu(QMenuBar* bar) = 0;
    virtual const char * getType() = 0;
    virtual void close() = 0;

    Ui::RenderingWindow *getUi() const{
        return ui;
    }
    void setUi(Ui::RenderingWindow *value){
        this->ui = value;
    }

private:
    Ui::RenderingWindow *ui;
};


#endif // PLUGIN_H
