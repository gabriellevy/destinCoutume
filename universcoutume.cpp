#include "universcoutume.h"
#include "../destinLib/perso.h"
#include "ui_univers.h"
#include "dixcommandements.h"
#include <qglobal.h>

UniversCoutume::UniversCoutume(ModeAffichage modeAffichage,
                               QWidget *parent,
                               QString premierEvt,
                               QString premierEffet)
: Univers(parent, modeAffichage)
{
    this->AppliquerTheme(QColor(180, 180, 210));

    this->InitialiserHistoire(new DixCommandements(ui->histoireWidget));

    GenererAventure();

    if ( premierEvt != "" )
        m_Histoire->SetCurrentEvtId( premierEvt ) ;
    if ( premierEffet!= "" )
        m_Histoire->SetEffetIndex(m_Histoire->DeterminerIndexEffet(premierEffet) );

    m_EtatPartie = EP_Deroulement;

    // tmp
    m_Reglages.m_SonOn = false;
    //fin tmp

    LancerEvtEtOuEffetCourant();
}

void UniversCoutume::GenererAventure()
{
    GenererTousNomsPeuples();

    m_Histoire->GenererThemes();

    m_Histoire->GenererPersos();

    m_Histoire->GenererFonctionsCallback();

    m_Histoire->GenererHistoire();

    m_Perso->RafraichirAffichage();
}

void UniversCoutume::GenererTousNomsPeuples()
{
    m_PeuplesPays["Lacédémoniens"] = "Sparte";
    m_PeuplesPays["Perses"] = "Perse";
    m_PeuplesPays["Gaulois"] = "Gaule";
    m_PeuplesPays["Romains"] = "Rome";
    m_PeuplesPays["Latins"] = "";
    m_PeuplesPays["Samnites"] = "";
    m_PeuplesPays["Tarentins"] = "Tarente";
    m_PeuplesPays["Tyrrhéniens"] = "";
    m_PeuplesPays["Campaniens"] = "";
    m_PeuplesPays["Carthaginois"] = "Carthage";
    m_PeuplesPays["Mamertins"] = "";
    m_PeuplesPays["Germains"] = "Germanie";
    m_PeuplesPays["Sarmates"] = "";
    m_PeuplesPays["Daces"] = "";
    m_PeuplesPays["Thraces"] = "";
    m_PeuplesPays["Ingévones"] = "";
    m_PeuplesPays["Herminones"] = "";
    m_PeuplesPays["Istévones"] = "";
    m_PeuplesPays["Marses"] = "";
    m_PeuplesPays["Gambriviens"] = "";
    m_PeuplesPays["Suèves"] = "";
    m_PeuplesPays["Vandales"] = "";
    m_PeuplesPays["Tongres"] = "";
    m_PeuplesPays["Cimbres"] = "";
    m_PeuplesPays["Teutons"] = "";
    m_PeuplesPays["Cauques"] = "";
    m_PeuplesPays["Suèves"] = "";
    m_PeuplesPays["Hermondures"] = "";
    m_PeuplesPays["Cattes"] = "";
    m_PeuplesPays["Chérusques"] = "";
    m_PeuplesPays["Cananéens"] = "";

    for ( QString key : m_PeuplesPays.keys())
    {
        m_PeuplesKeys.push_back(key);
    }
}

QString UniversCoutume::GenererNomPeuple()
{
    qsrand(qrand());
    return m_PeuplesKeys[qrand() % (m_PeuplesKeys.length() + 1)];
}

void UniversCoutume::GenererCaracs()
{
}

DixCommandements* UniversCoutume::GetHistoireDixCommandement()
{
    DixCommandements* dixcom = dynamic_cast<DixCommandements*>(this->m_Histoire);
}

QVector<DomaineLoi*> UniversCoutume::GetTousDomainesLoi()
{
    return this->GetHistoireDixCommandement()->m_TousDomainesLoi;
}
