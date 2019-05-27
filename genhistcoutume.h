#ifndef GENHISTCOUTUME_H
#define GENHISTCOUTUME_H

#include "../destinLib/genhistoire.h"
#include "cmdt.h"
#include "dixcommandements.h"

class ExecHistoire;
class UniversCoutume;

class GenHistCoutume : public GenHistoire
{
private:
    void GenererTousNomsPeuples();
    void GenererTousNomsMasculins();
    void GenererTousNomsFeminins();
    void GenererTousNomsVilles();
    void GenererTousNomsRegions();
    void GenererTousNomsFleuves();
    void GenererTousNomsMonts();

    void GenererEvtsAccueil();
    virtual void GenererPersos();
    virtual void GenererThemes();
    virtual void GenererFonctionsCallback();
    UniversCoutume* GetUniversCoutume();
    DixCommandements* GetDixCmdts(); // je le laisse pour l'instant mais ce n'est aps logique : on ne devrait pas utiliser de pointeur vers une histoire exécutable dans le système de génération d'histoire

public:
    GenHistCoutume(DixCommandements* histoireGeneree);

    virtual Hist* GenererHistoire();

    // gestion de la BDD
    virtual void ChargerBDD(QString cheminBDD);
    void ChargerCaracCoutume();
    void ChargerDomainesLoi();
    void ChargerCmdts();
    DomaineLoi* AjouterDomaineLoi(QString intitule, QString description, int bddId, int emplacements_initiaux);
    Cmdt* AjouterCmdtBdd(QString intitule, QString description, int bddid, int id_domaine_loi);

    Cmdt* GetCmdtViaBddId(int bdd_id);
    int GetCaracCoutumeBddId(QString intitule);
};

#endif // GENHISTCOUTUME_H
