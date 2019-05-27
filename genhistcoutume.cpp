#include "genhistcoutume.h"
#include "thdomainesdivins.h"
#include "../destinLib/univers.h"
#include "dixcommandements.h"
#include "peuple.h"
#include "universcoutume.h"

GenHistCoutume::GenHistCoutume(DixCommandements* histoireGeneree):GenHistoire (histoireGeneree)
{
}

// cette fonction peut être mise dans la bdd si elle ne fait que ça
bool passageDuTemps(QVector<QString> caracs, QVector<QString> )
{
    /*int temps =*/ Carac::AJouterValeurACaracId(caracs[0], 1);
    //qDebug() << "passageDuTemps temps : "<<temps<<endl;
    return true;
}

/**
 * @brief testeSiEmplacementCmdtLibre
 * @return true si le peuple a au moins un emplacement de commandement libre
 */
bool testeSiEmplacementCmdtLibre(QVector<QString>, QVector<QString>)
{
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());

    return dixCmdts->GetPeuple()->AEmplacementLibre();
}

/**
 * @brief appelée quand le joueur a sélectionné le cmdt d'id bddId
 * @param bddIdCmdt
 * @return
 */
bool selectionnerCmdt(QVector<QString> , QVector<QString> bddIdCmdt)
{
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());
    GenHistCoutume* gen = static_cast<GenHistCoutume*>(Univers::ME->GetGenHistoire());
    Peuple* peuple = dixCmdts->GetPeuple();

    Cmdt* nouv_cmdt = gen->GetCmdtViaBddId(bddIdCmdt[0].toInt());

    peuple->AppliquerCmdt(nouv_cmdt);

    return true;
}

/**
 * @brief génère la liste de commandments d=parmi lesquelle le joueur devra choisir
 * @param caracs
 * @return
 */
bool choisirCmdt(QVector<QString> , QVector<QString> )
{
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());

    Effet* effetCourant = Univers::ME->GetExecHistoire()->EffetActuel();
    effetCourant->SupprimerTousLesChoix();

    int nb_choix_cmdt = 6;
    int index = 0;
    while ( nb_choix_cmdt > 0 && index < dixCmdts->m_TousLesCmdts.length())
    {
        Cmdt* choix_cmdt = dixCmdts->m_TousLesCmdts[ qrand()%dixCmdts->m_TousLesCmdts.length()];
        // vérifier que ce cmdt n'est pas déjà possédé :
        bool a_deja = dixCmdts->GetPeuple()->ACeCommandement(choix_cmdt);
        if (!a_deja) {
            bool est_deja_dans_les_choix = false;
            for ( Choix* choix: effetCourant->m_Choix) {
                if ( choix->m_Text == choix_cmdt->m_Intitule) {
                    est_deja_dans_les_choix = true;
                    break;
                }
            }

            if ( !est_deja_dans_les_choix ) {
                Choix* choix = effetCourant->AjouterChoixVide();
                choix->m_Text = choix_cmdt->m_Intitule;
                AppelCallback* appel = new AppelCallback();
                appel->m_NomFonction = "selectionnerCmdt";
                appel->m_ArgumentsParValeur.push_back(QString::number(choix_cmdt->m_BddId));
                choix->m_FonctionsAppellees.push_back(appel);
                nb_choix_cmdt--;
            }
        }
        index++;
    }

    //int nbChoixCmdts
    //Choix*
    return true;
}

bool supprimerCmdt(QVector<QString>, QVector<QString> indexCmdtSuppr)
{
    qDebug() << "supprimerCmdt ";

    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());
    Peuple* peuple = dixCmdts->GetPeuple();
    peuple->SupprimerCmdt(indexCmdtSuppr[0].toInt());

    return true;
}

