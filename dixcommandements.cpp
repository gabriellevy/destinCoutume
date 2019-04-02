#include "dixcommandements.h"
#include "ui_aventure.h"
#include "peuple.h"

DixCommandements::DixCommandements(QWidget *parent):Histoire(parent)
{

}

void DixCommandements::GenererHistoire()
{
    m_Themes.append("Antiquité");

    GenererEvtsAccueil();
}


void DixCommandements::GenererPersos()
{
    Peuple peuple( "peuple", "peuple", "", ":/images/perso/peuple.jpg");
    IPerso::AjouterPersoJouable(peuple);
}

void DixCommandements::GenererEvtsAccueil()
{
    Evt* Debut = AjouterEvt("Debut", "Test début 10 commandements");
    Effet* intro = Debut->AjouterEffetNarration(
                "On va bientôt choisir des commandements");

}
