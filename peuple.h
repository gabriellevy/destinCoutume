#ifndef PEUPLE_H
#define PEUPLE_H

#include "../destinLib/perso.h"


class Peuple : public DPerso
{
public:
    Peuple(QString id, QString nom, QString description, QString imagePortrait);
};

#endif // PEUPLE_H
