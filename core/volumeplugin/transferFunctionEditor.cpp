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
    m_shade = QImage(size( ), QImage::Format_RGB32);

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
}

void ColorPicker::setHoverPoints(HoverPoints *hoverPoints)
{
    m_hoverPoints = hoverPoints;
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


ColorEditor::ColorEditor(QWidget *parent, QColor color) : QWidget(parent)
{
    this->color = color;
    QPolygonF points;
    points << QPointF(0, sizeHint( ).height( )) << QPointF(sizeHint( ).width( ), 0);

    m_hoverPoints = new HoverPoints(this, HoverPoints::CircleShape);
    m_hoverPoints->setPoints(points);
    m_hoverPoints->setPointLock(0, HoverPoints::LockToLeft);
    m_hoverPoints->setPointLock(1, HoverPoints::LockToRight);
    m_hoverPoints->setSortType(HoverPoints::XSort);

    generateShade();
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
    //generateShade( );

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


GradientEditor::GradientEditor(QWidget *parent, TifVolumeObject *vol, vtkVolumeProperty *defaultProperty) :QWidget(parent)
{
    this->vol = vol;
    this->defaultProperty = defaultProperty;
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);
    vbox->setMargin(1);


    colorPicker = new ColorPicker(this);

    vtkColorTransferFunction *ctf = defaultProperty->GetRGBTransferFunction();
    QColor color = QColor(ctf->GetRedValue(0), ctf->GetGreenValue(0), ctf->GetBlueValue(0), ctf->GetBlueValue(0));
    colorEditor = new ColorEditor(this, color);

    vbox->addWidget(colorPicker, 1, 0);
    vbox->addWidget(colorEditor, 3, 0);

    connect(colorPicker, SIGNAL(colorPickerChanged( )), this, SLOT(colorUpdated( )));
    connect(colorEditor, SIGNAL(colorsChanged( )), this, SLOT(pointsUpdated( )));
}

void GradientEditor::setValue(QColor color)
{
    colorEditor->color = color;
    colorEditor->update( );
}

inline static bool x_less_than(const QPointF &p1, const QPointF &p2)
{
    return p1.x( ) < p2.x( );
}

void GradientEditor::pointsUpdated( )
{
    double max = vol->getMaxValue();
    qreal w = colorEditor->width( );
    qreal widthRelation = max / w;
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
    vtkPiecewiseFunction *gpwf = vtkPiecewiseFunction::New();

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
        //interpolate the editor width value with the max value of the pixels
        stops << QGradientStop((x * widthRelation) / max, color);

        spwf->AddPoint(x * widthRelation, 1 - (y / h));
        gpwf->AddPoint((x * widthRelation) / max * 100, 1 - (y / h));
    }

    vol->getVolume()->GetProperty()->SetScalarOpacity(spwf);
    vol->getVolume()->GetProperty()->SetGradientOpacity(gpwf);

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
    QPolygonF pts;

    qreal h_color = colorEditor->height( );

    for ( int i = 0; i < stops.size( ); ++i )
    {
        qreal pos = stops.at(i).first;
        QRgb color = stops.at(i).second.rgba( );
        pts << QPointF(pos * colorEditor->width( ), h_color - qAlpha(color) * h_color / 255);
    }

    set_shade_points(pts);
}

TifVolumeObject *GradientEditor::getVol() const
{
    return vol;
}

void GradientEditor::setDefaultValues()
{
    QGradientStops stops;
    vtkPiecewiseFunction *spwf = defaultProperty->GetScalarOpacity();
    vtkColorTransferFunction *ctf = defaultProperty->GetRGBTransferFunction();

    QColor color;
    color.setRedF(ctf->GetRedValue(0));
    color.setGreenF(ctf->GetGreenValue(0));
    color.setBlueF(ctf->GetBlueValue(0));

    colorPicker->generateShade( );

    for(int i = 0; i < colorPicker->m_shade.width(); i++)
    {
        QColor pixel = colorPicker->m_shade.pixel(i, 0);
        QRgb b1 = pixel.rgb();
        QRgb b2 = color.rgb();
        if(b1 == b2)
        {
            QPointF point(i, 0);
            QPolygonF points = colorPicker->hoverPoints()->points();
            points.replace(0,point);
            colorPicker->hoverPoints()->setPoints(points);
            setValue(pixel);
            break;
        }
    }
    for(int i = 0; i < spwf->GetSize(); i++)
    {
        double node[4] = {};
        spwf->GetNodeValue(i, node);
        qreal w = colorEditor->width( );
        color.setAlphaF(node[1]);
        stops << QGradientStop(node[0] / vol->getMaxValue(), color);
    }
    vol->getVolume()->GetProperty()->SetColor(defaultProperty->GetRGBTransferFunction());
    vol->getVolume()->GetProperty()->SetScalarOpacity(defaultProperty->GetScalarOpacity());
    vol->getVolume()->GetProperty()->SetGradientOpacity(defaultProperty->GetGradientOpacity());
    setGradientStops(stops);
}


TransferFunctionEditor::TransferFunctionEditor(QWidget *parent, TifVolumeObject *vol) :QWidget(parent)
{
    this->vol = vol;
    saveDefault();
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setSpacing(1);
    vbox->setMargin(1);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    QPushButton *defaultButton = new QPushButton(tr("default"));
    QPushButton *saveButton = new QPushButton(tr("Save function"));
    hbox->addWidget(defaultButton);
    hbox->addWidget(saveButton);

    m_editor = new GradientEditor(this, vol, defaultProperty);
    vbox->addWidget(m_editor);
    vbox->addLayout(hbox);
    connect(defaultButton, SIGNAL(clicked( )), this, SLOT(setDefault( )));
    connect(saveButton, SIGNAL(clicked( )), this, SLOT(saveFunction()));
    connect(m_editor, SIGNAL(colorsChanged()), this, SIGNAL(colorsChanged( )));
    QTimer::singleShot(50, this, SLOT(setDefault( )));
}

void TransferFunctionEditor::setDefault( )
{
    m_editor->setDefaultValues();
    update( );
}

bool TransferFunctionEditor::saveFunction()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save transfer function in the same directory of the volume"), "home/Desktop/transferFunction.trans",tr("TransferFunctions (*.trans)"));
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);

        vtkColorTransferFunction *ctf = vol->getVolume()->GetProperty()->GetRGBTransferFunction();
        for(int i = 0; i < ctf->GetSize(); i++){
            double node[6] = {};
            ctf->GetNodeValue(i, node);
            stream << "c " << node[0] << " " << node[1] << " " << node[2] << " " << node[3] << endl;
        }

        vtkPiecewiseFunction *spwf = vol->getVolume()->GetProperty()->GetScalarOpacity();
        for(int i = 0; i < spwf->GetSize(); i++){
            double node[4] = {};
            spwf->GetNodeValue(i, node);
            stream << "s " << node[0] << " " << node[1] << endl;
        }

        vtkPiecewiseFunction *gpwf = vol->getVolume()->GetProperty()->GetGradientOpacity();
        for(int i = 0; i < gpwf->GetSize(); i++){
            double node[4] = {};
            gpwf->GetNodeValue(i, node);
            stream << "g " << node[0] << " " << node[1] << endl;
        }
    }
}

void TransferFunctionEditor::saveDefault()
{
    defaultProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    defaultProperty->SetScalarOpacity(vol->getVolume()->GetProperty()->GetScalarOpacity());
    defaultProperty->SetGradientOpacity(vol->getVolume()->GetProperty()->GetGradientOpacity());
    defaultProperty->SetColor(vol->getVolume()->GetProperty()->GetRGBTransferFunction());
}
