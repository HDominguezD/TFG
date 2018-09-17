#ifndef LOADDATA_H
#define LOADDATA_H

#include <QWidget>

namespace Ui {
class LoadData;
}

class LoadData : public QWidget
{
    Q_OBJECT

public:
    explicit LoadData(QWidget *parent = 0);
    ~LoadData();

private slots:
    void on_mesh_clicked(bool checked);

    void on_volumetric_clicked(bool checked);

    void on_image_clicked(bool checked);

private:
    Ui::LoadData *ui;
};

#endif // LOADDATA_H
