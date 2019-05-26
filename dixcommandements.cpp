#include "dixcommandements.h"
#include "ui_univers.h"
#include "peuple.h"
#include "cmdt.h"
#include <QDebug>

DixCommandements::DixCommandements(QWidget *parent):ExecHistoire(parent)
{
}

Peuple* DixCommandements::GetPeuple()
{
    return static_cast<Peuple*>(this->GetPersoCourant());
}

QString DixCommandements::GetTitre()
{
    return "Coutume";
}
