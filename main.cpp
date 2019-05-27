#include "saisiecmdt.h"
#include <QApplication>
#include "universcoutume.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // lancer le jeu :
    UniversCoutume* av = new UniversCoutume(ModeAffichage::ema_Jeu);
    DixCommandements* dix_cmdts = static_cast<DixCommandements*>(av->ExecuterGenerateurHistoire());
    ExecHistoire* exec_hist = new ExecHistoire(dix_cmdts);
    av->LancerHistoire(exec_hist);
    av->show();

    // saisie de commandement :
        /*new UniversCoutume(ModeAffichage::ema_Jeu);
        SaisieCmdt w;
        w.show();*/

    return a.exec();
}
