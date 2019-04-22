#ifndef PEUPLE_H
#define PEUPLE_H

#include "../destinLib/perso.h"
#include "cmdt.h"

struct EmplacementCmdt {
    EmplacementCmdt(DomaineLoi* domaine):m_DomaineLoi(domaine) {
    }

    DomaineLoi* m_DomaineLoi;
    Cmdt* cmdt;
};

class Peuple : public DPerso
{
private:
    void AjouterCaracs();
    void InitialiserEmplacementsCmdts();
    QVector<EmplacementCmdt> m_Cmdts = {};

public:
    Peuple(QString imagePortrait);
};

#endif // PEUPLE_H
