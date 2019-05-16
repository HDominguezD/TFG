#include "applyconversionseditor.h"
#include "QVBoxLayout"

ApplyConversionsEditor::ApplyConversionsEditor(QWidget *parent, TifVolumeObject *object)
{
    this->setParent(parent);
    this->object = object;

    label = new ClickableLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("Apply Conversions");
    label->setAlignment(Qt::AlignCenter);
    label->setFixedHeight(20);

    editor = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(editor);
    vLayout->setAlignment(Qt::AlignTop);

    createSegmentation = new QPushButton(tr("Create Segmentation"), this);

    vLayout->addWidget(createSegmentation);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(label);
    layout->addWidget(editor);

    this->setLayout(layout);

    connect(label, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(createSegmentation, SIGNAL(pressed()), this, SLOT(sendCreateSegmentationClicked()));
}

TifVolumeObject *ApplyConversionsEditor::getObject() const
{
    return object;
}

void ApplyConversionsEditor::sendCreateSegmentationClicked()
{
    emit createSegmentationClicked(object);
}

void ApplyConversionsEditor::labelClicked()
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
