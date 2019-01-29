
#include "transferFunctionEditor.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkPiecewiseFunction.h"

ColorPicker::ColorPicker(QWidget *parent) : QWidget(parent)
{
  QPolygonF points;
  points << QPointF(0, sizeHint( ).height( ));
  m_hoverPoints = new HoverPoints(this, HoverPoints::RectangleShape);
  //     m_hoverPoints->setConnectionType(HoverPoints::LineConnection);
  m_hoverPoints->setPoints(points);
  m_hoverPoints->setPointLock(0, HoverPoints::LockToTop);
  m_hoverPoints->setPointLock(0, HoverPoints::LockToBottom);
  m_hoverPoints->setPointSize(QSize(10, 25));
  m_hoverPoints->setEditable(false);
  m_hoverPoints->setSortType(HoverPoints::XSort);

  connect(m_hoverPoints, SIGNAL(pointsChanged(QPolygonF)), this, SIGNAL(colorPickerChanged( )));
}

void ColorPicker::generateShade( )
{
  /*if ( m_shade.isNull( ) )
  {*/
    m_shade = QImage(size( ), QImage::Format_RGB32);
    //QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
    QLinearGradient linearGrad(rect( ).topLeft( ), rect( ).topRight( ));
    linearGrad.setColorAt(1, QColor(229, 121, 121));
    linearGrad.setColorAt(0.15, QColor(209,170,98));
    linearGrad.setColorAt(0.25, QColor(155, 244, 139));
    linearGrad.setColorAt(0.5, QColor(114, 204, 204));
    linearGrad.setColorAt(0.65, QColor(120, 120, 237));
    linearGrad.setColorAt(0.9, QColor(204, 106, 204));
    linearGrad.setColorAt(0, QColor(229, 121, 121));

    QPainter painter(&m_shade);
    painter.fillRect(rect( ), QBrush(linearGrad));
  //}
}

void ColorPicker::paintEvent(QPaintEvent *event)
{
  generateShade( );
  QPainter p(this);
  p.drawImage(0, 0, m_shade);
  p.setPen(QColor(146, 146, 146));
  p.drawRect(0, 0, width( ) - 1, height( ) - 1);
}
QPolygonF ColorPicker::points( )const
{
  return m_hoverPoints->points( );
}


ColorEditor::ColorEditor(QWidget *parent) : QWidget(parent)
{
  color = QColor(232, 179, 156);
  QPolygonF points;
  points << QPointF(0, sizeHint( ).height( ))
    << QPointF(sizeHint( ).width( ), 0);

  m_hoverPoints = new HoverPoints(this, HoverPoints::CircleShape);
  //m_hoverPoints->setConnectionType(HoverPoints::LineConnection);
  m_hoverPoints->setPoints(points);
  m_hoverPoints->setPointLock(0, HoverPoints::LockToLeft);
  m_hoverPoints->setPointLock(1, HoverPoints::LockToRight);
  m_hoverPoints->setSortType(HoverPoints::XSort);

  connect(m_hoverPoints, SIGNAL(pointsChanged(QPolygonF)), this, SIGNAL(colorsChanged( )));
}

void ColorEditor::generateShade( )
{
  QColor color2 = QColor(255, 255, 255);
  if ( color.red( ) < 100 )
    color2.setRed(230);
  if ( color.green( ) < 100 )
    color2.setGreen(230);
  if ( color.blue( ) < 100 )
    color2.setBlue(230);
  m_shade = QImage(size( ), QImage::Format_RGB32);
  //QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
  QLinearGradient linearGrad(rect( ).topLeft( ), rect( ).topRight( ));
  //colores de la funcion de transferencia
  linearGrad.setColorAt(1, color2);
  linearGrad.setColorAt(0, color);

  QPainter painter(&m_shade);
  painter.fillRect(rect( ), QBrush(linearGrad));

}

void ColorEditor::setGradientStops(const QGradientStops &stops)
{
  for ( int i = 0; i < stops.size( ); ++i )
  {
    QColor c = stops.at(i).second;

  }
}


void ColorEditor::paintEvent(QPaintEvent *event)
{
  generateShade( );
  QPainter p(this);
  p.drawImage(0, 0, m_shade);
  p.setPen(QColor(146, 146, 146));
  p.drawRect(0, 0, width( ) - 1, height( ) - 1);
}
QPolygonF ColorEditor::points( )const
{
  return m_hoverPoints->points( );
}

QRgb ColorEditor::colorAt(int x)
{
  generateShade( );

  QPolygonF pts = m_hoverPoints->points( );
  for ( int i = 1; i < pts.size( ); ++i )
  {
    if ( pts.at(i - 1).x( ) <= x && pts.at(i).x( ) >= x )
    {
      QLineF l(pts.at(i - 1), pts.at(i));
      l.setLength(l.length( ) * ( ( x - l.x1( ) ) / l.dx( ) ));
      return m_shade.pixel(qRound(qMin(l.x2( ), ( qreal(m_shade.width( ) - 1) ))),
        qRound(qMin(l.y2( ), qreal(m_shade.height( ) - 1))));
    }
  }
  return 0;

}


