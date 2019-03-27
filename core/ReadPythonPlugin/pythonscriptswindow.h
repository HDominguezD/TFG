#ifndef PYTHONSCRIPTSWINDOW_H
#define PYTHONSCRIPTSWINDOW_H

#include <QMainWindow>
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

    void on_openFileButton_clicked();

    void on_openDirectoryButton_clicked();

    void on_parametersLineEdit_editingFinished();

    void on_scriptLineEdit_editingFinished();

    void on_argumentsLineEdit_editingFinished();

    void on_outputLineEdit_editingFinished();

private:
    Ui::PythonScriptsWindow *ui;

    string arguments;
    string outputDir;
    string paramenters;
    string scriptPath;
};

#endif // PYTHONSCRIPTSWINDOW_H
