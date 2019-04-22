#ifndef CMDT_H
#define CMDT_H
#include <QString>
#include <QVector>

class Cmdt;

struct DomaineLoi {
    int m_BddId;
    QString m_Intitule;
    QString m_Description;
};

struct CaracCoutume {
    int m_Id;
    QString m_Intitule;
    QString m_Description;
};

struct EffetSurCaracCoutume {
    CaracCoutume m_CaracCoutume;
    int m_Val;
};

static int s_EmplacementIndex = 0;
struct EmplacementCmdt {
    EmplacementCmdt(DomaineLoi* domaine):m_DomaineLoi(domaine), m_Index(++s_EmplacementIndex) {
    }

    DomaineLoi* m_DomaineLoi;
    int m_Index;
    Cmdt* cmdt;
};

class Cmdt
{
public:
    explicit Cmdt();

    QString m_Titre;
    QString m_Description;
    QVector<EffetSurCaracCoutume> m_EffetsSurCaracCoutume;// liste d'améliorations de caracs de coutume
    DomaineLoi m_DomaineLoi;// id de domaine de loi divine associé

};

#endif // CMDT_H
