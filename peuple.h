#ifndef PEUPLE_H
#define PEUPLE_H

#include "../destinLib/perso.h"


class Peuple : public DPerso
{
private:
    void AjouterCaracs();
public:
    Peuple(QString imagePortrait);
};

#endif // PEUPLE_H
