#include "graphicwindow.h"
#include "QKeyEvent"

GraphicWindow::GraphicWindow(QWidget *parent)
{
    this->setParent(parent);
}

GraphicWindow::~GraphicWindow()
{
    this->~QVTKWidget();
}

void GraphicWindow::keyPressEvent(QKeyEvent *event)
{
    if(transformEditor)
    {
        double tras[3];
            tras[0] = transformEditor->positionXInput->text().toDouble();
            tras[1] = transformEditor->positionYInput->text().toDouble();
            tras[2] = transformEditor->positionZInput->text().toDouble();

        if(event->key() == Qt::Key_Left)
        {
            tras[0]--;
        }
        else if(event->key() == Qt::Key_Right)
        {
            tras[0]++;
        }
        else if(event->key() == Qt::Key_Down)
        {
            tras[1]--;
        }
        else if(event->key() == Qt::Key_Up)
        {
            tras[1]++;
        }
        else if(event->key() == Qt::Key_1)
        {
            tras[2]--;
        }
        else if(event->key() == Qt::Key_2)
        {
            tras[2]++;
        }
        transformEditor->positionXInput->setText(to_string(tras[0]).c_str());
        transformEditor->positionYInput->setText(to_string(tras[1]).c_str());
        transformEditor->positionZInput->setText(to_string(tras[2]).c_str());

        transformEditor->updateObject("");
    }
}

void GraphicWindow::keyReleaseEvent(QKeyEvent *event)
{

}

void GraphicWindow::setTransformEditor(TransformEditorObject *value)
{
    transformEditor = value;
}
