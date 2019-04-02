#ifndef CMDT_H
#define CMDT_H
#include <QString>
#include <QVector>

struct DomaineLoi {
    int m_Id;
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
