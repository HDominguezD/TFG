#ifndef APPLYCONVERSIONSEDITOR_H
#define APPLYCONVERSIONSEDITOR_H
#include "QWidget"
#include "QPushButton"
#include "objectclasses/tifvolumeobject.h"

class ApplyConversionsEditor: public QWidget
{
    Q_OBJECT
public:
    ApplyConversionsEditor(QWidget *parent, TifVolumeObject *object);

    TifVolumeObject *getObject() const;

private:
    TifVolumeObject *object;
    QPushButton *createMesh;
    QPushButton *createSegmentation;

private slots:
    void sendCreateMeshClicked();
    void sendCreateSegmentationClicked();

signals:
    void createMeshClicked(TifVolumeObject* vol);
    void createSegmentationClicked(TifVolumeObject* vol);

};

#endif // APPLYCONVERSIONSEDITOR_H
