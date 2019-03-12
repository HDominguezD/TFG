#ifndef OBJECTBUTTON_H
#define OBJECTBUTTON_H
#include "QPushButton"
#include "Pairs/objectpropertiespair.h"

class ObjectButton : public QPushButton
{
        Q_OBJECT
public:
    ObjectButton(ObjectPropertiesPair *objectPropertiesPair, QWidget *parent = nullptr);

private:
    ObjectPropertiesPair *objectPropertiesPair;

signals:
    void objectButtonClicked(ObjectPropertiesPair *objectPropertiesPair);

private slots:
    void buttonClicked(bool clicked);

};

#endif // OBJECTBUTTON_H
