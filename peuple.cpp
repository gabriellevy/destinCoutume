#include "peuple.h"
#include "dixcommandements.h"
#include "universcoutume.h"

Peuple::Peuple(QString imagePortrait)
{
    m_ImagePortrait.load(imagePortrait);

    this->m_Id = this->m_Nom = ((UniversCoutume*)(Univers::ME))->GenererNomPeuple();

    //m_CaracsAAfficher.append(Run::pv);
}
