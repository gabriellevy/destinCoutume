#ifndef CMDT_H
#define CMDT_H
#include <QString>
#include <QVector>

class Cmdt;
class DixCommandements;

// ce système de classification ne me semble plus utile. En attendant décision complète je le désactive
struct DomaineLoi {
    int m_BddId;
    QString m_Intitule;
    QString m_Description;
};

struct CaracCoutume {
    int m_BddId;
    QString m_Intitule;
    QString m_Description;
};

struct EffetSurCaracCoutume {
    CaracCoutume* m_CaracCoutume;
    int m_Val;
    int m_BddId;
};

static int s_EmplacementIndex = 0;
struct EmplacementCmdt {
    EmplacementCmdt(/*DomaineLoi* domaine*/):/*m_DomaineLoi(domaine),*/ m_Index(++s_EmplacementIndex) {}

    //DomaineLoi* m_DomaineLoi;
    int m_Index;
    Cmdt* cmdt = nullptr;
};

class Cmdt
{
    DixCommandements* m_Dixcom;
    EffetSurCaracCoutume* AjouterUnEffetSurCaracCoutume(int val, int id_carac_coutume, int bdd_id);

public:
    explicit Cmdt(DixCommandements* dixcom);

    QString m_Intitule;
    QString m_Description;
    QVector<EffetSurCaracCoutume*> m_EffetsSurCaracCoutume;// liste d'améliorations de caracs de coutume
    //DomaineLoi* m_DomaineLoi;// id de domaine de loi divine associé

    // gestion de la BDD
    int m_BddId;
    void AjouterEffetsSurCaracCoutumeBdd();

    // accesseurs de convénience
    DixCommandements* GetDixCommandements();

};

#endif // CMDT_H
