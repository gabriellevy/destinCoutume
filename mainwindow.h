#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../destinLib/dbmanager.h"
#include "cmdt.h"

class UniversCoutume;

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
    QList<CaracCoutume> m_CaracsCoutume;

private:
    Ui::MainWindow *ui;

    void ChargerInterfaceSaisieCmdt();
    UniversCoutume* GetUniversCoutume();
};

#endif // MAINWINDOW_H
