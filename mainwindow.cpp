#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // chargements de base :
    m_Db.Initialisation("D:/boulot/QtProjects/Coutume/data/Coutume.db");
    //m_TousDomainesLoi = m_Db.GetAllDomaineLoi();
    //m_CaracsCoutume = m_Db.GetAllCaracCoutume();

    ChargerInterfaceSaisieCmdt();
}


void MainWindow::ChargerInterfaceSaisieCmdt()
{
    foreach(DomaineLoi it, m_TousDomainesLoi)
    {
        ui->comBoxDomaineLoi->addItem(it.m_Intitule);
    }

    foreach(CaracCoutume it, m_CaracsCoutume)
    {
        ui->cb_CaracCoutume_1->addItem(it.m_Intitule);
        ui->cb_CaracCoutume_2->addItem(it.m_Intitule);
        ui->cb_CaracCoutume_3->addItem(it.m_Intitule);
        ui->cb_CaracCoutume_4->addItem(it.m_Intitule);
        ui->cb_CaracCoutume_5->addItem(it.m_Intitule);
        ui->cb_CaracCoutume_6->addItem(it.m_Intitule);
        ui->cb_CaracCoutume_7->addItem(it.m_Intitule);
        ui->cb_CaracCoutume_8->addItem(it.m_Intitule);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
