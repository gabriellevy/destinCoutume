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
    static DixCommandements* ME;

    virtual void GenererHistoire();
    virtual QString GetTitre();

    virtual void GenererThemes();
    virtual void GenererFonctionsCallback();

    void AjouterDomaineLoi(QString intitule, QString description);
    void ChargerDomaineLoi();
    // gestion de la BDD
    virtual void ChargerBDD(QString cheminBDD);
    void ChargerCaracCoutume();
    QList<DomaineLoi*>  m_TousDomainesLoi;
    QList<CaracCoutume*> m_CaracsCoutume;

private:
    void GenererEvtsAccueil();
    virtual void GenererPersos();
};

#endif // DIXCOMMANDEMENTS_H
