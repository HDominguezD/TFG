#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "loaddata.h"

mainMenu::mainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::on_loadData_clicked(bool checked)
{
    if(!checked){
        LoadData* w = new LoadData();
        w->show();
        ui->loadData->setDisabled(true);
    }
}
