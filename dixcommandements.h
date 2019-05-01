#ifndef DIXCOMMANDEMENTS_H
#define DIXCOMMANDEMENTS_H

#include <QWidget>
#include "../destinLib/histoire.h"
#include "cmdt.h"

class Peuple;

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

    Peuple* GetPeuple();

    // gestion de la BDD
    virtual void ChargerBDD(QString cheminBDD);
    void ChargerCaracCoutume();
    void ChargerDomainesLoi();
    void ChargerCmdts();
    DomaineLoi* AjouterDomaineLoi(QString intitule, QString description, int bddId, int emplacements_initiaux);
    Cmdt* AjouterCmdtBdd(QString intitule, QString description, int bddid, int id_domaine_loi);
    QVector<DomaineLoi*> m_TousDomainesLoi;
    QVector<CaracCoutume*> m_CaracsCoutume; // liste de toutes les caracs coutume existantes
    QVector<Cmdt*> m_Cmdts;
    Cmdt* GetCmdtViaBddId(int bdd_id);
    int GetCaracCoutumeBddId(QString intitule);

private:
    void GenererEvtsAccueil();
    virtual void GenererPersos();
};

#endif // DIXCOMMANDEMENTS_H
