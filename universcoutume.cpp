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

    GenererTousNomsVilles();

    GenererTousNomsRegions();

    GenererTousNomsMonts();

    GenererTousNomsFleuves();

    m_Histoire->GenererThemes();

    m_Histoire->GenererPersos();

    m_Histoire->GenererFonctionsCallback();

    m_Histoire->GenererHistoire();

    m_Perso->RafraichirAffichage();
}

void UniversCoutume::GenererTousNomsRegions()
{
    m_Regions.push_back("Péloponèse");
    m_Regions.push_back("Hellespond");
}

void UniversCoutume::GenererTousNomsMonts()
{
    m_Monts.push_back("Tmolos");
}

void UniversCoutume::GenererTousNomsFleuves()
{
    m_Fleuves.push_back("Halys");
    m_Fleuves.push_back("Tibre");
    m_Fleuves.push_back("Euphrate");
}

void UniversCoutume::GenererTousNomsVilles()
{
    m_Villes.push_back("Delphes");
    m_Villes.push_back("Pytho");
    m_Villes.push_back("Pallacia");
    m_Villes.push_back("Scylacé");
    m_Villes.push_back("Athènes");
    m_Villes.push_back("Sparte");
    m_Villes.push_back("Mégare");
    m_Villes.push_back("Nisée");
    m_Villes.push_back("Marathon");
    m_Villes.push_back("Sarde");
    m_Villes.push_back("Babyllone");
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
    m_PeuplesPays["Ciliciens"] = "Cilicie";
    m_PeuplesPays["Lyciens"] = "Lycie";
    m_PeuplesPays["Ioniens"] = "Ionie";
    m_PeuplesPays["Cimmériens"] = "Cimmérie";
    m_PeuplesPays["Hittites"] = "";
    m_PeuplesPays["Corinthiens"] = "Corinthe";
    m_PeuplesPays["Lydiens"] = "Lydie";
    m_PeuplesPays["Phrygiens"] = "Phrygie";
    m_PeuplesPays["Mysiens"] = "";
    m_PeuplesPays["Samiens"] = "Samos";
    m_PeuplesPays["Mariandynes"] = "";
    m_PeuplesPays["Chalybes"] = "";
    m_PeuplesPays["Paphlagoniens"] = "";
    m_PeuplesPays["Thraces"] = "Thrace";
    m_PeuplesPays["Thymiens"] = "";
    m_PeuplesPays["Bithyniens"] = "Bythinie";
    m_PeuplesPays["Cariens"] = "Carie";
    m_PeuplesPays["Doriens"] = "";
    m_PeuplesPays["Syriens"] = "Syrie";
    m_PeuplesPays["Éoliens"] = "Éolie";
    m_PeuplesPays["Pamphyliens"] = "";
    m_PeuplesPays["Éphésiens"] = "Éphèse";
    m_PeuplesPays["Pélasge"] = "";
    m_PeuplesPays["Crestoniates"] = "";
    m_PeuplesPays["Naxiens"] = "Naxos";
    m_PeuplesPays["Tégéates"] = "";
    m_PeuplesPays["Arcadiens"] = "Arcadie";
    m_PeuplesPays["Matiènes"] = "";
    m_PeuplesPays["Phrygiens"] = "Phrygie";
    m_PeuplesPays["Paphlagoniens"] = "Paphlagonie";
    m_PeuplesPays["Scythes"] = "Scythie";
    m_PeuplesPays["Telmessiens"] = "";
    m_PeuplesPays["Mèdes"] = "Médie";
    m_PeuplesPays["Parétacènes"] = "";
    m_PeuplesPays["Arizantes"] = "";
    m_PeuplesPays["Boudiens"] = "";
    m_PeuplesPays["Mages"] = "";

    for ( QString key : m_PeuplesPays.keys())
    {
        m_PeuplesKeys.push_back(key);
    }
}

QString UniversCoutume::GenererNomPeuple()
{
    qsrand(static_cast<unsigned int>(qrand()));
    return m_PeuplesKeys[qrand() % (m_PeuplesKeys.length() + 1)];
}

void UniversCoutume::GenererCaracs()
{
}

DixCommandements* UniversCoutume::GetHistoireDixCommandement()
{
    return dynamic_cast<DixCommandements*>(this->m_Histoire);
}

QVector<DomaineLoi*> UniversCoutume::GetTousDomainesLoi()
{
    return this->GetHistoireDixCommandement()->m_TousDomainesLoi;
}

QVector<CaracCoutume*> UniversCoutume::GetTousCaracCoutumes()
{
    return this->GetHistoireDixCommandement()->m_CaracsCoutume;
}