bool genererChoixSuppressionCmdts(QVector<QString>, QVector<QString> )
{
    qDebug() << "genererChoixSuppressionCmdts ";
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());
    Peuple* peuple = dixCmdts->GetPeuple();

    Effet* effetCourant = Univers::ME->GetExecHistoire()->EffetActuel();
    effetCourant->SupprimerTousLesChoix();

    int index = 0;
    while ( index < peuple->m_Cmdts.length())
    {
        Cmdt* choix_cmdt = peuple->m_Cmdts[index]->cmdt;

        Choix* choix = effetCourant->AjouterChoixVide();
        choix->m_Text = choix_cmdt->m_Intitule;
        choix->m_GoToEffetId = "ajoutCmdt";
        AppelCallback* appel = new AppelCallback();
        appel->m_NomFonction = "supprimerCmdt";
        appel->m_ArgumentsParValeur.push_back(QString::number(index));
        choix->m_FonctionsAppellees.push_back(appel);

        index++;
    }

    return true;
}

bool testSiTempsDeChoisirCmdt(QVector<QString> caracs, QVector<QString> )
{
    int temps = Carac::GetCaracValueAsInt(caracs[0]);
    //qDebug() << "testSiTempsDeChoisirCmdt temps : "<<temps<<endl;
    //qDebug() << "testSiTempsDeChoisirCmdt ( temps % 2 == 0) : "<<( temps % 2 == 0)<<endl;

    // pour tester je renvoie true une fois sur deux mais il faudra une formule sérieuse pour ça !
    return ( temps % 2 == 0);
}

/**
 * @brief applique l'effet de tous les commandements aux caracs de coutume du peuple
 * @param caracs
 * @param vals
 * @return
 */
bool appliquerCmdts(QVector<QString> , QVector<QString> )
{
    DixCommandements* dixCmdts = static_cast<DixCommandements*>(Univers::ME->GetHistoire());

    // remise à 0 de toutes les caracs coutume :
    for ( CaracCoutume* cCout: dixCmdts->m_ToutesCaracsCoutume) {
        Carac::SetValeurACaracId(cCout->m_Intitule, "0");
    }

    // application de tous les effets sur carac coutume des cmdts :
    for ( EmplacementCmdt* empl_cmdt: dixCmdts->GetPeuple()->m_Cmdts) {
        if ( empl_cmdt->cmdt != nullptr) {
            for ( EffetSurCaracCoutume* effet: empl_cmdt->cmdt->m_EffetsSurCaracCoutume) {
                Carac::AJouterValeurACaracId(effet->m_CaracCoutume->m_Intitule, effet->m_Val);
            }
        }
    }

    return true;
}

void GenHistCoutume::GenererFonctionsCallback()
{
    m_HistoireGeneree->m_CallbackFunctions["appliquerCmdts"] = &appliquerCmdts;
    m_HistoireGeneree->m_CallbackFunctions["passageDuTemps"] = &passageDuTemps;
    m_HistoireGeneree->m_CallbackFunctions["testSiTempsDeChoisirCmdt"] = &testSiTempsDeChoisirCmdt;
    m_HistoireGeneree->m_CallbackFunctions["choisirCmdt"] = &choisirCmdt;
    m_HistoireGeneree->m_CallbackFunctions["testeSiEmplacementCmdtLibre"] = &testeSiEmplacementCmdtLibre;
    m_HistoireGeneree->m_CallbackFunctions["selectionnerCmdt"] = &selectionnerCmdt;
    m_HistoireGeneree->m_CallbackFunctions["supprimerCmdt"] = &supprimerCmdt;
    m_HistoireGeneree->m_CallbackFunctions["genererChoixSuppressionCmdts"] = &genererChoixSuppressionCmdts;
}

void GenHistCoutume::GenererThemes()
{
    Univers::ME->GetHistoire()->AppliquerTheme(new ThDomainesDivins());
}

Hist* GenHistCoutume::GenererHistoire()
{
    GenererTousNomsPeuples();

    GenererTousNomsVilles();

    GenererTousNomsRegions();

    GenererTousNomsMonts();

    GenererTousNomsFleuves();

    GenererThemes();

    GenererPersos();

    GenererFonctionsCallback();

    GenererEvtsAccueil();

    this->ChargerBDD("C:/Users/Mathieu/Documents/GitHub/destinCoutume/data/CoutumeSimple.db");
    //this->ChargerBDD("D:/Mathieu/GitHub/destinCoutume/data/CoutumeSimple.db");

    return m_HistoireGeneree;
}

