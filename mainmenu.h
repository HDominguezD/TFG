#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

namespace Ui {
class mainMenu;
}

class mainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = 0);
    ~mainMenu();

private slots:
    void on_loadData_clicked(bool checked);

private:
    Ui::mainMenu *ui;
};

#endif // MAINMENU_H
