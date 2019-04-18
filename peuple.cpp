#include "peuple.h"
#include "dixcommandements.h"
#include "universcoutume.h"
#include "thdomainesdivins.h"

Peuple::Peuple(QString imagePortrait)
{
    m_ImagePortrait.load(imagePortrait);

    this->m_Id = this->m_Nom = ((UniversCoutume*)(Univers::ME))->GenererNomPeuple();

    this->m_CaracsAAfficher.append("tempsEnMois");

    // temp test :
    /*this->m_CaracsAAfficher.append(ThDomainesDivins::integrite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::agressivite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::cruaute);
    this->m_CaracsAAfficher.append(ThDomainesDivins::sociabilite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::courage);
    this->m_CaracsAAfficher.append(ThDomainesDivins::determination);
    this->m_CaracsAAfficher.append(ThDomainesDivins::cupidite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::integrite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::marins);*/
    // fin temp test
}
