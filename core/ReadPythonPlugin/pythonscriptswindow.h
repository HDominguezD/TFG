#ifndef PYTHONSCRIPTSWINDOW_H
#define PYTHONSCRIPTSWINDOW_H

#include <QMainWindow>
#include "QPair"
#include "qlineedit.h"
#include "QPushButton"

using namespace std;

namespace Ui {
class PythonScriptsWindow;
}

class PythonScriptsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PythonScriptsWindow(QWidget *parent = 0);
    ~PythonScriptsWindow();

private slots:

    void on_CancelOkbuttonBox_rejected();

    void on_CancelOkbuttonBox_accepted();

    void on_openScriptButton_clicked();

    void openFileButtonClicked();

    void on_parametersLineEdit_editingFinished();

    void on_scriptLineEdit_editingFinished();

    void argumentsLineEditsEditingFinished();

    void addArgumentButtonClicked();

private:
    Ui::PythonScriptsWindow *ui;
    QList<QPair<QLineEdit*, QPushButton*>*>* argumentsLines;
    string arguments;
    string paramenters;
    string scriptPath;
};

#endif // PYTHONSCRIPTSWINDOW_H
