#include "dixcommandements.h"
#include "../destinLib/univers.h"
#include "ui_univers.h"
#include "peuple.h"
#include "thdomainesdivins.h"
#include "cmdt.h"
#include <QDebug>

DixCommandements::DixCommandements(QWidget *parent):Histoire(parent)
{
}


// cette fonction peut être mise dans la bdd si elle ne fait que ça
bool passageDuTemps(QVector<QString> caracs, QVector<QString> )
{
    /*int temps =*/ Carac::AJouterValeurACaracId(caracs[0], 1);
    //qDebug() << "passageDuTemps temps : "<<temps<<endl;
    return true;
}

/**
 * @brief testeSiEmplacementCmdtLibre
 * @return true si le peuple a au moins un emplacement de commandement libre
 */
bool testeSiEmplacementCmdtLibre(QVector<QString>, QVector<QString>)
{
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());

    return dixCmdts->GetPeuple()->AEmplacementLibre();
}

/**
 * @brief appelée quand le joueur a sélectionné le cmdt d'id bddId
 * @param bddIdCmdt
 * @return
 */
bool selectionnerCmdt(QVector<QString> , QVector<QString> bddIdCmdt)
{
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());
    Peuple* peuple = dixCmdts->GetPeuple();

    Cmdt* nouv_cmdt = dixCmdts->GetCmdtViaBddId(bddIdCmdt[0].toInt());

    peuple->AppliquerCmdt(nouv_cmdt);

    return true;
}

/**
 * @brief génère la liste de commandments d=parmi lesquelle le joueur devra choisir
 * @param caracs
 * @return
 */
bool choisirCmdt(QVector<QString> , QVector<QString> )
{
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());

    Effet* effetCourant = Univers::ME->GetHistoire()->EffetActuel();
    effetCourant->SupprimerTousLesChoix();

    int nb_choix_cmdt = 6;
    int index = 0;
    while ( nb_choix_cmdt > 0 && index < dixCmdts->m_TousLesCmdts.length())
    {
        Cmdt* choix_cmdt = dixCmdts->m_TousLesCmdts[ qrand()%dixCmdts->m_TousLesCmdts.length()];
        // vérifier que ce cmdt n'est pas déjà possédé :
        bool a_deja = dixCmdts->GetPeuple()->ACeCommandement(choix_cmdt);
        if (!a_deja) {
            bool est_deja_dans_les_choix = false;
            for ( Choix* choix: effetCourant->m_Choix) {
                if ( choix->m_Text == choix_cmdt->m_Intitule) {
                    est_deja_dans_les_choix = true;
                    break;
                }
            }

            if ( !est_deja_dans_les_choix ) {
                Choix* choix = effetCourant->AjouterChoixVide();
                choix->m_Text = choix_cmdt->m_Intitule;
                AppelCallback* appel = new AppelCallback();
                appel->m_NomFonction = "selectionnerCmdt";
                appel->m_ArgumentsParValeur.push_back(QString::number(choix_cmdt->m_BddId));
                choix->m_FonctionsAppellees.push_back(appel);
                nb_choix_cmdt--;
            }
        }
        index++;
    }

    //int nbChoixCmdts
    //Choix*
    return true;
}

bool supprimerCmdt(QVector<QString>, QVector<QString> indexCmdtSuppr)
{
    qDebug() << "supprimerCmdt ";

    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());
    Peuple* peuple = dixCmdts->GetPeuple();
    peuple->SupprimerCmdt(indexCmdtSuppr[0].toInt());

    return true;
}

bool genererChoixSuppressionCmdts(QVector<QString>, QVector<QString> )
{
    qDebug() << "genererChoixSuppressionCmdts ";
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());
    Peuple* peuple = dixCmdts->GetPeuple();

    Effet* effetCourant = Univers::ME->GetHistoire()->EffetActuel();
    effetCourant->SupprimerTousLesChoix();

    int index = 0;
    while ( index < peuple->m_Cmdts.length())
    {
        Cmdt* choix_cmdt = peuple->m_Cmdts[index]->cmdt;

        Choix* choix = effetCourant->AjouterChoixVide();
        choix->m_Text = choix_cmdt->m_Intitule;
        choix->m_GoToEffetId = "ajoutCmdt";
        AppelCallback* appel = new AppelCallback();
        appel->m_NomFonction = "supprimerCmdt";
        appel->m_ArgumentsParValeur.push_back(QString::number(index));
        choix->m_FonctionsAppellees.push_back(appel);

        index++;
    }

    return true;
}

