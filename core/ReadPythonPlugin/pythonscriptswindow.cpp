#include "pythonscriptswindow.h"
#include "ui_pythonscriptswindow.h"
#include "QFileDialog"

PythonScriptsWindow::PythonScriptsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PythonScriptsWindow)
{
    ui->setupUi(this);

    paramenters = "";
    scriptPath  = "";
    arguments  = "";
    outputDir  = "";

        ui->scriptLineEdit->setText(arguments.c_str());
}

PythonScriptsWindow::~PythonScriptsWindow()
{
    delete ui;
}

void PythonScriptsWindow::on_CancelOkbuttonBox_accepted()
{
    string pythonCode = paramenters + " " + scriptPath + " " + arguments + " " + outputDir;
    string code = "python3 " + pythonCode;
    system(code.c_str());
    this->close();
    this->~PythonScriptsWindow();
}

void PythonScriptsWindow::on_CancelOkbuttonBox_rejected()
{
    this->close();
    this->~PythonScriptsWindow();
}

void PythonScriptsWindow::on_openScriptButton_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Select python script"),"/path/to/file/",QObject::tr("Python scripts (*.py)"));
    if(fileNames.isEmpty())
    {
        return;
    }

    scriptPath = fileNames.at(0).toStdString();
    ui->scriptLineEdit->setText(scriptPath.c_str());
}

void PythonScriptsWindow::on_openFileButton_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Argument File"),"/path/to/file/",QObject::tr("Arguments Files (*)"));
    if(fileNames.isEmpty())
    {
        return;
    }

    arguments = fileNames.at(0).toStdString();
    ui->argumentsLineEdit->setText(arguments.c_str());
}

void PythonScriptsWindow::on_openDirectoryButton_clicked()
{
    QDir directory = QFileDialog::getExistingDirectory(Q_NULLPTR, QObject::tr("select directory"));
    if(!directory.exists())
    {
        return;
    }
    outputDir = directory.absolutePath().toStdString();
    ui->outputLineEdit->setText(outputDir.c_str());
}

void PythonScriptsWindow::on_parametersLineEdit_editingFinished()
{
    paramenters = ui->parametersLineEdit->text().toStdString();
}

void PythonScriptsWindow::on_scriptLineEdit_editingFinished()
{
    scriptPath = ui->scriptLineEdit->text().toStdString();
}

void PythonScriptsWindow::on_argumentsLineEdit_editingFinished()
{
    arguments = ui->argumentsLineEdit->text().toStdString();
}

void PythonScriptsWindow::on_outputLineEdit_editingFinished()
{
    outputDir = ui->outputLineEdit->text().toStdString();
}
