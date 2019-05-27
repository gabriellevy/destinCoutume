#include "universcoutume.h"
#include "../destinLib/perso.h"
#include "ui_univers.h"
#include "dixcommandements.h"
#include "genhistcoutume.h"
#include <qglobal.h>

UniversCoutume::UniversCoutume(ModeAffichage modeAffichage,
                               QWidget *parent)
: Univers(parent, modeAffichage)
{
    this->AppliquerTheme(QColor(180, 180, 210));
}

Hist* UniversCoutume::ExecuterGenerateurHistoire()
{
    m_Histoire = new DixCommandements();
    m_GenHistoire = new GenHistCoutume(static_cast<DixCommandements*>(m_Histoire));
    m_GenHistoire->GenererHistoire();
    return m_Histoire;
}

void UniversCoutume::LancerHistoire(ExecHistoire* execHistoire, QWidget *parent, QString premierEvt, QString premierEffet, bool BarreDeCote)
{
    Univers::LancerHistoire(execHistoire, parent, premierEvt, premierEffet, BarreDeCote);

    if ( premierEvt != "" )
        m_ExecHistoire->SetCurrentEvtId( premierEvt ) ;
    if ( premierEffet!= "" )
        m_ExecHistoire->SetEffetIndex(m_ExecHistoire->DeterminerIndexEffet(premierEffet) );

    m_EtatPartie = EP_Deroulement;

    // tmp
    m_Reglages.m_SonOn = false;
    //fin tmp

    LancerEvtEtOuEffetCourant();
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
    return dynamic_cast<DixCommandements*>(this->m_ExecHistoire);
}

GenHistCoutume* UniversCoutume::GetGenHistCoutume()
{
    return dynamic_cast<GenHistCoutume*>(this->m_GenHistoire);
}

/*QVector<DomaineLoi*> UniversCoutume::GetTousDomainesLoi()
{
    return this->GetHistoireDixCommandement()->m_TousDomainesLoi;
}*/

QVector<CaracCoutume*> UniversCoutume::GetTousCaracCoutumes()
{
    return this->GetHistoireDixCommandement()->m_ToutesCaracsCoutume;
}
