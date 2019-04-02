#ifndef UNIVERSCOUTUME_H
#define UNIVERSCOUTUME_H


#include <QWidget>
#include "../destinLib/aventure.h"

class UniversCoutume : public Univers
{
    Q_OBJECT
private:

protected:
    // pour les aventures qui n'utilisent pas le json mais du code :surclasser aventure et développer cette fonction
    virtual void GenererAventure();
    // génère toutes les caracs qui peuvent être visualisées par le joueur (d'autres caracs peuvent être générées et invisibles n'importe quand dans l'aventure)
    virtual void GenererCaracs();

public:
    UniversCoutume(ModeAffichage modeAffichage = ModeAffichage::ema_Jeu,
                   QWidget *parent = nullptr, QString premierEvt = "", QString premierEffet = "");
};

#endif // UNIVERSCOUTUME_H
