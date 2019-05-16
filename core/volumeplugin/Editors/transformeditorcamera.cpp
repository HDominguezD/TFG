#include "transformeditorcamera.h"
#include "QGridLayout"
#include "QLabel"
#include "QIntValidator"
#include "vtkRenderWindow.h"
#include <iomanip>
#include <sstream>

using namespace std;

TransformEditorCamera::TransformEditorCamera(QWidget *parent, vtkCamera *camera, QVTKWidget *vtkWidget)
{
    this->digits = 3;
    this->setParent(parent);
    this->camera = camera;
    this->vtkWidget = vtkWidget;

    QRegExpValidator *val = new QRegExpValidator(QRegExp("[--+]?[0-9]+.[0-9][0-9]"));

    QFont *font = new QFont(this->font());
    font->setPointSize(9);
    this->setFont(*font);

    label = new ClickableLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("Transform");
    label->setAlignment(Qt::AlignCenter);
    label->setFixedHeight(20);

    editor = new QWidget(this);

    QGridLayout *gridLayout = new QGridLayout(editor);

    QLabel *position = new QLabel(tr("Position"));
    QLabel *positionX = new QLabel(tr("X"));
    positionXInput = new QLineEdit(this);
    positionXInput->setObjectName("PositionXInput");
    positionXInput->setValidator( val);

    QLabel *positionY = new QLabel(tr("Y"));
    positionYInput = new QLineEdit(this);
    positionYInput->setObjectName("PositionYInput");
    positionYInput->setValidator( val);

    QLabel *positionZ = new QLabel(tr("Z"));
    positionZInput = new QLineEdit(this);
    positionZInput->setObjectName("PositionZInput");
    positionZInput->setValidator( val);

    QLabel *fPoint = new QLabel(tr("Focal Point"));
    QLabel *fPointX = new QLabel(tr("X"));
    fPointXInput = new QLineEdit(this);
    fPointXInput->setObjectName("FPointXInput");
    fPointXInput->setValidator( val);

    QLabel *fPointY = new QLabel(tr("Y"));
    fPointYInput = new QLineEdit(this);
    fPointYInput->setObjectName("FPointYInput");
    fPointYInput->setValidator( val);

    QLabel *fPointZ = new QLabel(tr("Z"));
    fPointZInput = new QLineEdit(this);
    fPointZInput->setObjectName("FPointZInput");
    fPointZInput->setValidator( val);

    gridLayout->addWidget(position, 0, 0);
    gridLayout->addWidget(positionX, 0, 1);
    gridLayout->addWidget(positionXInput, 0, 2);
    gridLayout->addWidget(positionY, 0, 3);
    gridLayout->addWidget(positionYInput, 0, 4);
    gridLayout->addWidget(positionZ, 0, 5);
    gridLayout->addWidget(positionZInput, 0, 6);

    gridLayout->addWidget(fPoint, 2, 0);
    gridLayout->addWidget(fPointX, 2, 1);
    gridLayout->addWidget(fPointXInput, 2, 2);
    gridLayout->addWidget(fPointY, 2, 3);
    gridLayout->addWidget(fPointYInput, 2, 4);
    gridLayout->addWidget(fPointZ, 2, 5);
    gridLayout->addWidget(fPointZInput, 2, 6);

    double *pos = camera->GetPosition();
    double *fP = camera->GetFocalPoint();
    stringstream stream;

    stream << fixed << setprecision(2) << pos[0];
    positionXInput->setText(stream.str().c_str());
    stream.str(std::string());
    stream << fixed << setprecision(2) << pos[1];
    positionYInput->setText(stream.str().c_str());
    stream.str(std::string());
    stream << fixed << setprecision(2) << pos[2];
    positionZInput->setText(stream.str().c_str());
    stream.str(std::string());

    stream << fixed << setprecision(2) << fP[0];
    fPointXInput->setText(stream.str().c_str());
    stream.str(std::string());
    stream << fixed << setprecision(2) << fP[1];
    fPointYInput->setText(stream.str().c_str());
    stream.str(std::string());
    stream << fixed << setprecision(2) << fP[2];
    fPointZInput->setText(stream.str().c_str());
    stream.str(std::string());

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(label);
    layout->addWidget(editor);

    this->setLayout(layout);

    connect(label, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(positionXInput, SIGNAL(textEdited(QString)), this, SLOT(updateCamera(QString)));
    connect(positionYInput, SIGNAL(textEdited(QString)), this, SLOT(updateCamera(QString)));
    connect(positionZInput, SIGNAL(textEdited(QString)), this, SLOT(updateCamera(QString)));

    connect(fPointXInput, SIGNAL(textEdited(QString)), this, SLOT(updateCamera(QString)));
    connect(fPointYInput, SIGNAL(textEdited(QString)), this, SLOT(updateCamera(QString)));
    connect(fPointZInput, SIGNAL(textEdited(QString)), this, SLOT(updateCamera(QString)));
}

void TransformEditorCamera::updateFocalPoint(double *fP)
{
    fPointXInput->setText(to_string(fP[0]).c_str());
    fPointYInput->setText(to_string(fP[1]).c_str());
    fPointZInput->setText(to_string(fP[2]).c_str());
}

void TransformEditorCamera::updateCamera(QString text)
{
    double pos[3];
    pos[0] = positionXInput->text().toDouble();
    pos[1] = positionYInput->text().toDouble();
    pos[2] = positionZInput->text().toDouble();

    double fp[3];
    fp[0] = fPointXInput->text().toDouble();
    fp[1] = fPointYInput->text().toDouble();
    fp[2] = fPointZInput->text().toDouble();

    camera->SetPosition(pos);
    camera->SetFocalPoint(fp);
    vtkWidget->GetRenderWindow()->Render();
}

void TransformEditorCamera::labelClicked()
{
    if(editor->isVisible())
    {
        editor->setVisible(false);
        label->setStyleSheet("QLabel { background-color : #C4C4C0  ; }");
    }
    else
    {
        editor->setVisible(true);
        label->setStyleSheet("");

    }
}
