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
    ui->removeArgumentButton->setIcon(QIcon::fromTheme("window-close"));

    connect(ui->argumentsLineEdit, SIGNAL(editingFinished()), this, SLOT(argumentsLineEditsEditingFinished()));
    connect(ui->openFileButton, SIGNAL(pressed()), this, SLOT(openFileButtonClicked()));
    connect(ui->addArgumentButton, SIGNAL(pressed()), this, SLOT(addArgumentButtonClicked()));
    connect(ui->removeArgumentButton, SIGNAL(pressed()), this, SLOT(removeArgumentButtonClicked()));
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
    QPushButton *removeButton = new QPushButton();
    removeButton->setIcon(QIcon::fromTheme("window-close"));

    QPushButton *addArgument = this->findChild<QPushButton*>("addArgumentButton");
    ui->gridLayout->removeWidget(addArgument);
    ui->gridLayout->addWidget(removeButton, argumentsLines->length() + 1, 0);
    ui->gridLayout->addWidget(argumentLineEdit, argumentsLines->length() + 1, 1);
    ui->gridLayout->addWidget(dirButton, argumentsLines->length() + 1, 2);
    QPair<QLineEdit*, QPushButton*>* pair = new QPair<QLineEdit*, QPushButton*>(argumentLineEdit, dirButton);
    argumentsLines->append(pair);
    ui->gridLayout->addWidget(addArgument, argumentsLines->length() + 1, 0);
    ui->scrollArea->setWidgetResizable(true);

    connect(argumentLineEdit, SIGNAL(editingFinished()), this, SLOT(argumentsLineEditsEditingFinished()));
    connect(dirButton, SIGNAL(pressed()), this, SLOT(openFileButtonClicked()));
    connect(removeButton, SIGNAL(pressed()), this, SLOT(removeArgumentButtonClicked()));
}

void PythonScriptsWindow::removeArgumentButtonClicked()
{
    QPushButton* removeArgument = qobject_cast<QPushButton*>(sender());
    int row;
    int index = ui->gridLayout->indexOf(removeArgument);
    row = index / ui->gridLayout->columnCount();
    QLineEdit *line = argumentsLines->at(row)->first;
    QPushButton *open = argumentsLines->at(row)->second;

    QPushButton *addArgument = this->findChild<QPushButton*>("addArgumentButton");
    ui->gridLayout->removeWidget(addArgument);
    ui->gridLayout->removeWidget(line);
    ui->gridLayout->removeWidget(open);
    ui->gridLayout->removeWidget(removeArgument);
    argumentsLines->removeAt(row);

    ui->gridLayout->addWidget(addArgument, argumentsLines->length() + 1, 0);

    line->deleteLater();
    open->deleteLater();
    removeArgument->deleteLater();
    ui->scrollArea->setWidgetResizable(true);

}
