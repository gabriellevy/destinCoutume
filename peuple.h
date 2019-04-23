#ifndef PEUPLE_H
#define PEUPLE_H

#include "../destinLib/perso.h"
#include "cmdt.h"

class Peuple : public DPerso
{
private:
    void AjouterCaracs();
    QVector<EmplacementCmdt*> m_Cmdts = {};

public:
    Peuple(QString imagePortrait);
    void AjouterEmplacementCmdt(DomaineLoi* domaine);
    /**
     * @brief applique le commandement dans l'emplacement d'index
     */
    void AppliquerCmdt(Cmdt* cmdt, int index);
};

#endif // PEUPLE_H