void GenHistCoutume::ChargerBDD(QString cheminBDD)
{
    if ( this->m_Db.Initialisation(cheminBDD) )
    {
        // chargements de base :
        this->ChargerDomainesLoi();
        this->ChargerCaracCoutume();

        // les caracs de coutume sont chargées en tant que caracs "normales" de l'histoire (et commencent à valeur 0)
        for ( CaracCoutume* cCout: GetDixCmdts()->m_ToutesCaracsCoutume)
        {
            QString id = cCout->m_Intitule;

            Carac* carac = new Carac(id, cCout->m_Intitule, "0", "", cCout->m_Description, MODE_AFFICHAGE::ma_Nombre);
            this->m_HistoireGeneree->m_Caracs.push_back(carac);

            //this->GetPersoCourant()->m_CaracsAAfficher.append(id);
        }

        this->ChargerCmdts();

        GenHistoire::ChargerBDD(cheminBDD);
    }
}

DomaineLoi* GenHistCoutume::AjouterDomaineLoi(QString intitule, QString description, int bddId, int )
{
    DomaineLoi* dl = new DomaineLoi();
    dl->m_Intitule = intitule;
    dl->m_Description = description;
    dl->m_BddId = bddId;
    //m_TousDomainesLoi.push_back(dl);
    return dl;
}

Cmdt* GenHistCoutume::AjouterCmdtBdd(QString intitule, QString description, int bddid, int /*id_domaine_loi*/)
{
    Cmdt* cmdt = new Cmdt(this->GetDixCmdts());
    cmdt->m_Intitule = intitule;
    cmdt->m_Description = description;
    cmdt->m_BddId = bddid;

    // récupérer le domaine de loi associé
    /*for ( DomaineLoi* dom: this->m_TousDomainesLoi)
    {
        if ( dom->m_BddId == id_domaine_loi) {
            cmdt->m_DomaineLoi = dom;
            break;
        }
    }*/
    // et les effets sur carac coutume associés :
    cmdt->AjouterEffetsSurCaracCoutumeBdd();

    this->GetDixCmdts()->m_TousLesCmdts.push_back(cmdt);
    return cmdt;
}

void GenHistCoutume::ChargerCmdts()
{
    QSqlQuery query("SELECT * FROM Cmdt");
    int index = 0;
    while (query.next())
    {
        /*Cmdt* cmdt =*/ this->AjouterCmdtBdd(
                    query.value("intitule").toString(),
                    query.value("description").toString(),
                    query.value("id").toInt(),
                    query.value("id_domaine_loi").toInt()
                    );

        // test
        /*if ( index == 0)
            this->GetPeuple()->AppliquerCmdt(cmdt, 0);
        else if ( index == 1)
            this->GetPeuple()->AppliquerCmdt(cmdt, 1);
        else if ( index == 2)
            this->GetPeuple()->AppliquerCmdt(cmdt, 2);
        else if ( index == 3)
            this->GetPeuple()->AppliquerCmdt(cmdt, 3);
        else if ( index == 4)
            this->GetPeuple()->AppliquerCmdt(cmdt, 4);
        else if ( index == 5)
            this->GetPeuple()->AppliquerCmdt(cmdt, 5);
        else if ( index == 6)
            this->GetPeuple()->AppliquerCmdt(cmdt, 6);
        else if ( index == 7)
            this->GetPeuple()->AppliquerCmdt(cmdt, 7);
        else if ( index == 8)
            this->GetPeuple()->AppliquerCmdt(cmdt, 8);
        else if ( index == 9)
            this->GetPeuple()->AppliquerCmdt(cmdt, 9);*/

        index++;
    }
}

// conservée car elle sert pour la création d'emplacements de commandements mais elle pourrait être supprimée et réorganisée si la suppresion du DomaineLoi est confirmée
void GenHistCoutume::ChargerDomainesLoi()
{
    QSqlQuery query("SELECT * FROM DomaineLoi");
    while (query.next())
    {
        DomaineLoi* dom = this->AjouterDomaineLoi(
                    query.value("intitule").toString(),
                    query.value("description").toString(),
                    query.value("id").toInt(),
                    query.value("emplacements_initiaux").toInt()
                    );

        // création des emplacements de commandement associés si il y en a :
        if (dom->m_Intitule != "Métaphysique")
        {
            this->GetDixCmdts()->GetPeuple()->AjouterEmplacementCmdt(/*dom*/);
            if (dom->m_Intitule == "Pouvoir" ||
                    dom->m_Intitule == "Moeurs" ||
                    dom->m_Intitule == "Rituels")
            {
                this->GetDixCmdts()->GetPeuple()->AjouterEmplacementCmdt(/*dom*/);
            }
        }
    }
}

