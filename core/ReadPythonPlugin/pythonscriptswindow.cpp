#include "pythonscriptswindow.h"
#include "ui_pythonscriptswindow.h"
#include "QFileDialog"
#include "QFileIconProvider"

PythonScriptsWindow::PythonScriptsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PythonScriptsWindow)
{
    ui->setupUi(this);

    paramenters = "";
    scriptPath  = "";

    arguments  = "";
    ui->addArgumentButton->setObjectName("addArgumentButton");

    argumentsLines = new QList<QPair<QLineEdit*, QPushButton*>*>();
    QPair<QLineEdit*, QPushButton*>* pair = new QPair<QLineEdit*, QPushButton*>(ui->argumentsLineEdit, ui->openFileButton);
    argumentsLines->append(pair);
    ui->openFileButton->setIcon(QIcon::fromTheme("document-open"));
    ui->openScriptButton->setIcon(QIcon::fromTheme("folder-open"));

    connect(ui->argumentsLineEdit, SIGNAL(editingFinished()), this, SLOT(argumentsLineEditsEditingFinished()));
    connect(ui->openFileButton, SIGNAL(pressed()), this, SLOT(openFileButtonClicked()));
    connect(ui->addArgumentButton, SIGNAL(pressed()), this, SLOT(addArgumentButtonClicked()));

}

PythonScriptsWindow::~PythonScriptsWindow()
{
    delete ui;
}

void PythonScriptsWindow::on_CancelOkbuttonBox_accepted()
{
    string pythonCode = paramenters + " " + scriptPath + " " + arguments;
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

void PythonScriptsWindow::openFileButtonClicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Argument File"),"/path/to/file/",QObject::tr("Arguments Files (*)"));
    if(fileNames.isEmpty())
    {
        return;
    }

    arguments = fileNames.at(0).toStdString();
    ui->argumentsLineEdit->setText(arguments.c_str());
}

void PythonScriptsWindow::on_parametersLineEdit_editingFinished()
{
    paramenters = ui->parametersLineEdit->text().toStdString();
}

void PythonScriptsWindow::on_scriptLineEdit_editingFinished()
{
    scriptPath = ui->scriptLineEdit->text().toStdString();
}

void PythonScriptsWindow::argumentsLineEditsEditingFinished()
{
    arguments = "";
    for(int i = 0; i < argumentsLines->length(); i++)
    {
        arguments += " " + argumentsLines->at(i)->first->text().toStdString();
    }
}

void PythonScriptsWindow::addArgumentButtonClicked()
{
    QLineEdit *argumentLineEdit = new QLineEdit();
    QPushButton *dirButton = new QPushButton();

    dirButton->setIcon(QIcon::fromTheme("document-open"));
    ui->addArgumentButton->objectName();
    QPushButton *addArgument = this->findChild<QPushButton*>("addArgumentButton");
    ui->gridLayout->removeWidget(addArgument);
    ui->gridLayout->addWidget(argumentLineEdit, argumentsLines->length() + 2, 0);
    ui->gridLayout->addWidget(dirButton, argumentsLines->length() + 2, 1);
    QPair<QLineEdit*, QPushButton*>* pair = new QPair<QLineEdit*, QPushButton*>(argumentLineEdit, dirButton);
    argumentsLines->append(pair);
    ui->gridLayout->addWidget(addArgument, argumentsLines->length() + 3, 0);
    ui->scrollArea->setWidgetResizable(true);

    connect(argumentLineEdit, SIGNAL(editingFinished()), this, SLOT(argumentsLineEditsEditingFinished()));
    connect(dirButton, SIGNAL(pressed()), this, SLOT(openFileButtonClicked()));
}
