#include "dixcommandements.h"
#include "../destinLib/univers.h"
#include "ui_univers.h"
#include "peuple.h"
#include "thdomainesdivins.h"
#include <QDebug>

DixCommandements::DixCommandements(QWidget *parent):Histoire(parent)
{
}

bool testTemp(QVector<QString> caracs, QVector<QString> vals)
{
    qDebug() << "RIEN DU TOUT JE TESTE !!!!!!!!!!!!!!!!"<<endl;
    qDebug() << "Intégrité : "<<Univers::ME->GetHistoire()->GetCaracValue(caracs[0])<<endl;
    qDebug() << "param à la con : "<<vals[0]<<endl;
    return true;
}

/**
 * @brief cette fonction gère le passage du temps cad elle incrémente la variable temps et teste si il est temps de modifier un commandement
 * @param caracs la première doit être 'tempsEnMois'
 * @param vals
 * @return true si il est temps de choisir/modifier un commandement, false si il faut lancer un nouvel événement
 */
bool passageDuTemps(QVector<QString> caracs, QVector<QString> )
{
    qDebug() << "passageDuTemps"<<endl;
    int temps = Carac::AJouterValeurACaracId(caracs[0], 1);

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
    qDebug() << "appliquerCmdts"<<endl;
    return true;
}

void DixCommandements::GenererFonctionsCallback()
{
    this->m_CallbackFunctions["testTemp"] = &testTemp;
    this->m_CallbackFunctions["appliquerCmdts"] = &appliquerCmdts;
    this->m_CallbackFunctions["passageDuTemps"] = &passageDuTemps;
}

void DixCommandements::GenererThemes()
{
    AppliquerTheme(new ThDomainesDivins());
}

void DixCommandements::GenererHistoire()
{
    GenererEvtsAccueil();

    this->ChargerBDD("C:/Users/Mathieu/Documents/GitHub/destinCoutume/data/CoutumeSimple.db");
}

void DixCommandements::ChargerBDD(QString cheminBDD)
{
    if ( this->m_Db.Initialisation(cheminBDD) )
    {
        // chargements de base :
        this->ChargerDomaineLoi();
        this->ChargerCaracCoutume();

        // les caracs de coutume sont chargées en tant que caracs "normales" de l'histoire (et commencent à valeur 0)
        for ( CaracCoutume* cCout: m_CaracsCoutume)
        {
            QString id = cCout->m_Intitule;

            Carac* carac = new Carac(id, cCout->m_Intitule, "0", "", cCout->m_Description, MODE_AFFICHAGE::ma_Nombre);
            this->m_Caracs.push_back(carac);

            this->GetPersoCourant()->m_CaracsAAfficher.append(id);
        }

        Histoire::ChargerBDD(cheminBDD);
    }
}

void DixCommandements::ChargerDomaineLoi()
{
    QSqlQuery query("SELECT * FROM DomaineLoi");
    while (query.next())
    {
       QString intitule = query.value("intitule").toString();
       QString description = query.value("description").toString();
       int id = query.value("id").toInt();
       DomaineLoi* dl = new DomaineLoi();
       dl->m_Intitule = intitule;
       dl->m_Description = description;
       dl->m_Id = id;
       m_TousDomainesLoi.push_back(dl);
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
       car->m_Id = id;
       m_CaracsCoutume.push_back(car);
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