void GenHistCoutume::GenererPersos()
{
    Peuple* peuple = new Peuple(":/images/perso/peuple.jpg", m_HistoireGeneree);
    IPerso::AjouterPersoJouable(peuple);
}

void GenHistCoutume::GenererEvtsAccueil()
{
    /*Evt* Debut = AjouterEvt("Debut", "Test début 10 commandements");
    Effet* intro = Debut->AjouterEffetNarration(
                "On va bientôt choisir des commandements");
*/
}


UniversCoutume* GenHistCoutume::GetUniversCoutume()
{
    return static_cast<UniversCoutume*>(Univers::ME);
}

DixCommandements* GenHistCoutume::GetDixCmdts()
{
    return static_cast<DixCommandements*>(Univers::ME->GetHistoire());
}

void GenHistCoutume::ChargerCaracCoutume()
{

    QSqlQuery query("SELECT * FROM CaracCoutume");
    while (query.next())
    {
       QString intitule = query.value("intitule").toString();
       //qDebug()<<intitule;
       QString description = query.value("description").toString();
       int id = query.value("id").toInt();
       CaracCoutume* car = new CaracCoutume();
       car->m_Intitule = intitule;
       car->m_Description = description;
       car->m_BddId = id;
       GetDixCmdts()->m_ToutesCaracsCoutume.push_back(car);
    }
}

void GenHistCoutume::GenererTousNomsRegions()
{
    UniversCoutume* univ = this->GetUniversCoutume();
    univ->m_Regions.push_back("Péloponèse");
    univ->m_Regions.push_back("Hellespond");
}

void GenHistCoutume::GenererTousNomsMonts()
{
    UniversCoutume* univ = this->GetUniversCoutume();
    univ->m_Monts.push_back("Tmolos");
}

void GenHistCoutume::GenererTousNomsFleuves()
{
    UniversCoutume* univ = this->GetUniversCoutume();
    univ->m_Fleuves.push_back("Halys");
    univ->m_Fleuves.push_back("Tibre");
    univ->m_Fleuves.push_back("Euphrate");
}


void GenHistCoutume::GenererTousNomsMasculins()
{
    UniversCoutume* univ = this->GetUniversCoutume();
    univ->m_NomsMasculins.push_back("Crésus");
    univ->m_NomsMasculins.push_back("Aion");
    univ->m_NomsMasculins.push_back("Gygès");
    univ->m_NomsMasculins.push_back("Théodore");
    univ->m_NomsMasculins.push_back("Polycrate");
    univ->m_NomsMasculins.push_back("Adraste");
    univ->m_NomsMasculins.push_back("Pantaléon");
    univ->m_NomsMasculins.push_back("Polynice");
    univ->m_NomsMasculins.push_back("Amphiaraos");
    univ->m_NomsMasculins.push_back("Alyatte");
    univ->m_NomsMasculins.push_back("Pisistrate");
    univ->m_NomsMasculins.push_back("Hippocrate");
    univ->m_NomsMasculins.push_back("Mégaclès");
    univ->m_NomsMasculins.push_back("Solon");
    univ->m_NomsMasculins.push_back("Alcméon");
    univ->m_NomsMasculins.push_back("Agamemnon");
    univ->m_NomsMasculins.push_back("Odysséus");
    univ->m_NomsMasculins.push_back("Ulysse");
    univ->m_NomsMasculins.push_back("Achille");
    univ->m_NomsMasculins.push_back("Lycurgue");
    univ->m_NomsMasculins.push_back("Lygdamis");
    univ->m_NomsMasculins.push_back("Amphilytos");
    univ->m_NomsMasculins.push_back("Léon");
    univ->m_NomsMasculins.push_back("Hégésiclès");
    univ->m_NomsMasculins.push_back("Léobotès");
    univ->m_NomsMasculins.push_back("Anaxauride");
    univ->m_NomsMasculins.push_back("Ariston");
    univ->m_NomsMasculins.push_back("Oreste");
    univ->m_NomsMasculins.push_back("Lichas");
    univ->m_NomsMasculins.push_back("Sandanis");
    univ->m_NomsMasculins.push_back("Astyage");
    univ->m_NomsMasculins.push_back("Cyaxare");
    univ->m_NomsMasculins.push_back("Cyrus");
    univ->m_NomsMasculins.push_back("Cambyse");
    univ->m_NomsMasculins.push_back("Phraorte");
    univ->m_NomsMasculins.push_back("Déiocès");
    univ->m_NomsMasculins.push_back("Alyatte");
    univ->m_NomsMasculins.push_back("Sadyatte");
    univ->m_NomsMasculins.push_back("Thalès");
    univ->m_NomsMasculins.push_back("Syennésie");
    univ->m_NomsMasculins.push_back("Labynétos");
    univ->m_NomsMasculins.push_back("Amasis");
    univ->m_NomsMasculins.push_back("Harpage");
    univ->m_NomsMasculins.push_back("Alcénor");
    univ->m_NomsMasculins.push_back("Chronios");
    univ->m_NomsMasculins.push_back("Othryadès");
    univ->m_NomsMasculins.push_back("Hyroiadès");
    univ->m_NomsMasculins.push_back("Déiocès");
    univ->m_NomsMasculins.push_back("Pythermos");
    univ->m_NomsMasculins.push_back("Lacrénès");
}

