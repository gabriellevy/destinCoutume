#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../destinLib/dbmanager.h"
#include "cmdt.h"
#include "QLineEdit"
#include <QComboBox>

class UniversCoutume;

namespace Ui {
class MainWindow;
}

/**
 * @brief Interface de saisie de commandement
 */
class SaisieCmdt : public QMainWindow
{
    Q_OBJECT

public:
    explicit SaisieCmdt(QWidget *parent = nullptr);
    ~SaisieCmdt();

    //DbManager m_Db;
    //QList<CaracCoutume> m_CaracsCoutume;

private:
    Ui::MainWindow *ui;

    // convenient pointers to interface elements :
    QVector<QLineEdit*> m_CaracValuesInputs = {};
    QVector<QComboBox*> m_CaracTypeInputs = {};

    void ChargerInterfaceSaisieCmdt();
    UniversCoutume* GetUniversCoutume();

private slots:
    void AjouterCmdtBdd();
};

#endif // MAINWINDOW_H
