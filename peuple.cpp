#include "peuple.h"
#include "dixcommandements.h"
#include "universcoutume.h"
#include "thdomainesdivins.h"
#include "caraccmdt.h"

Peuple::Peuple(QString imagePortrait)
{
    m_ImagePortrait.load(imagePortrait);

    this->m_Id = this->m_Nom = (static_cast<UniversCoutume*>(Univers::ME))->GenererNomPeuple();

    this->AjouterCaracs();
    // temp test :
    /*this->m_CaracsAAfficher.append(ThDomainesDivins::integrite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::agressivite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::cruaute);
    this->m_CaracsAAfficher.append(ThDomainesDivins::sociabilite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::courage);
    this->m_CaracsAAfficher.append(ThDomainesDivins::determination);
    this->m_CaracsAAfficher.append(ThDomainesDivins::cupidite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::integrite);
    this->m_CaracsAAfficher.append(ThDomainesDivins::marins);*/
    // fin temp test
}

void Peuple::AjouterCaracs()
{
    Univers::ME->GetHistoire()->m_Caracs.push_back(
                new Carac(
                    "tempsEnMois",
                    "Temps en mois",
                    "0",
                    "",
                    "Temps en mois passé depuis la création du peuple",
                    MODE_AFFICHAGE::ma_Nombre));
    this->m_CaracsAAfficher.append("tempsEnMois");
}


void Peuple::AppliquerCmdt(Cmdt* cmdt, int index)
{
    this->m_Cmdts[index]->cmdt = cmdt;
}

void Peuple::AjouterEmplacementCmdt(DomaineLoi* domaine)
{
    EmplacementCmdt* empl = new EmplacementCmdt(domaine);
    this->m_Cmdts.push_back(empl);

    CaracCmdt* carac = new CaracCmdt(empl);
    Univers::ME->GetHistoire()->m_Caracs.push_back(carac);

    this->m_CaracsAAfficher.append(carac->m_DataCarac.m_Id);
}
