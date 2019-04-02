#include "peuple.h"
#include "dixcommandements.h"

Peuple::Peuple(QString id, QString nom, QString description, QString imagePortrait)
    :DPerso(id, nom, description)
{
    m_ImagePortrait.load(imagePortrait);

    //m_CaracsAAfficher.append(Run::pv);
}
