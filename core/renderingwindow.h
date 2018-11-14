#ifndef RENDERINGWINDOW_H
#define RENDERINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class renderingWindow;
}

class renderingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit renderingWindow(QWidget *parent = nullptr);
    ~renderingWindow();

private:
    Ui::renderingWindow *ui;
};

#endif // RENDERINGWINDOW_H
