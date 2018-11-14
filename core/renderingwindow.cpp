#include "renderingwindow.h"
#include "ui_renderingwindow.h"

renderingWindow::renderingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::renderingWindow)
{
    ui->setupUi(this);
}

renderingWindow::~renderingWindow()
{
    delete ui;
}
