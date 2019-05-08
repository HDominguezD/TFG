#include "hoverpoints.h"
#include "objectclasses/tifvolumeobject.h"
#include "vtkVolumeProperty.h"
#include "Labels/clickablelabel.h"

class ColorPicker : public QWidget
{
  Q_OBJECT
public:
  QImage m_shade;
  QPolygonF points() const;
  ColorPicker(QWidget *parent);
  HoverPoints *hoverPoints() const
  {
    return m_hoverPoints;
  }
  void paintEvent(QPaintEvent *event);

  void setGradientStops(const QGradientStops &stops);

  void generateShade();
  void setHoverPoints(HoverPoints *hoverPoints);

signals:
  void colorPickerChanged();
private:
  HoverPoints *m_hoverPoints;
};


class ColorEditor : public QWidget
{
  Q_OBJECT
public:
  QImage m_shade;
  QPolygonF points() const;
  ColorEditor(QWidget *parent, QColor color);
  HoverPoints *hoverPoints() const
  {
    return m_hoverPoints;
  }
  void paintEvent(QPaintEvent *event);
  QRgb colorAt(int x);

  QColor color;
  void setGradientStops(const QGradientStops &stops);
  void setValue(QColor color);
signals:
  void colorsChanged();
private:
  HoverPoints *m_hoverPoints;
  void generateShade();
};




class GradientEditor :public QWidget
{
  Q_OBJECT

public:
  GradientEditor(QWidget *parent, TifVolumeObject* vol, vtkVolumeProperty *defaultProperty);
  QLabel *label;
  QString text;
  void setValue(QColor color);
  //void setGradientStops(const QGradientStops &stops);
  void set_shade_points(const QPolygonF &points);
  int maxPoints = 15;
  TifVolumeObject *getVol() const;
  void setDefaultValues();

signals:
  void gradientStopsChanged(QGradientStops &stops);
  void colorsChanged();
public slots:
  void pointsUpdated( );
  void colorUpdated( );
  void setGradientStops(QGradientStops &stops);

private:
  ColorEditor *colorEditor;
  ColorPicker *colorPicker;
  TifVolumeObject *vol;
  vtkVolumeProperty *defaultProperty;
};



class TransferFunctionEditor: public QWidget{
  Q_OBJECT
public:
  TransferFunctionEditor(QWidget *parent, TifVolumeObject *vol);
  GradientEditor *m_editor;
  TifVolumeObject *vol;
  vtkSmartPointer<vtkVolumeProperty> defaultProperty;
  ClickableLabel *label;
  QWidget *editor;

signals:
  void colorsChanged();
public slots:
  void setDefault( );
  bool saveFunction();
  void labelClicked();
private:
  void saveDefault();
};
