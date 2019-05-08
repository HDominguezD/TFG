#ifndef APPLYCONVERSIONSEDITOR_H
#define APPLYCONVERSIONSEDITOR_H
#include "QWidget"
#include "QPushButton"
#include "objectclasses/tifvolumeobject.h"
#include "Labels/clickablelabel.h"

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
    ClickableLabel *label;
    QWidget *editor;

private slots:
    void sendCreateMeshClicked();
    void sendCreateSegmentationClicked();
    void labelClicked();

signals:
    void createMeshClicked(TifVolumeObject* vol);
    void createSegmentationClicked(TifVolumeObject* vol);

};

#endif // APPLYCONVERSIONSEDITOR_H
