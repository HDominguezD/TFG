#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H
#include <QVTKWidget.h>
#include <Editors/transformeditorObject.h>

class GraphicWindow: public QVTKWidget
{
    Q_OBJECT

public:

    GraphicWindow(QWidget *parent = NULL);

    ~GraphicWindow();


    void setTransformEditor(TransformEditorObject *value);

protected:


    virtual void keyPressEvent(QKeyEvent *event);

    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    TransformEditorObject *transformEditor;

};


#endif // GRAPHICWINDOW_H
