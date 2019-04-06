#include "thdomainesdivins.h"

ThDomainesDivins::ThDomainesDivins():Theme ("dix_commandements", "Fonctions de base des 10 commandements")
{
    Carac* carac_integrite = new Carac("integrite", "Intégrité", "1", "",
                                        "probablement la plus importante car elle conditionne le fait que votre peuple reste soudé et ne disparaîtra pas au moindre coup dur. Les commandements insistant particulièrement sur le groupe ou sur la résistance aux coups durs amélioreront l'intégrité. Exemples : Les hindouistes, les juifs, les chrétiens, ont une intégrité particulièrement forte.",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_integrite);
    Carac* carac_stabilite = new Carac("stabilite", "Stabilité", "0", "",
                                        "représente la stabilité du gouvernement et des lois. Si elle est très faible les guerres civiles risqueront d'apparaître ainsi que des révolutions",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_stabilite);
    Carac* carac_agressivite = new Carac("agressivite", "Agressivité", "0", "",
                                        "tendance de ce peuple à chercher le conflit et à résoudre les problèmes par la violence.",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_agressivite);
    Carac* carac_cruaute = new Carac("cruaute", "Cruauté", "0", "",
                                        " ",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_cruaute);
    Carac* carac_sociabilite = new Carac("sociabilite", "Sociabilité", "0", "",
                                        "à quel point ce peuple est poussé à interagir avec les autres peuples et à se faire aimer par eux",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_sociabilite);
    Carac* carac_courage = new Carac("courage", "Courage", "0", "",
                                        " ",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_courage);
    Carac* carac_determination = new Carac("determination", "Détermination", "0", "",
                                        " ",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_determination);
    Carac* carac_cupidite = new Carac("cupidite", "Cupidité", "0", "",
                                        " ",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_cupidite);
    Carac* carac_marins = new Carac("marins", "Marins", "0", "",
                                        "si le peuple a une affinité avec la mer",
                                        MODE_AFFICHAGE::ma_Nombre);
    this->m_CaracsDeBase.push_back(carac_marins);

    //m_Histoire->m_Caracs.append(new Jauge(Run::pv, "PV", 0, 8,8,"", ""));
}

QString ThDomainesDivins::integrite = "integrite";
QString ThDomainesDivins::stabilite = "stabilite";
QString ThDomainesDivins::agressivite = "agressivite";
QString ThDomainesDivins::cruaute = "cruaute";
QString ThDomainesDivins::sociabilite = "sociabilite";
QString ThDomainesDivins::courage = "courage";
QString ThDomainesDivins::determination = "determination";
QString ThDomainesDivins::cupidite = "cupidite";
QString ThDomainesDivins::marins = "marins";
