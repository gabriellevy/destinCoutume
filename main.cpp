//#include "mainwindow.h"
#include <QApplication>
#include "universcoutume.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*MainWindow w;
    w.show();*/

    UniversCoutume* av = new UniversCoutume(ModeAffichage::ema_Jeu);
    av->show();

    return a.exec();
}
