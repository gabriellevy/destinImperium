#include "crime.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "warp/voyage.h"
#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/aleatoire.h"
#include "classesociale.h"
#include "humanite/pbsante.h"
#include "socio_eco/economieevt.h"

// caracs :
QString Crime::C_CRIMINEL = "Est criminel";
QString Crime::C_GANG = "Gang";
//valeurs de criminel : ("" signifie innocent). Note : être jugé innocent même si n est coupable remet en ""
QString Crime::DELINQUANT = "Délinquant";
QString Crime::CRIMINEL = "Criminel";
// valeurs de GenVieHumain::C_LIBERTE :
QString Crime::CAPTURE_POLICE = "Capturé par la police";
QString Crime::CAPTURE_ARBITES = "Capturé par l'Adeptus Arbites";
QString Crime::CAPTURE_ORDO_HERETICUS = "Capturé par l'Ordo Hereticus";

Crime::Crime(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0; //pour les tests (doit être à 0 en prod)
    switch (indexEvt) {
    case 0 : {
        m_Nom = Crime::DELINQUANT;
        m_ConditionSelecteurProba = new Condition(0.01 + tmp_Modificateur, p_Relative);
        m_Description = "Vous vous mettez à voler à droite à gauche pour survivre";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  "",
                                  Comparateur::c_Egal));
        m_Conditions.push_back(
                    new Condition(ClasseSociale::C_CLASSE_SOCIALE,
                                  ClasseSociale::MISERABLES,
                                  Comparateur::c_Egal));
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::DELINQUANT;
        m_ConditionSelecteurProba = Planete::AjouterModifProbaSiMondeRuche(m_ConditionSelecteurProba, 0.02);

    }break;
    case 1 : {
        m_Nom = Crime::CRIMINEL + "_1";
        m_ConditionSelecteurProba = new Condition(0.0001 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_Description = "Vos perversions vous poussent à devenir un violeur de plus en plus dépravé.";
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;

    }break;
    case 2 : {
        m_Nom = Crime::CRIMINEL + "_2";
        m_ConditionSelecteurProba = new Condition(0.0001 + tmp_Modificateur, p_Relative);
        m_Description = "Votre soif de richesse fait de vous un criminel de plus en plus violent.";
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;

    }break;
    case 3 : {
        m_Nom = Crime::CAPTURE_POLICE;
        m_ConditionSelecteurProba = new Condition(0.005 + tmp_Modificateur, p_Relative);
        m_Description = "Vous avez été capturé par la police pour vos méfaits.";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  "",
                                  Comparateur::c_Different));
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_POLICE;

    }break;
    case 4 : {
        m_Nom = Crime::CAPTURE_ARBITES;
        m_ConditionSelecteurProba = new Condition(0.001 + tmp_Modificateur, p_Relative);
        m_Description = "Vous avez été capturé par l'Adeptus Arbites pour vos méfaits.";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  Crime::CRIMINEL,
                                  Comparateur::c_Egal));
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_ARBITES;

    }break;
    case 5 : {
        m_Nom = "Exécuté par un arbitrator";
        m_ConditionSelecteurProba = new Condition(0.05 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes jugé et condamné à mort pour vos crimes. La sentence est exécutée immédiatement par le juge Arbitrator.";
        m_Image = ":/images/metier/juge.jpg";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_ARBITES,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;

    }break;
    case 6 : {
        m_Nom = "Exécuté par la justice";
        m_ConditionSelecteurProba = new Condition(0.01 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes jugé et condamné à mort pour vos crimes. La sentence est exécutée le mois suivant.";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_POLICE,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;

    }break;
    case 7 : {
        m_Nom = "Transformé en serviteur";
        m_ConditionSelecteurProba = new Condition(0.01 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes jugé et condamné à être transformé en serviteur décérébré jusqu'à la fin de vos jours. Vous êtes lobotomisé le mois suivant...";
        m_Image = ":/images/metier/serviteur.jpg";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_POLICE,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;

    }break;
    case 8 : {
        m_Nom = Crime::DELINQUANT + "_" + ClasseSociale::PAUVRES;
        m_ConditionSelecteurProba = new Condition(0.002 + tmp_Modificateur, p_Relative);
        m_Description = "Vous prenez l'habitude de vous battre et de voler.";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  "",
                                  Comparateur::c_Egal));
        m_Conditions.push_back(
                    new Condition(ClasseSociale::C_CLASSE_SOCIALE,
                                  ClasseSociale::PAUVRES,
                                  Comparateur::c_Egal));
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::DELINQUANT;
        m_ConditionSelecteurProba = Planete::AjouterModifProbaSiMondeRuche(m_ConditionSelecteurProba, 0.02);

    }break;
    case 9 : {
        m_Nom = "joint_" + Crime::C_GANG;
        m_ConditionSelecteurProba = new Condition(0.002 + tmp_Modificateur, p_Relative);
        QString gang = Crime::GenererNomGang();
        m_Description = "Vous rejoignez le gang " + gang + ".";
        m_Image = ":/images/crime/gang.PNG";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  Crime::DELINQUANT,
                                  Comparateur::c_Egal));
        m_Conditions.push_back(
                    new Condition(Crime::C_GANG,
                                  "",
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[Crime::C_GANG] = gang;
        m_ConditionSelecteurProba = Planete::AjouterModifProbaSiMondeRuche(m_ConditionSelecteurProba, 0.02);

    }break;
    case 10 : {
        m_Nom = "Envoyé en travail forcé en monde minier";
        m_ConditionSelecteurProba = new Condition(0.01 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes jugé et condamné à travailler dans la colonie pénale d'un monde minier.";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_ARBITES,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = Planete::GetPlaneteAleatoire(false, false, Planete::PLANETE_MINIERE)->m_Nom;
        m_ModificateursCaracs[Metier::C_METIER] = Metier::MINEUR;
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::MISERABLES;

    }break;
    case 11 : {
        m_Nom = "Misérable qui devient pauvre par le crime";
        m_ConditionSelecteurProba = new Condition(0.001 + tmp_Modificateur, p_Relative);
        Crime::AjouterModificateurDeProbaSiDelinquant(m_ConditionSelecteurProba, 0.01);
        Crime::AjouterModificateurDeProbaSiCriminel(m_ConditionSelecteurProba, 0.01);
        m_Description = "Par un crime très astucieux vous parvenez à vous enrichir considérablement.";
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::MISERABLES));
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::PAUVRES;

    }break;
    case 12 : {
        m_Nom = "Pauvre qui devient classe moyenne par le crime";
        m_ConditionSelecteurProba = new Condition(0.001 + tmp_Modificateur, p_Relative);
        Crime::AjouterModificateurDeProbaSiDelinquant(m_ConditionSelecteurProba, 0.01);
        Crime::AjouterModificateurDeProbaSiCriminel(m_ConditionSelecteurProba, 0.01);
        m_Description = "Par un crime très astucieux vous parvenez à vous enrichir considérablement.";
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::PAUVRES));
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::CLASSE_MOYENNE;

    }break;
    case 13 : {
        m_Nom = "Vendeur de drogue";
        m_ConditionSelecteurProba = new Condition(0.01 + tmp_Modificateur, p_Relative);
        m_Description = "VOus mettez en place un petit réseau de revente de drogue sur votre lieu "
                "de travail qui vous fait très bien voir de vos collègues.";
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        m_Conditions.push_back(Crime::AjouterConditionSiMalhonnete());
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::DELINQUANT;
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = 3;

    }break;
    }
}

