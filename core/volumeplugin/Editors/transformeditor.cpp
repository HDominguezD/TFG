#include "transformeditor.h"
#include "QLabel"
#include "QGridLayout"
#include "QLineEdit"
#include "QIntValidator"
#include "QFont"

TransformEditor::TransformEditor(QWidget *parent) : QWidget(parent)
{
    QFont *font = new QFont(this->font());
    font->setPointSize(9);
    this->setFont(*font);
    QGridLayout *layout = new QGridLayout(this);

    QLabel *position = new QLabel(tr("Position"));
    QLabel *positionX = new QLabel(tr("X"));
    QLineEdit *positionXInput = new QLineEdit(this);
    positionXInput->setValidator( new QIntValidator(0));
    QLabel *positionY = new QLabel(tr("Y"));
    QLineEdit *positionYInput = new QLineEdit(this);
    positionYInput->setValidator( new QIntValidator(0));
    QLabel *positionZ = new QLabel(tr("Z"));
    QLineEdit *positionZInput = new QLineEdit(this);
    positionZInput->setValidator( new QIntValidator(0));

    QLabel *rotation = new QLabel(tr("Rotation"));
    QLabel *rotationX = new QLabel(tr("X"));
    QLineEdit *rotationXInput = new QLineEdit(this);
    rotationXInput->setValidator( new QIntValidator(0));
    QLabel *rotationY = new QLabel(tr("Y"));
    QLineEdit *rotationYInput = new QLineEdit(this);
    rotationYInput->setValidator( new QIntValidator(0));
    QLabel *rotationZ = new QLabel(tr("Z"));
    QLineEdit *rotationZInput = new QLineEdit(this);
    rotationZInput->setValidator( new QIntValidator(0));

    QLabel *scale = new QLabel(tr("Scale"));
    QLabel *scaleX = new QLabel(tr("X"));
    QLineEdit *scaleXInput = new QLineEdit(this);
    scaleXInput->setValidator( new QIntValidator(0));
    QLabel *scaleY = new QLabel(tr("Y"));
    QLineEdit *scaleYInput = new QLineEdit(this);
    scaleYInput->setValidator( new QIntValidator(0));
    QLabel *scaleZ = new QLabel(tr("Z"));
    QLineEdit *scaleZInput = new QLineEdit(this);
    scaleZInput->setValidator( new QIntValidator(0));

    layout->addWidget(position, 0, 0);
    layout->addWidget(positionX, 0, 1);
    layout->addWidget(positionXInput, 0, 2);
    layout->addWidget(positionY, 0, 3);
    layout->addWidget(positionYInput, 0, 4);
    layout->addWidget(positionZ, 0, 5);
    layout->addWidget(positionZInput, 0, 6);

    layout->addWidget(rotation, 1, 0);
    layout->addWidget(rotationX, 1, 1);
    layout->addWidget(rotationXInput, 1, 2);
    layout->addWidget(rotationY, 1, 3);
    layout->addWidget(rotationYInput, 1, 4);
    layout->addWidget(rotationZ, 1, 5);
    layout->addWidget(rotationZInput, 1, 6);

    layout->addWidget(scale, 2, 0);
    layout->addWidget(scaleX, 2, 1);
    layout->addWidget(scaleXInput, 2, 2);
    layout->addWidget(scaleY, 2, 3);
    layout->addWidget(scaleYInput, 2, 4);
    layout->addWidget(scaleZ, 2, 5);
    layout->addWidget(scaleZInput, 2, 6);

    this->setLayout(layout);
}
