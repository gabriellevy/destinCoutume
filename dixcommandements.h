#ifndef DIXCOMMANDEMENTS_H
#define DIXCOMMANDEMENTS_H

#include <QWidget>
#include "../destinLib/histoire.h"
#include "cmdt.h"

class DixCommandements : public Histoire
{
    Q_OBJECT

public:
    DixCommandements(QWidget *parent = nullptr);

    virtual void GenererHistoire();
    virtual QString GetTitre();

    virtual void GenererThemes();

    // gestion de la BDD
    virtual void ChargerBDD(QString cheminBDD);
    void ChargerDomaineLoi();
    void ChargerCaracCoutume();
    QList<DomaineLoi*>  m_TousDomainesLoi;
    QList<CaracCoutume*> m_CaracsCoutume;

private:
    void GenererEvtsAccueil();
    virtual void GenererPersos();
};

#endif // DIXCOMMANDEMENTS_H
