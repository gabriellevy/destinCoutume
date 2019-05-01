#ifndef UNIVERSCOUTUME_H
#define UNIVERSCOUTUME_H


#include <QWidget>
#include "../destinLib/univers.h"
#include "cmdt.h"

class DixCommandements;

class UniversCoutume : public Univers
{
    Q_OBJECT
private:
    // noms de peuple et éventuellement nom de pays associé
    QMap<QString, QString> m_PeuplesPays;
    QVector<QString> m_PeuplesKeys;
    QVector<QString> m_Villes;
    QVector<QString> m_Regions;
    QVector<QString> m_Fleuves;
    QVector<QString> m_Monts;
    void GenererTousNomsPeuples();
    void GenererTousNomsVilles();
    void GenererTousNomsRegions();
    void GenererTousNomsFleuves();
    void GenererTousNomsMonts();

protected:
    // pour les aventures qui n'utilisent pas le json mais du code :surclasser aventure et développer cette fonction
    virtual void GenererAventure();
    // génère toutes les caracs qui peuvent être visualisées par le joueur (d'autres caracs peuvent être générées et invisibles n'importe quand dans l'aventure)
    virtual void GenererCaracs();

public:
    UniversCoutume(ModeAffichage modeAffichage = ModeAffichage::ema_Jeu,
                   QWidget *parent = nullptr, QString premierEvt = "", QString premierEffet = "");

    // données génériques d'historique
    QString GenererNomPeuple();

    DixCommandements* GetHistoireDixCommandement();
    QVector<DomaineLoi*> GetTousDomainesLoi();
    QVector<CaracCoutume*> GetTousCaracCoutumes();


};

#endif // UNIVERSCOUTUME_H
