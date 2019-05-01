#include "saisiecmdt.h"
#include "ui_mainwindow.h"
#include "dixcommandements.h"
#include "universcoutume.h"

SaisieCmdt::SaisieCmdt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // chargements de base :
    //m_Db.Initialisation("D:/boulot/QtProjects/Coutume/data/Coutume.db");
    //m_TousDomainesLoi = m_Db.GetAllDomaineLoi();
    //m_CaracsCoutume = m_Db.GetAllCaracCoutume();

    ChargerInterfaceSaisieCmdt();
    QObject::connect(this->ui->ajouterCmdt, SIGNAL(clicked()), this, SLOT(AjouterCmdtBdd()));


    m_CaracValuesInputs.push_back(ui->val_CaracCoutume_1);
    m_CaracValuesInputs.push_back(ui->val_CaracCoutume_2);
    m_CaracValuesInputs.push_back(ui->val_CaracCoutume_3);
    m_CaracValuesInputs.push_back(ui->val_CaracCoutume_4);
    m_CaracValuesInputs.push_back(ui->val_CaracCoutume_5);
    m_CaracValuesInputs.push_back(ui->val_CaracCoutume_6);
    m_CaracTypeInputs.push_back(ui->cb_CaracCoutume_1);
    m_CaracTypeInputs.push_back(ui->cb_CaracCoutume_2);
    m_CaracTypeInputs.push_back(ui->cb_CaracCoutume_3);
    m_CaracTypeInputs.push_back(ui->cb_CaracCoutume_4);
    m_CaracTypeInputs.push_back(ui->cb_CaracCoutume_5);
    m_CaracTypeInputs.push_back(ui->cb_CaracCoutume_6);
}

void SaisieCmdt::AjouterCmdtBdd()
{
    QString intitule = this->ui->titreCmdt->text();
    // attention aux testes contenant des apostrophes :
    intitule = intitule.replace("'", "''");
    QString description = this->ui->texteCmdt->toPlainText();
    description = description.replace("'", "''");
    int id_domaine_loi = -1;
    QString domaineSelectionne = ui->comBoxDomaineLoi->currentText();
    for ( DomaineLoi* domaine: this->GetUniversCoutume()->GetTousDomainesLoi()) {
        if ( domaine->m_Intitule == domaineSelectionne) {
            id_domaine_loi = domaine->m_BddId;
            break;
        }
    }
    QString msg = "id de domaine loi introuvable pour ce domaine : " + domaineSelectionne;
    Q_ASSERT_X(id_domaine_loi != -1, msg.toStdString().c_str(), "MainWindow::AjouterCmdtBdd");

    QSqlQuery query;
    if ( query.exec("INSERT INTO Cmdt (intitule, description, id_domaine_loi) "
                    "VALUES ('" + intitule + "', '" + description + "', '" + QString::number(id_domaine_loi) + "')")) {
        this->GetUniversCoutume()->GetHistoireDixCommandement()->m_Db.m_db.commit();
    } else {
         qDebug() <<  "Erreur SQL : " + query.lastError().text();
         return;
    }

    int id_cmdt = query.lastInsertId().toInt();

    QSqlQuery requete_EffetCaracCoutume;

    requete_EffetCaracCoutume.prepare("INSERT INTO EffetCaracCoutume (val, id_carac_coutume, id_cmdt) "
                                      "VALUES (:val, :id_carac_coutume, :id_cmdt)");
    requete_EffetCaracCoutume.bindValue(":id_cmdt", id_cmdt);

    for ( int i = 0 ; i < m_CaracValuesInputs.length(); ++i) {
        if ( m_CaracValuesInputs[i]->text() != "") {
            requete_EffetCaracCoutume.bindValue(":val", m_CaracValuesInputs[i]->text());
            int id_carac = this->GetUniversCoutume()->GetHistoireDixCommandement()->GetCaracCoutumeBddId(
                        m_CaracTypeInputs[i]->currentText());
            requete_EffetCaracCoutume.bindValue(":id_carac_coutume",id_carac);
            if ( requete_EffetCaracCoutume.exec()) {
                this->GetUniversCoutume()->GetHistoireDixCommandement()->m_Db.m_db.commit();
            } else {
                 qDebug() <<  "Erreur SQL : " + requete_EffetCaracCoutume.lastError().text();
                 return;
            }
        } else {
            break;
        }
    }

    this->GetUniversCoutume()->GetHistoireDixCommandement()->m_Db.m_db.commit();
}

UniversCoutume* SaisieCmdt::GetUniversCoutume()
{
    return static_cast<UniversCoutume*>(Univers::ME);
}


void SaisieCmdt::ChargerInterfaceSaisieCmdt()
{
    foreach(DomaineLoi* it, GetUniversCoutume()->GetTousDomainesLoi())
    {
        ui->comBoxDomaineLoi->addItem(it->m_Intitule);
    }

    for(CaracCoutume* carac: GetUniversCoutume()->GetTousCaracCoutumes())
    {
        ui->cb_CaracCoutume_1->addItem(carac->m_Intitule);
        ui->cb_CaracCoutume_2->addItem(carac->m_Intitule);
        ui->cb_CaracCoutume_3->addItem(carac->m_Intitule);
        ui->cb_CaracCoutume_4->addItem(carac->m_Intitule);
        ui->cb_CaracCoutume_5->addItem(carac->m_Intitule);
        ui->cb_CaracCoutume_6->addItem(carac->m_Intitule);
        ui->cb_CaracCoutume_7->addItem(carac->m_Intitule);
        ui->cb_CaracCoutume_8->addItem(carac->m_Intitule);
    }
}

SaisieCmdt::~SaisieCmdt()
{
    delete ui;
}