Condition* Crime::AjouterModificateurDeProbaSiDelinquant(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {         new Condition(Crime::C_CRIMINEL, Crime::DELINQUANT, Comparateur::c_Egal)        });
    return cond;
}

Condition* Crime::AjouterModificateurDeProbaSiCriminel(Condition* cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {         new Condition(Crime::C_CRIMINEL, Crime::CRIMINEL, Comparateur::c_Egal)        });
    return cond;
}

QList<QString> Crime::NOMS_GANGS = {
    "Mara Salvatrucha", "Hell's Angels", "Camorra", "Los Zetas", "Yakuzas", "The Crips", "The Bloods", "Mongrel Mob",
    "Bahala Na", "Big Circle", "Born To Kill", "Bing Kong Tong", "Hip Sing Tong", "Ying On Tong", "Satanas", "Tiny Rascal Gang",
    "Wah Ching", "Triades", "Chung Ching Yee", "Chung Ching Yee", "Chung Ching Yee", "Breed Street", "Venice 13", "Culver City Boyz",
    "Maravilla", "avenidas", "Onterio Varrio Sur", "Tortilla Flats", "Rockwood", "Hazard", "Harpys 13", "Varrio Pico Nuevo", "Inglewood 13",
    "Rivas", "Whittier", "La Eme", "El Monte Flores", "norwalk los one ways gang", "White Fence", "Ñetas", "NFOD", "Hessians",
    "Milieu", "Les Apaches", "Les Loups de la Butte", "Cœurs d’Acier", "Gars d'Charonne", "Milieu", "Mitan",
};

QString Crime::GenererNomGang()
{
    return Crime::NOMS_GANGS[Aleatoire::GetAl()->EntierInferieurA(Crime::NOMS_GANGS.length())];
}

Condition* Crime::AjouterConditionSiLibre()
{    return new Condition(GenVieHumain::C_LIBERTE, "", Comparateur::c_Egal);}

Condition* Crime::AjouterConditionSiNonLibre()
{    return new Condition(GenVieHumain::C_LIBERTE, "", Comparateur::c_Different);}

Condition* Crime::AjouterConditionSiJamaisCriminel()
{    return new Condition(Crime::C_CRIMINEL, "", Comparateur::c_Egal);}

Condition* Crime::AjouterConditionSiMalhonnete()
{    return new Condition(Crime::C_CRIMINEL, "", Comparateur::c_Different);}

