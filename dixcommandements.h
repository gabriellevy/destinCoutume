#ifndef DIXCOMMANDEMENTS_H
#define DIXCOMMANDEMENTS_H

#include "../destinLib/histoire.h"
#include "cmdt.h"

class Peuple;

class DixCommandements : public Hist
{
public:
    DixCommandements();
    static DixCommandements* ME;
    virtual QString GetTitre();

    Peuple* GetPeuple();

    //QVector<DomaineLoi*> m_TousDomainesLoi;
    QVector<CaracCoutume*> m_ToutesCaracsCoutume; // liste de toutes les caracs coutume existantes
    QVector<Cmdt*> m_TousLesCmdts;

private:
};

#endif // DIXCOMMANDEMENTS_H
