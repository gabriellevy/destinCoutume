#ifndef UNIVERSCOUTUME_H
#define UNIVERSCOUTUME_H


#include <QWidget>
#include "../destinLib/univers.h"

class UniversCoutume : public Univers
{
    Q_OBJECT
private:
    // noms de peuple et éventuellement nom de pays associé
    QMap<QString, QString> m_PeuplesPays;
    QVector<QString> m_PeuplesKeys;
    void GenererTousNomsPeuples();

protected:
    // pour les aventures qui n'utilisent pas le json mais du code :surclasser aventure et développer cette fonction
    virtual void GenererAventure();
    // génère toutes les caracs qui peuvent être visualisées par le joueur (d'autres caracs peuvent être générées et invisibles n'importe quand dans l'aventure)
    virtual void GenererCaracs();

public:
    UniversCoutume(ModeAffichage modeAffichage = ModeAffichage::ema_Jeu,
                   QWidget *parent = nullptr, QString premierEvt = "", QString premierEffet = "");

    QString GenererNomPeuple();
};

#endif // UNIVERSCOUTUME_H
