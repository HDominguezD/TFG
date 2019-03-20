#include "transformeditorcamera.h"
#include "QGridLayout"
#include "QLabel"
#include "QIntValidator"
#include "vtkRenderWindow.h"

using namespace std;

TransformEditorCamera::TransformEditorCamera(QWidget *parent, vtkCamera *camera, QVTKWidget *vtkWidget)
{
    this->digits = 3;
    this->setParent(parent);
    this->camera = camera;
    this->vtkWidget = vtkWidget;

    QDoubleValidator *val = new QDoubleValidator(0);
    val->setDecimals(digits);

    QFont *font = new QFont(this->font());
    font->setPointSize(9);
    this->setFont(*font);
    QGridLayout *layout = new QGridLayout(this);

    QLabel *position = new QLabel(tr("Position"));
    QLabel *positionX = new QLabel(tr("X"));
    positionXInput = new QLineEdit(this);
    positionXInput->setObjectName("PositionXInput");
    positionXInput->setMaxLength(6);
    positionXInput->setValidator( val);

    QLabel *positionY = new QLabel(tr("Y"));
    positionYInput = new QLineEdit(this);
    positionYInput->setObjectName("PositionYInput");
    positionYInput->setMaxLength(6);
    positionYInput->setValidator( val);

    QLabel *positionZ = new QLabel(tr("Z"));
    positionZInput = new QLineEdit(this);
    positionZInput->setObjectName("PositionZInput");
    positionZInput->setMaxLength(6);
    positionZInput->setValidator( val);

    QLabel *fPoint = new QLabel(tr("Focal Point"));
    QLabel *fPointX = new QLabel(tr("X"));
    fPointXInput = new QLineEdit(this);
    fPointXInput->setObjectName("FPointXInput");
    fPointXInput->setMaxLength(6);
    fPointXInput->setValidator( val);

    QLabel *fPointY = new QLabel(tr("Y"));
    fPointYInput = new QLineEdit(this);
    fPointYInput->setObjectName("FPointYInput");
    fPointYInput->setMaxLength(6);
    fPointYInput->setValidator( val);

    QLabel *fPointZ = new QLabel(tr("Z"));
    fPointZInput = new QLineEdit(this);
    fPointZInput->setObjectName("FPointZInput");
    fPointZInput->setMaxLength(6);
    fPointZInput->setValidator( val);

    layout->addWidget(position, 0, 0);
    layout->addWidget(positionX, 0, 1);
    layout->addWidget(positionXInput, 0, 2);
    layout->addWidget(positionY, 0, 3);
    layout->addWidget(positionYInput, 0, 4);
    layout->addWidget(positionZ, 0, 5);
    layout->addWidget(positionZInput, 0, 6);

    layout->addWidget(fPoint, 2, 0);
    layout->addWidget(fPointX, 2, 1);
    layout->addWidget(fPointXInput, 2, 2);
    layout->addWidget(fPointY, 2, 3);
    layout->addWidget(fPointYInput, 2, 4);
    layout->addWidget(fPointZ, 2, 5);
    layout->addWidget(fPointZInput, 2, 6);

    double *pos = camera->GetPosition();
    double *fP = camera->GetFocalPoint();

    positionXInput->setText(to_string(pos[0]).c_str());
    positionYInput->setText(to_string(pos[1]).c_str());
    positionZInput->setText(to_string(pos[2]).c_str());

    fPointXInput->setText(to_string(fP[0]).c_str());
    fPointYInput->setText(to_string(fP[1]).c_str());
    fPointZInput->setText(to_string(fP[2]).c_str());

    this->setLayout(layout);

    connect(positionXInput, SIGNAL(editingFinished()), this, SLOT(updateCamera()));
    connect(positionYInput, SIGNAL(editingFinished()), this, SLOT(updateCamera()));
    connect(positionZInput, SIGNAL(editingFinished()), this, SLOT(updateCamera()));

    connect(fPointXInput, SIGNAL(editingFinished()), this, SLOT(updateCamera()));
    connect(fPointYInput, SIGNAL(editingFinished()), this, SLOT(updateCamera()));
    connect(fPointZInput, SIGNAL(editingFinished()), this, SLOT(updateCamera()));
}

void TransformEditorCamera::updateFocalPoint(double *fP)
{
    fPointXInput->setText(to_string(fP[0]).c_str());
    fPointYInput->setText(to_string(fP[1]).c_str());
    fPointZInput->setText(to_string(fP[2]).c_str());
}

void TransformEditorCamera::updateCamera()
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
