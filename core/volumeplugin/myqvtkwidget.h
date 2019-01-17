#ifndef MYQVTKWIDGET_H
#define MYQVTKWIDGET_H
#include "QVTKWidget.h"

class MyQVTKWidget : public QVTKWidget
{
public:
    MyQVTKWidget();

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MYQVTKWIDGET_H
