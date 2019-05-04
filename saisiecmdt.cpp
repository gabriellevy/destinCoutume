#include "saisiecmdt.h"
#include "ui_saisiecmdt.h"
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
    ChargerInterfaceSaisieEvt();
}


void SaisieCmdt::AjouterEvtBdd()
{
    QString intitule = this->ui->titreEvt->text();
    // attention aux testes contenant des apostrophes :
    intitule = intitule.replace("'", "''");
    QString texte = this->ui->texteEvt->toPlainText();
    texte = texte.replace("'", "''");

    // insertion d'un événement
    QSqlQuery requeteNoeud;
    if ( requeteNoeud.exec("INSERT INTO d_Noeud (m_Id) "
                    "VALUES ('" + intitule + "')")) {
        this->GetUniversCoutume()->GetHistoireDixCommandement()->m_Db.m_db.commit();
    } else {
         qDebug() <<  "requeteNoeud Evt Erreur SQL : " + requeteNoeud.lastError().text();
         return;
    }
    int noeud_evt_id = requeteNoeud.lastInsertId().toInt();
    QSqlQuery requeteEvt;
    if ( requeteEvt.exec("INSERT INTO d_Evt (est_noeud_id, appartient_selectionneur_evt_id) "
                    "VALUES ('" + QString::number(noeud_evt_id) + "', '1')")) { // A FAIRE : le sélectionneur d'événement est laissé en dur pour l'instant => il faudrait ajouter sa sélection dans l'interface
        this->GetUniversCoutume()->GetHistoireDixCommandement()->m_Db.m_db.commit();
    } else {
         qDebug() <<  "requeteEvt Erreur SQL : " + requeteEvt.lastError().text();
         return;
    }
    int evt_id = requeteEvt.lastInsertId().toInt();


    // ajout des conditions à cet evt
    QSqlQuery requete_Conditions;

    requete_Conditions.prepare("INSERT INTO d_Condition (est_a_noeud_id, m_CaracId, m_Valeur, m_Comparateur, m_Proba) "
                                      "VALUES (:bdd_id_noeud_evt, :id_carac_coutume, :valeur, :comparateur, :proba)");
    requete_Conditions.bindValue(":bdd_id_noeud_evt", noeud_evt_id);
    requete_Conditions.bindValue(":proba", 1);// A FAIRE : ajouter un champs de proba permettant de donner une valeur de 0 à 1 pour indiquer si cet effet est courant

    for ( int i = 0 ; i < this->m_CondValeurCaracInputs.length(); ++i) {
        if ( m_CondValeurCaracInputs[i]->text() != "") {
            requete_Conditions.bindValue(":id_carac_coutume", m_CondTypeCaracInputs[i]->currentText());
            requete_Conditions.bindValue(":valeur", m_CondValeurCaracInputs[i]->text());

            QString strFinale = Condition::GetStrFromComparateur(Condition::GetComparateurFromStrSigne(m_CondSigneInputs[i]->currentText()));
            requete_Conditions.bindValue(":comparateur", strFinale);

            if ( requete_Conditions.exec()) {
                this->GetUniversCoutume()->GetHistoireDixCommandement()->m_Db.m_db.commit();
            } else {
                 qDebug() <<  "requete_Conditions Erreur SQL : " + requete_Conditions.lastError().text() + " - index : " + i;
                 return;
            }
        } else {
            break;
        }
    }

    // insertion d'un effet dans l'événement (un seul pour l'instant)
    QSqlQuery requeteNoeudEffet;
    if ( requeteNoeudEffet.exec("INSERT INTO d_Noeud (m_Id, m_Text, m_GoToEvtId) "
                    "VALUES ('" + intitule + "', '" + texte + "', 'EvtPassageDuTemps')")) { // une fois l'effet aléatoire exécuté on va forcément vers EvtPassageDuTemps
        this->GetUniversCoutume()->GetHistoireDixCommandement()->m_Db.m_db.commit();
    } else {
         qDebug() <<  "requeteNoeudEffet Erreur SQL : " + requeteNoeudEffet.lastError().text();
         return;
    }
    int noeud_effet_id = requeteNoeudEffet.lastInsertId().toInt();
    QSqlQuery requeteEffet;
    if ( requeteEffet.exec("INSERT INTO d_Effet (est_un_noeud_id, appartient_a_evt_id, ordre) "
                    "VALUES ('" + QString::number(noeud_effet_id) + "', '" + QString::number(evt_id) + "', '1')")) {
        this->GetUniversCoutume()->GetHistoireDixCommandement()->m_Db.m_db.commit();
    } else {
         qDebug() <<  "requeteEffet Erreur SQL : " + requeteEffet.lastError().text();
         return;
    }
}

