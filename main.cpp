#include "saisiecmdt.h"
#include <QApplication>
#include "universcoutume.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*UniversCoutume* av = */new UniversCoutume(ModeAffichage::ema_Jeu);
   // av->show();

    SaisieCmdt w;
    w.show();

    return a.exec();
}
