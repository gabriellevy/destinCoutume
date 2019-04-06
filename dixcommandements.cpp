#include "dixcommandements.h"
#include "ui_univers.h"
#include "peuple.h"
#include "thdomainesdivins.h"

DixCommandements::DixCommandements(QWidget *parent):Histoire(parent)
{
}

void DixCommandements::GenererThemes()
{
    AppliquerTheme(new ThDomainesDivins());
}

void DixCommandements::GenererHistoire()
{
    GenererEvtsAccueil();
}

QString DixCommandements::GetTitre()
{
    return "Coutume";
}

void DixCommandements::GenererPersos()
{
    Peuple peuple(":/images/perso/peuple.jpg");
    IPerso::AjouterPersoJouable(peuple);
}

void DixCommandements::GenererEvtsAccueil()
{
    Evt* Debut = AjouterEvt("Debut", "Test début 10 commandements");
    Effet* intro = Debut->AjouterEffetNarration(
                "On va bientôt choisir des commandements");

}