bool testSiTempsDeChoisirCmdt(QVector<QString> caracs, QVector<QString> )
{
    int temps = Carac::GetCaracValueAsInt(caracs[0]);
    //qDebug() << "testSiTempsDeChoisirCmdt temps : "<<temps<<endl;
    //qDebug() << "testSiTempsDeChoisirCmdt ( temps % 2 == 0) : "<<( temps % 2 == 0)<<endl;

    // pour tester je renvoie true une fois sur deux mais il faudra une formule sérieuse pour ça !
    return ( temps % 2 == 0);
}

/**
 * @brief applique l'effet de tous les commandements aux caracs de coutume du peuple
 * @param caracs
 * @param vals
 * @return
 */
bool appliquerCmdts(QVector<QString> , QVector<QString> )
{
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());

    // remise à 0 de toutes les caracs coutume :
    for ( CaracCoutume* cCout: dixCmdts->m_ToutesCaracsCoutume) {
        Carac::SetValeurACaracId(cCout->m_Intitule, "0");
    }

    // application de tous les effets sur carac coutume des cmdts :
    for ( EmplacementCmdt* empl_cmdt: dixCmdts->GetPeuple()->m_Cmdts) {
        if ( empl_cmdt->cmdt != nullptr) {
            for ( EffetSurCaracCoutume* effet: empl_cmdt->cmdt->m_EffetsSurCaracCoutume) {
                Carac::AJouterValeurACaracId(effet->m_CaracCoutume->m_Intitule, effet->m_Val);
            }
        }
    }

    return true;
}


Cmdt* DixCommandements::GetCmdtViaBddId(int bdd_id)
{
    for ( Cmdt* cmdt: this->m_TousLesCmdts) {
        if ( cmdt->m_BddId == bdd_id)
            return cmdt;
    }

    Q_ASSERT_X(true, "aucun cmdt de ce bdd id n'est trouvable", "DixCommandements::GetCmdtViaBddId");

    return nullptr;
}

int DixCommandements::GetCaracCoutumeBddId(QString intitule)
{
    for (CaracCoutume* carac: this->m_ToutesCaracsCoutume) {
        if ( carac->m_Intitule == intitule) {
            return carac->m_BddId;
        }
    }

    Q_ASSERT_X(true, "id de CaracCoutume introuvable pour cet intitulé de carac", "DixCommandements::GetCaracCoutumeBddId");
    return -1;
}

void DixCommandements::GenererFonctionsCallback()
{
    this->m_CallbackFunctions["appliquerCmdts"] = &appliquerCmdts;
    this->m_CallbackFunctions["passageDuTemps"] = &passageDuTemps;
    this->m_CallbackFunctions["testSiTempsDeChoisirCmdt"] = &testSiTempsDeChoisirCmdt;
    this->m_CallbackFunctions["choisirCmdt"] = &choisirCmdt;
    this->m_CallbackFunctions["testeSiEmplacementCmdtLibre"] = &testeSiEmplacementCmdtLibre;
    this->m_CallbackFunctions["selectionnerCmdt"] = &selectionnerCmdt;
    this->m_CallbackFunctions["supprimerCmdt"] = &supprimerCmdt;
    this->m_CallbackFunctions["genererChoixSuppressionCmdts"] = &genererChoixSuppressionCmdts;
}

void DixCommandements::GenererThemes()
{
    AppliquerTheme(new ThDomainesDivins());
}

void DixCommandements::GenererHistoire()
{
    GenererEvtsAccueil();

    this->ChargerBDD("C:/Users/Mathieu/Documents/GitHub/destinCoutume/data/CoutumeSimple.db");
    //this->ChargerBDD("D:/Mathieu/GitHub/destinCoutume/data/CoutumeSimple.db");
}

Peuple* DixCommandements::GetPeuple()
{
    return static_cast<Peuple*>(this->GetPersoCourant());
}

void DixCommandements::ChargerBDD(QString cheminBDD)
{
    if ( this->m_Db.Initialisation(cheminBDD) )
    {
        // chargements de base :
        this->ChargerDomainesLoi();
        this->ChargerCaracCoutume();

        // les caracs de coutume sont chargées en tant que caracs "normales" de l'histoire (et commencent à valeur 0)
        for ( CaracCoutume* cCout: m_ToutesCaracsCoutume)
        {
            QString id = cCout->m_Intitule;

            Carac* carac = new Carac(id, cCout->m_Intitule, "0", "", cCout->m_Description, MODE_AFFICHAGE::ma_Nombre);
            this->m_Caracs.push_back(carac);

            //this->GetPersoCourant()->m_CaracsAAfficher.append(id);
        }

        this->ChargerCmdts();

        Histoire::ChargerBDD(cheminBDD);
    }
}

