#include "cmdt.h"
#include <QString>
#include "../destinLib/dbmanager.h"
#include "dixcommandements.h"
#include "universcoutume.h"

Cmdt::Cmdt(DixCommandements* dixcom):m_Dixcom(dixcom)
{

}

DixCommandements* Cmdt::GetDixCommandements()
{
    return m_Dixcom;
}

EffetSurCaracCoutume* Cmdt::AjouterUnEffetSurCaracCoutume(int val, int id_carac_coutume, int bdd_id)
{
    EffetSurCaracCoutume* effet = new EffetSurCaracCoutume();
    effet->m_Val = val;
    effet->m_BddId = bdd_id;

    // récupérer la bonne carac coutume et l'associer :
    for ( CaracCoutume* cCout: GetDixCommandements()->m_ToutesCaracsCoutume)
    {
        if ( cCout->m_BddId == id_carac_coutume) {
            effet->m_CaracCoutume = cCout;
            break;
        }
    }

    this->m_EffetsSurCaracCoutume.push_back(effet);
}

void Cmdt::AjouterEffetsSurCaracCoutumeBdd()
{
    // int val, int id_carac_coutume, int bddid, int id_cmdt
    QSqlQuery query("SELECT * FROM EffetCaracCoutume WHERE id_cmdt = " + QString::number(this->m_BddId));
    while (query.next())
    {
        EffetSurCaracCoutume* effet = this->AjouterUnEffetSurCaracCoutume(
                    query.value("val").toInt(),
                    query.value("id_carac_coutume").toInt(),
                    query.value("id").toInt()
                    );
    }
}
