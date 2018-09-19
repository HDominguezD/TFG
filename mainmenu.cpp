#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "loaddata.h"
#include <qwidget.h>

mainMenu::mainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
    core = new Core();
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::on_loadData_clicked(bool checked)
{
    if(!checked){
        QWidget *parent = 0;
        LoadData* w = new LoadData(parent, core);
        w->show();
        ui->loadData->setDisabled(true);
    }
}