DomaineLoi* DixCommandements::AjouterDomaineLoi(QString intitule, QString description, int bddId, int )
{
    DomaineLoi* dl = new DomaineLoi();
    dl->m_Intitule = intitule;
    dl->m_Description = description;
    dl->m_BddId = bddId;
    //m_TousDomainesLoi.push_back(dl);
    return dl;
}

Cmdt* DixCommandements::AjouterCmdtBdd(QString intitule, QString description, int bddid, int id_domaine_loi)
{
    Cmdt* cmdt = new Cmdt();
    cmdt->m_Intitule = intitule;
    cmdt->m_Description = description;
    cmdt->m_BddId = bddid;

    // récupérer le domaine de loi associé
    /*for ( DomaineLoi* dom: this->m_TousDomainesLoi)
    {
        if ( dom->m_BddId == id_domaine_loi) {
            cmdt->m_DomaineLoi = dom;
            break;
        }
    }*/
    // et les effets sur carac coutume associés :
    cmdt->AjouterEffetsSurCaracCoutumeBdd();

    this->m_TousLesCmdts.push_back(cmdt);
    return cmdt;
}

void DixCommandements::ChargerCmdts()
{
    QSqlQuery query("SELECT * FROM Cmdt");
    int index = 0;
    while (query.next())
    {
        /*Cmdt* cmdt =*/ this->AjouterCmdtBdd(
                    query.value("intitule").toString(),
                    query.value("description").toString(),
                    query.value("id").toInt(),
                    query.value("id_domaine_loi").toInt()
                    );

        // test
        /*if ( index == 0)
            this->GetPeuple()->AppliquerCmdt(cmdt, 0);
        else if ( index == 1)
            this->GetPeuple()->AppliquerCmdt(cmdt, 1);
        else if ( index == 2)
            this->GetPeuple()->AppliquerCmdt(cmdt, 2);
        else if ( index == 3)
            this->GetPeuple()->AppliquerCmdt(cmdt, 3);
        else if ( index == 4)
            this->GetPeuple()->AppliquerCmdt(cmdt, 4);
        else if ( index == 5)
            this->GetPeuple()->AppliquerCmdt(cmdt, 5);
        else if ( index == 6)
            this->GetPeuple()->AppliquerCmdt(cmdt, 6);
        else if ( index == 7)
            this->GetPeuple()->AppliquerCmdt(cmdt, 7);
        else if ( index == 8)
            this->GetPeuple()->AppliquerCmdt(cmdt, 8);
        else if ( index == 9)
            this->GetPeuple()->AppliquerCmdt(cmdt, 9);*/

        index++;
    }
}

// conservée car elle sert pour la création d'emplacements de commandements mais elle pourrait être supprimée et réorganisée si la suppresion du DomaineLoi est confirmée
void DixCommandements::ChargerDomainesLoi()
{
    QSqlQuery query("SELECT * FROM DomaineLoi");
    while (query.next())
    {
        DomaineLoi* dom = this->AjouterDomaineLoi(
                    query.value("intitule").toString(),
                    query.value("description").toString(),
                    query.value("id").toInt(),
                    query.value("emplacements_initiaux").toInt()
                    );

        // création des emplacements de commandement associés si il y en a :
        if (dom->m_Intitule != "Métaphysique")
        {
            this->GetPeuple()->AjouterEmplacementCmdt(/*dom*/);
            if (dom->m_Intitule == "Pouvoir" ||
                    dom->m_Intitule == "Moeurs" ||
                    dom->m_Intitule == "Rituels")
            {
                this->GetPeuple()->AjouterEmplacementCmdt(/*dom*/);
            }
        }
    }
}


void DixCommandements::ChargerCaracCoutume()
{
    QSqlQuery query("SELECT * FROM CaracCoutume");
    while (query.next())
    {
       QString intitule = query.value("intitule").toString();
       //qDebug()<<intitule;
       QString description = query.value("description").toString();
       int id = query.value("id").toInt();
       CaracCoutume* car = new CaracCoutume();
       car->m_Intitule = intitule;
       car->m_Description = description;
       car->m_BddId = id;
       m_ToutesCaracsCoutume.push_back(car);
    }
}

QString DixCommandements::GetTitre()
{
    return "Coutume";
}

void DixCommandements::GenererPersos()
{
    Peuple* peuple = new Peuple(":/images/perso/peuple.jpg");
    IPerso::AjouterPersoJouable(peuple);
}

void DixCommandements::GenererEvtsAccueil()
{
    /*Evt* Debut = AjouterEvt("Debut", "Test début 10 commandements");
    Effet* intro = Debut->AjouterEffetNarration(
                "On va bientôt choisir des commandements");
*/
}
