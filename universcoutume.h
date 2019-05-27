#ifndef UNIVERSCOUTUME_H
#define UNIVERSCOUTUME_H

#include <QWidget>
#include "../destinLib/univers.h"
#include "cmdt.h"
#include "genhistcoutume.h"

class DixCommandements;

class UniversCoutume : public Univers
{
    Q_OBJECT
private:

protected:
    // génère toutes les caracs qui peuvent être visualisées par le joueur (d'autres caracs peuvent être générées et invisibles n'importe quand dans l'aventure)
    virtual void GenererCaracs();

public:
    UniversCoutume(ModeAffichage modeAffichage = ModeAffichage::ema_Jeu,
                   QWidget *parent = nullptr);

    // données génériques d'historique
    QString GenererNomPeuple();
    virtual Hist* ExecuterGenerateurHistoire();
    virtual void LancerHistoire(ExecHistoire* execHistoire, QWidget *parent = nullptr, QString premierEvt = "", QString premierEffet = "", bool BarreDeCote = true);

    DixCommandements* GetHistoireDixCommandement();
    GenHistCoutume* GetGenHistCoutume();
    //QVector<DomaineLoi*> GetTousDomainesLoi();
    QVector<CaracCoutume*> GetTousCaracCoutumes();

    // noms de peuple et éventuellement nom de pays associé
    QMap<QString, QString> m_PeuplesPays;
    QVector<QString> m_PeuplesKeys;
    QVector<QString> m_Villes;
    QVector<QString> m_Regions;
    QVector<QString> m_Fleuves;
    QVector<QString> m_Monts;
    QVector<QString> m_NomsMasculins;
    QVector<QString> m_NomsFeminins;

};

#endif // UNIVERSCOUTUME_H