void GenHistCoutume::GenererTousNomsFeminins()
{
    UniversCoutume* univ = this->GetUniversCoutume();
    univ->m_NomsFeminins.push_back("Hélène");
    univ->m_NomsFeminins.push_back("Phye");
    univ->m_NomsFeminins.push_back("Aryénis");
    univ->m_NomsFeminins.push_back("Mandane");
}

void GenHistCoutume::GenererTousNomsVilles()
{
    UniversCoutume* univ = this->GetUniversCoutume();
    univ->m_Villes.push_back("Delphes");
    univ->m_Villes.push_back("Pytho");
    univ->m_Villes.push_back("Pallacia");
    univ->m_Villes.push_back("Scylacé");
    univ->m_Villes.push_back("Athènes");
    univ->m_Villes.push_back("Sparte");
    univ->m_Villes.push_back("Mégare");
    univ->m_Villes.push_back("Nisée");
    univ->m_Villes.push_back("Marathon");
    univ->m_Villes.push_back("Sarde");
    univ->m_Villes.push_back("Babyllone");
}
void GenHistCoutume::GenererTousNomsPeuples()
{
    UniversCoutume* univ = this->GetUniversCoutume();
    univ->m_PeuplesPays["Lacédémoniens"] = "Sparte";
    univ->m_PeuplesPays["Perses"] = "Perse";
    univ->m_PeuplesPays["Gaulois"] = "Gaule";
    univ->m_PeuplesPays["Romains"] = "Rome";
    univ->m_PeuplesPays["Latins"] = "";
    univ->m_PeuplesPays["Samnites"] = "";
    univ->m_PeuplesPays["Tarentins"] = "Tarente";
    univ->m_PeuplesPays["Tyrrhéniens"] = "";
    univ->m_PeuplesPays["Campaniens"] = "";
    univ->m_PeuplesPays["Carthaginois"] = "Carthage";
    univ->m_PeuplesPays["Mamertins"] = "";
    univ->m_PeuplesPays["Germains"] = "Germanie";
    univ->m_PeuplesPays["Sarmates"] = "";
    univ->m_PeuplesPays["Daces"] = "";
    univ->m_PeuplesPays["Thraces"] = "";
    univ->m_PeuplesPays["Ingévones"] = "";
    univ->m_PeuplesPays["Herminones"] = "";
    univ->m_PeuplesPays["Istévones"] = "";
    univ->m_PeuplesPays["Marses"] = "";
    univ->m_PeuplesPays["Gambriviens"] = "";
    univ->m_PeuplesPays["Suèves"] = "";
    univ->m_PeuplesPays["Vandales"] = "";
    univ->m_PeuplesPays["Tongres"] = "";
    univ->m_PeuplesPays["Cimbres"] = "";
    univ->m_PeuplesPays["Teutons"] = "";
    univ->m_PeuplesPays["Cauques"] = "";
    univ->m_PeuplesPays["Suèves"] = "";
    univ->m_PeuplesPays["Hermondures"] = "";
    univ->m_PeuplesPays["Cattes"] = "";
    univ->m_PeuplesPays["Chérusques"] = "";
    univ->m_PeuplesPays["Cananéens"] = "";
    univ->m_PeuplesPays["Ciliciens"] = "Cilicie";
    univ->m_PeuplesPays["Lyciens"] = "Lycie";
    univ->m_PeuplesPays["Ioniens"] = "Ionie";
    univ->m_PeuplesPays["Cimmériens"] = "Cimmérie";
    univ->m_PeuplesPays["Hittites"] = "";
    univ->m_PeuplesPays["Corinthiens"] = "Corinthe";
    univ->m_PeuplesPays["Lydiens"] = "Lydie";
    univ->m_PeuplesPays["Phrygiens"] = "Phrygie";
    univ->m_PeuplesPays["Mysiens"] = "";
    univ->m_PeuplesPays["Samiens"] = "Samos";
    univ->m_PeuplesPays["Mariandynes"] = "";
    univ->m_PeuplesPays["Chalybes"] = "";
    univ->m_PeuplesPays["Paphlagoniens"] = "";
    univ->m_PeuplesPays["Thraces"] = "Thrace";
    univ->m_PeuplesPays["Thymiens"] = "";
    univ->m_PeuplesPays["Bithyniens"] = "Bythinie";
    univ->m_PeuplesPays["Cariens"] = "Carie";
    univ->m_PeuplesPays["Doriens"] = "";
    univ->m_PeuplesPays["Syriens"] = "Syrie";
    univ->m_PeuplesPays["Éoliens"] = "Éolie";
    univ->m_PeuplesPays["Pamphyliens"] = "";
    univ->m_PeuplesPays["Éphésiens"] = "Éphèse";
    univ->m_PeuplesPays["Pélasge"] = "";
    univ->m_PeuplesPays["Crestoniates"] = "";
    univ->m_PeuplesPays["Naxiens"] = "Naxos";
    univ->m_PeuplesPays["Tégéates"] = "";
    univ->m_PeuplesPays["Arcadiens"] = "Arcadie";
    univ->m_PeuplesPays["Matiènes"] = "";
    univ->m_PeuplesPays["Phrygiens"] = "Phrygie";
    univ->m_PeuplesPays["Paphlagoniens"] = "Paphlagonie";
    univ->m_PeuplesPays["Scythes"] = "Scythie";
    univ->m_PeuplesPays["Telmessiens"] = "";
    univ->m_PeuplesPays["Mèdes"] = "Médie";
    univ->m_PeuplesPays["Parétacènes"] = "";
    univ->m_PeuplesPays["Arizantes"] = "";
    univ->m_PeuplesPays["Boudiens"] = "";
    univ->m_PeuplesPays["Mages"] = "";

    for ( QString key : univ->m_PeuplesPays.keys())
    {
        univ->m_PeuplesKeys.push_back(key);
    }
}

Cmdt* GenHistCoutume::GetCmdtViaBddId(int bdd_id)
{
    for ( Cmdt* cmdt: this->GetDixCmdts()->m_TousLesCmdts) {
        if ( cmdt->m_BddId == bdd_id)
            return cmdt;
    }

    Q_ASSERT_X(true, "aucun cmdt de ce bdd id n'est trouvable", "DixCommandements::GetCmdtViaBddId");

    return nullptr;
}

int GenHistCoutume::GetCaracCoutumeBddId(QString intitule)
{
    for (CaracCoutume* carac: this->GetDixCmdts()->m_ToutesCaracsCoutume) {
        if ( carac->m_Intitule == intitule) {
            return carac->m_BddId;
        }
    }

    Q_ASSERT_X(true, "id de CaracCoutume introuvable pour cet intitulé de carac", "DixCommandements::GetCaracCoutumeBddId");
    return -1;
}
