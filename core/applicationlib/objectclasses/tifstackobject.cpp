#include "tifstackobject.h"
#include <QDir>
#include <QFileDialog>

TifStackObject::TifStackObject()
{
    tifStack = new QVector<TifObject*>();
    activeImage = 0;
}

bool TifStackObject::readObject()
{
    bool readed = false;

    QDir directory = QFileDialog::getExistingDirectory(Q_NULLPTR, QObject::tr("select directory"));
    if(!directory.exists())
    {
        return readed;
    }

    QStringList images = directory.entryList(QStringList() << "*.tif" << "*.tiff",QDir::Files);
    if(images.size() == 0){
        return false;
    } else if(images.size() == 1){
        name = images.at(0).toStdString();
    } else {
        name = directory.dirName().toStdString();
    }

    for(QString image : images){
        TifObject *tif = new TifObject();
        readed = tif->readObjectFromFile(directory.absolutePath().toStdString() + "/" + image.toStdString());
        tifStack->append(tif);
    }

    return readed;
}

void TifStackObject::printObject(QVTKWidget *widget)
{
    if(tifStack->size() != 0 && activeImage >= 0 && activeImage < tifStack->size()){
        tifStack->at(activeImage)->printObject(widget);
    }
}

const char *TifStackObject::objectType()
{
    return "TifStack";
}

QVector<TifObject*>* TifStackObject::getTifStack() const
{
    return tifStack;
}

void TifStackObject::setTifStack(QVector<TifObject*>* value)
{
    tifStack = value;
}

void TifStackObject::addTifObject(TifObject* value)
{
    tifStack->append(value);
}

void TifStackObject::removeTifObject(TifObject* value)
{
    tifStack->removeAll(value);
}

int TifStackObject::getActiveImage() const
{
    return activeImage;
}

void TifStackObject::setActiveImage(int value)
{
    activeImage = value;
}

string TifStackObject::getName() const
{
    return name;
}

TifStackObject::~TifStackObject()
{
    for(int i = 0; i < tifStack->size(); i++){
        tifStack->at(i)->getActor2D()->VisibilityOff();
    }
}

QVTKWidget *TifStackObject::getVtkWidget() const
{
    return vtkWidget;
}

void TifStackObject::setName(const string &value)
{
    name = value;
}
