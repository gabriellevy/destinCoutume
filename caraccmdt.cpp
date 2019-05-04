#include "caraccmdt.h"
#include "cmdt.h"

CaracCmdt::CaracCmdt(EmplacementCmdt* emplacementCmdt, QWidget *parent)
    :Carac(parent),
      m_EmplacementCmdt(emplacementCmdt)
{
    m_ModeAffichage = MODE_AFFICHAGE::ma_Img;

    int index = emplacementCmdt->m_Index;
    m_DataCarac.m_Id = "Cmdt" + QString::number(index);
    m_DataCarac.m_Valeur = "Pas de valeur encore faire un accesseur malin";
    m_DataCarac.m_Intitule = "";

    QString chemin = ":/images/icones_cmdt/" + QString::number(index) + ".png";
    m_Img.load(chemin);
}


QString CaracCmdt::GetCaracDescription()
{
    //QString domaineStr = "Domaine " + m_EmplacementCmdt->m_DomaineLoi->m_Intitule;
    QString domaineStr = "";
    if ( m_EmplacementCmdt->cmdt != nullptr)
        return m_EmplacementCmdt->cmdt->m_Intitule/* +
                "\n( " + domaineStr + " )"*/;
    else return /*domaineStr + "\n"*/
            "Pas de commandement affecté encore";
}