void SaisieCmdt::AjouterCmdtBdd()
{
    QString intitule = this->ui->titreCmdt->text();
    // attention aux testes contenant des apostrophes :
    intitule = intitule.replace("'", "''");
    QString description = this->ui->texteCmdt->toPlainText();
    description = description.replace("'", "''");
    int id_domaine_loi = -1;
    /*QString domaineSelectionne = ui->comBoxDomaineLoi->currentText();
    for ( DomaineLoi* domaine: this->GetUniversCoutume()->GetTousDomainesLoi()) {
        if ( domaine->m_Intitule == domaineSelectionne) {
            id_domaine_loi = domaine->m_BddId;
            break;
        }
    }
    QString msg = "id de domaine loi introuvable pour ce domaine : " + domaineSelectionne;
    Q_ASSERT_X(id_domaine_loi != -1, msg.toStdString().c_str(), "MainWindow::AjouterCmdtBdd");*/

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
    /*foreach(DomaineLoi* it, GetUniversCoutume()->GetTousDomainesLoi())
    {
        ui->comBoxDomaineLoi->addItem(it->m_Intitule);
    }*/

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


void SaisieCmdt::ChargerInterfaceSaisieEvt()
{
    m_CondValeurCaracInputs.push_back(ui->valeurCondition1);
    m_CondValeurCaracInputs.push_back(ui->valeurCondition2);
    m_CondValeurCaracInputs.push_back(ui->valeurCondition3);
    m_CondValeurCaracInputs.push_back(ui->valeurCondition4);
    m_CondValeurCaracInputs.push_back(ui->valeurCondition5);
    m_CondValeurCaracInputs.push_back(ui->valeurCondition6);
    m_CondValeurCaracInputs.push_back(ui->valeurCondition7);
    m_CondValeurCaracInputs.push_back(ui->valeurCondition8);
    m_CondValeurCaracInputs.push_back(ui->valeurCondition9);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition1);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition2);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition3);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition4);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition5);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition6);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition7);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition8);
    m_CondTypeCaracInputs.push_back(ui->caracCoutumeCondition9);
    m_CondSigneInputs.push_back(ui->signeCondition1);
    m_CondSigneInputs.push_back(ui->signeCondition2);
    m_CondSigneInputs.push_back(ui->signeCondition3);
    m_CondSigneInputs.push_back(ui->signeCondition4);
    m_CondSigneInputs.push_back(ui->signeCondition5);
    m_CondSigneInputs.push_back(ui->signeCondition6);
    m_CondSigneInputs.push_back(ui->signeCondition7);
    m_CondSigneInputs.push_back(ui->signeCondition8);
    m_CondSigneInputs.push_back(ui->signeCondition9);


    for(CaracCoutume* carac: GetUniversCoutume()->GetTousCaracCoutumes())
    {
        for ( int i = 0 ; i < m_CondTypeCaracInputs.length(); ++i) {
            m_CondTypeCaracInputs[i]->addItem(carac->m_Intitule);
        }
    }

    for ( int i = 0 ; i < m_CondSigneInputs.length(); ++i) {
        m_CondSigneInputs[i]->addItem(">=");
        m_CondSigneInputs[i]->addItem("<=");
        m_CondSigneInputs[i]->addItem(">");
        m_CondSigneInputs[i]->addItem("<");
        m_CondSigneInputs[i]->addItem("==");
        m_CondSigneInputs[i]->addItem("!=");
    }

    QObject::connect(this->ui->ajouterEvt, SIGNAL(clicked()), this, SLOT(AjouterEvtBdd()));
}

SaisieCmdt::~SaisieCmdt()
{
    delete ui;
}
