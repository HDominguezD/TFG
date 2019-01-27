#include "hoverpoints.h"


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
  ColorEditor(QWidget *parent);
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
  GradientEditor(QWidget *parent);
  QLabel *label;
  QString text;
  void setValue(QColor color);
  //void setGradientStops(const QGradientStops &stops);
  void set_shade_points(const QPolygonF &points);
  int maxPoints = 15;
signals:
  void gradientStopsChanged(QGradientStops &stops);
public slots:
  void pointsUpdated( );
  void colorUpdated( );
  void setGradientStops(QGradientStops &stops);
private:
  ColorEditor *colorEditor;
  ColorPicker *colorPicker;
};



class TransferFunctionEditor: public QWidget{
  Q_OBJECT
public:
  TransferFunctionEditor(QWidget *parent);

  GradientEditor *m_editor;
public slots:
  void setDefault( );
private:
};
