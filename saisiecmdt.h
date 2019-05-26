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

class GenHistCoutume;

/**
 * @brief Interface de saisie de commandement et d'événement
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
    // saisie de commandement :
    QVector<QLineEdit*> m_CaracValuesInputs = {};
    QVector<QComboBox*> m_CaracTypeInputs = {};
    // saisie d'événement :
    QVector<QLineEdit*> m_CondValeurCaracInputs = {};
    QVector<QComboBox*> m_CondTypeCaracInputs = {};
    QVector<QComboBox*> m_CondSigneInputs = {};

    void ChargerInterfaceSaisieCmdt();
    void ChargerInterfaceSaisieEvt();
    UniversCoutume* GetUniversCoutume();
    GenHistCoutume* GetGenHistCoutume();

private slots:
    void AjouterCmdtBdd();
    void AjouterEvtBdd();
};

#endif // MAINWINDOW_H
