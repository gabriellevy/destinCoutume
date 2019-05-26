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

void UniversCoutume::ExecuterGenerateurHistoire(QWidget *parent)
{
    m_GenHistoire = new GenHistCoutume(parent);
    m_Histoire = m_GenHistoire->GenererHistoire();
}

void UniversCoutume::LancerHistoire(QString premierEvt, QString premierEffet, bool BarreDeCote)
{
    Univers::LancerHistoire(premierEvt, premierEffet, BarreDeCote);

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
