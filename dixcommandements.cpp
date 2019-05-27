#include "dixcommandements.h"
//#include "ui_univers.h"
#include "peuple.h"
#include "cmdt.h"

DixCommandements::DixCommandements():Hist()
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
