#include "saisiecmdt.h"
#include <QApplication>
#include "universcoutume.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // lancer le jeu :
        UniversCoutume* av = new UniversCoutume(ModeAffichage::ema_Jeu);
        av->show();

    // saisie de commandement :
        /*new UniversCoutume(ModeAffichage::ema_Jeu);
        SaisieCmdt w;
        w.show();*/

    return a.exec();
}
