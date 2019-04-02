#include "universcoutume.h"
#include "../destinLib/perso.h"
#include "ui_aventure.h"
#include "dixcommandements.h"

UniversCoutume::UniversCoutume(ModeAffichage modeAffichage,
                               QWidget *parent,
                               QString premierEvt,
                               QString premierEffet)
: Univers(parent, modeAffichage)
{
    m_Perso = new IPerso(ui->persoWidget);

    m_Histoire = new DixCommandements(ui->histoireWidget);
    this->setWindowTitle("à mettre dans une génération d'histoire");

    // positionner l'interface
    ui->persoWidget->layout()->addWidget(m_Perso);
    //m_Perso->show();
    ui->histoireWidget->layout()->addWidget(m_Histoire);

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
    GenererCaracs();

    m_Histoire->GenererPersos();

    m_Histoire->GenererHistoire();

    m_Perso->RafraichirAffichage();
}

void UniversCoutume::GenererCaracs()
{
    //m_Histoire->m_Caracs.append(new Jauge(Run::pv, "PV", 0, 8,8,"", ""));
}
