#include "applyconversionseditor.h"
#include "QVBoxLayout"

ApplyConversionsEditor::ApplyConversionsEditor(QWidget *parent, TifVolumeObject *object)
{
    this->setParent(parent);
    this->object = object;
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    createMesh = new QPushButton(tr("create Mesh"), this);
    createSegmentation = new QPushButton(tr("Create Segmentation"), this);

    layout->addWidget(createMesh);
    layout->addWidget(createSegmentation);

    connect(createMesh, SIGNAL(pressed()), this, SLOT(sendCreateMeshClicked()));
    connect(createSegmentation, SIGNAL(pressed()), this, SLOT(sendCreateSegmentationClicked()));
}

TifVolumeObject *ApplyConversionsEditor::getObject() const
{
    return object;
}

void ApplyConversionsEditor::sendCreateMeshClicked()
{
    emit createMeshClicked(object);
}

void ApplyConversionsEditor::sendCreateSegmentationClicked()
{
    emit createSegmentationClicked(object);
}
