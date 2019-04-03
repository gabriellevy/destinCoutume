#include "dixcommandements.h"
#include "ui_aventure.h"
#include "peuple.h"

DixCommandements::DixCommandements(QWidget *parent):Histoire(parent)
{
    GenererThemes();
}

void DixCommandements::GenererThemes()
{
    Theme* theme10cmdts = new Theme("dix_commandements", "Fonctions de base des 10 commandements");
    Carac* carac_integrite = new Carac("integrite", "Intégrité", "1", ":/images/perso/peuple.jpg",
                                        "probablement la plus importante car elle conditionne le fait que votre peuple reste soudé et ne disparaîtra pas au moindre coup dur. Les commandements insistant particulièrement sur le groupe ou sur la résistance aux coups durs amélioreront l'intégrité. Exemples : Les hindouistes, les juifs, les chrétiens, ont une intégrité particulièrement forte.",
                                        MODE_AFFICHAGE::ma_Img);


            /*Ouverture

            Agressivité

            Cruauté

            Sociabilité : à quel point ce peuple est poussé à interagir avec les autres peuples et à les respecter

            Courage

            Détermination

            Cupidité*/

    theme10cmdts->m_Caracs.push_back(carac_integrite);
    this->m_Themes.push_back(theme10cmdts);


}

void DixCommandements::GenererHistoire()
{
    GenererEvtsAccueil();
}


void DixCommandements::GenererPersos()
{
    Peuple peuple(":/images/perso/peuple.jpg");
    peuple.m_CaracsAAfficher.append("integrite"); // temp test
    IPerso::AjouterPersoJouable(peuple);
}

void DixCommandements::GenererEvtsAccueil()
{
    Evt* Debut = AjouterEvt("Debut", "Test début 10 commandements");
    Effet* intro = Debut->AjouterEffetNarration(
                "On va bientôt choisir des commandements");

}