GradientEditor::GradientEditor(QWidget *parent, TifVolumeObject *vol) :QWidget(parent)
{
  this->vol = vol;
  QVBoxLayout *vbox = new QVBoxLayout(this);
  vbox->setSpacing(1);
  vbox->setMargin(1);


  colorPicker = new ColorPicker(this);
  colorEditor = new ColorEditor(this);
  //label = new QLabel(this);


  //stretch-factor relacion 1:5

  vbox->addWidget(colorPicker, 1, 0);
  vbox->addWidget(colorEditor, 3, 0);
  //vbox->addWidget(label);
  connect(colorPicker, SIGNAL(colorPickerChanged( )), this, SLOT(colorUpdated( )));
  connect(colorEditor, SIGNAL(colorsChanged( )), this, SLOT(pointsUpdated( )));
}
void GradientEditor::setValue(QColor color)
{
  //text = color.name( );
  colorEditor->color = color;
  colorEditor->update( );
  //label->setText(text);
}
inline static bool x_less_than(const QPointF &p1, const QPointF &p2)
{
  return p1.x( ) < p2.x( );
}

void GradientEditor::pointsUpdated( )
{

  qreal w = colorEditor->width( );
  qreal h = colorEditor->height( );
  QGradientStops stops;
  QPolygonF points;
  points += colorEditor->points( );
  //maximo de 15 ptos de control
  if ( points.size( ) >= maxPoints )
  {
    colorEditor->hoverPoints( )->setAddingEditable(false);
  }
  else
  {
    colorEditor->hoverPoints( )->setAddingEditable(true);
  }
  std::sort(points.begin( ), points.end( ), x_less_than);
  vtkPiecewiseFunction *spwf = vtkPiecewiseFunction::New();
  for ( int i = 0; i < points.size( ); ++i )
  {
    qreal x = int(points.at(i).x( ));
    qreal y = int(points.at(i).y( ));
    if ( i + 1 < points.size( ) && x == points.at(i + 1).x( ) )
      continue;
    QColor color;

    color = colorEditor->colorAt(int(x));
    if ( x / w > 1 )
      return;
    color.setAlphaF(1 - ( y / h ));
    stops << QGradientStop(x / w, color);

    spwf->AddPoint(x, 1 - (y / h));
  }
  vol->getVolume()->GetProperty()->SetScalarOpacity(spwf);

  emit gradientStopsChanged(stops);
  emit colorsChanged();
}

void GradientEditor::colorUpdated( )
{
  QPolygonF points;
  points = colorPicker->points( );

  qreal x = int(points.at(0).x( ));
  qreal y = int(points.at(0).y( ));
  QColor color;
  colorPicker->generateShade( );
  color = colorPicker->m_shade.pixel(x, 0);


  vtkColorTransferFunction *ctf = vtkColorTransferFunction::New();
  ctf->AddRGBPoint(0, color.redF(), color.greenF(), color.blueF());
  vol->getVolume()->GetProperty()->SetColor(ctf);
  setValue(color);

  emit colorEditor->colorsChanged( );

}
void GradientEditor::set_shade_points(const QPolygonF &points)
{
  colorEditor->hoverPoints( )->setPoints(points);
  colorEditor->hoverPoints( )->setPointLock(0, HoverPoints::LockToLeft);
  colorEditor->hoverPoints( )->setPointLock(points.size( ) - 1, HoverPoints::LockToRight);
  colorEditor->update( );
  pointsUpdated( );
}

void GradientEditor::setGradientStops(QGradientStops &stops)
{
  //clave
  QPolygonF pts;

  qreal h_color = colorEditor->height( );

  for ( int i = 0; i < stops.size( ); ++i )
  {
    qreal pos = stops.at(i).first;
    QRgb color = stops.at(i).second.rgba( );
    pts << QPointF(pos * colorEditor->width( ), h_color - qAlpha(color) * h_color / 255);
  }

  set_shade_points(pts);

  QPolygonF pt;
  //QRgb color = QColor::fromRgba(0x00e8b93c).rgba( );
  pt << QPointF(0.1 * colorPicker->width( ), 0);
  colorPicker->hoverPoints( )->setPoints(pt);
  colorPicker->update( );
  colorUpdated( );
}

TifVolumeObject *GradientEditor::getVol() const
{
    return vol;
}

TransferFunctionEditor::TransferFunctionEditor(QWidget *parent, TifVolumeObject *vol) :QWidget(parent)
{
  QVBoxLayout *vbox = new QVBoxLayout(this);
  vbox->setSpacing(1);
  vbox->setMargin(1);

  QPushButton *defaultButton = new QPushButton(tr("default"));

  m_editor = new GradientEditor(this, vol);
  vbox->addWidget(m_editor);
  vbox->addWidget(defaultButton);
  connect(defaultButton, SIGNAL(clicked( )), this, SLOT(setDefault( )));
  connect(m_editor, SIGNAL(colorsChanged()), this, SIGNAL(colorsChanged( )));
  QTimer::singleShot(50, this, SLOT(setDefault( )));
}

void TransferFunctionEditor::setDefault( )
{
  //color = QColor(232, 179, 156);0x00e8b93c
  //init
  QGradientStops stops;

  stops << QGradientStop(0.00, QColor::fromRgba(0));
  stops << QGradientStop(80.0 / 255.0, QColor::fromRgba(0)); //alpha 0.0
  stops << QGradientStop(1.0, QColor::fromRgba(0xff000000));//alpha 1.0
  m_editor->setGradientStops(stops);
  update( );
}
