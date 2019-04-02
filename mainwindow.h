#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DbManager m_Db;
    QList<DomaineLoi>  m_TousDomainesLoi;
    QList<CaracCoutume> m_CaracsCoutume;

private:
    Ui::MainWindow *ui;

    void ChargerInterfaceSaisieCmdt();
};

#endif // MAINWINDOW_H
