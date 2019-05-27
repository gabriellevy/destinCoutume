#ifndef PEUPLE_H
#define PEUPLE_H

#include "../destinLib/perso.h"
#include "../destinLib/histoire.h"
#include "cmdt.h"

class Peuple : public DPerso
{
private:
    void AjouterCaracs();
    Hist* m_Hist = nullptr;

public:
    Peuple(QString imagePortrait, Hist* hist);
    void AjouterEmplacementCmdt(/*DomaineLoi* domaine*/);

    /**
     * @brief applique le commandement dans l'emplacement d'index
     * @param cmdt
     * @param index : index de l'emplacement où ajouter le cmdt. -1 signifie le premier disponible dans l'ordre
     */
    void AppliquerCmdt(Cmdt* cmdt, int index = -1);
    void SupprimerCmdt(int index);
    bool AEmplacementLibre();
    bool ACeCommandement(Cmdt* cmdt);

    QVector<EmplacementCmdt*> m_Cmdts = {};
};

#endif // PEUPLE_H
