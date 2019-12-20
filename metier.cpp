#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "types_planete/planet.h"
#include "warp/voyage.h"
#include "socio_eco/crime.h"
#include "factions/assassinorum.h"
#include "factions/marineimperiale.h"
#include "factions/adeptusmechanicus.h"
#include "humain.h"

QString Metier::C_METIER = "Métier";

QString Metier::PAYSAN = "Paysan";
QString Metier::MINEUR = "Mineur";
QString Metier::CHASSEUR_CUEILLEUR_NOMADE = "Chasseur cueilleur nomade";
QString Metier::OUVRIER = "Ouvrier";
QString Metier::GARDE_IMPERIAL = "Garde Imperial";
QString Metier::MARIN_IMPERIAL = "Marin Imperial";
QString Metier::ADEPTE_ADMINISTRATUM = "Adepte Administratum";
QString Metier::TECHNOPRETRE = "Technoprêtre";
QString Metier::ARBITES = "Arbitrator"; // Adeptus Arbites
// mondes chevaliers :
QString Metier::NOBLE_CHEVALIER = "Noble Chevalier";
QString Metier::INQUISITEUR = "Inquisiteur";
QString Metier::SERVANT_ADEPTUS_ASTRONOMICA = "Servant Adeptus Astronomica";
QString Metier::ADEPTUS_ASSASSINORUM = "Adeptus Assassinorum";
QString Metier::ADEPTUS_MINISTORUM = "Adeptus Ministorum";
// psykers
QString Metier::SCHOLIA_PSYKANA = "Scholia Psykana";

QMap<QString, Metier*> Metier::METIERS;

Metier::Metier(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmpFavoriseur = 0.0; // valeur servant à tester => à mettre à 0 pour un test final
    switch (indexEvt) {
    case 0 : {
        m_Nom = Metier::PAYSAN;
        m_ConditionSelecteurProba = new Condition(0.1 - tmpFavoriseur, p_Relative);
        // plus de chances d'êtres paysans sur les mondes agricoles et médiévaux
        Planete::AjouterModifProbaSiMondeAgricole(m_ConditionSelecteurProba, 0.8);
        Planete::AjouterModifProbaSiMondeFeodal(m_ConditionSelecteurProba, 0.6);
    }break;
    case 1 : {
        m_Nom = Metier::ADEPTE_ADMINISTRATUM;
        m_Image = ":/images/metier/Administratum Adept.png";
        m_ConditionSelecteurProba = new Condition(0.15 - tmpFavoriseur, p_Relative);
    }break;
    case 2 : {
        m_Nom = Metier::NOBLE_CHEVALIER;
        m_ConditionSelecteurProba = new Condition(0 - tmpFavoriseur, p_Relative);
        Planete::AjouterModifProbaSiMondeChevalier(m_ConditionSelecteurProba, 0.01);
        m_Conditions.push_back( Planete::AjouterConditionSiMondeChevalier() );
    }break;
    case 3 : {
        m_Nom = Metier::GARDE_IMPERIAL;
        m_Image = ":/images/metier/garde-imperial.jpg";
        m_ConditionSelecteurProba = new Condition(0.02 - tmpFavoriseur, p_Relative);
        // plus de chances de devenir garde sur les mondes férals et médiévaux
        Planete::AjouterModifProbaSiMondeFeodal(m_ConditionSelecteurProba, 0.2);
        Planete::AjouterModifProbaSiMondeFeral(m_ConditionSelecteurProba, 0.2);
    }break;
    case 4 : {
        m_Nom = Metier::ARBITES;
        m_Description = "Agent de l'Adeptus Arbites, l'agence chargée de faire respecter la loi impériale. Vous allez bientôt être affecté à votre planète de garnison.";
        m_Image = ":/images/metier/Arbitrator.jpg";
        m_ConditionSelecteurProba = new Condition(0.01 - tmpFavoriseur, p_Relative);
        // à peine nommé, un arbitrator est affecté à une nouvelle planète
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = Voyage::ALEATOIRE;
        m_Conditions.push_back(Crime::AjouterConditionSiJamaisCriminel());
    }break;
    case 5 : {
        m_Nom = Metier::INQUISITEUR;
        m_Description = "Agent de l'Inquisition, une organisation secrète chargée de traquer les ennemis de l'imperium.";
        m_Image = ":/images/metier/inquisiteur.jpg";
        m_ConditionSelecteurProba = new Condition(0.001 - tmpFavoriseur, p_Relative);
        // à peine nommé, un Inquisiteur est affecté à une nouvelle planète
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = Voyage::ALEATOIRE;
        m_Conditions.push_back(Crime::AjouterConditionSiJamaisCriminel());
    }break;
    case 6 : {
        m_Nom = Metier::SERVANT_ADEPTUS_ASTRONOMICA;
        m_Description = "Vous êtes un servant dévoué héréditaire de l'Adeptus Astronomica. Comme vos parents avant vous et les parents de vos parents.";
        m_Image = ":/images/organisations/Adeptus_Astronomica_Icon_update.jpg";
        m_ConditionSelecteurProba = new Condition(0.001 - tmpFavoriseur, p_Relative);
        m_Conditions.push_back(new Condition(Planete::C_PLANETE, Planete::TERRE, Comparateur::c_Egal));
        m_Conditions.push_back(Crime::AjouterConditionSiJamaisCriminel());
        m_Conditions.push_back( Planete::AjouterConditionSiPasMondeFeral() );
    }break;
    case 7 : {
        m_Nom = Metier::ADEPTUS_ASSASSINORUM;
        m_Description = "Vous êtes maintenant un fonctionnaire dévoué du très secret Officio Assassinorum.";
        m_Image = ":/images/organisations/Officio_Assassinorum_symbol_2.png";
        m_CallbackDisplay = [] {
            QString temple = Assassinorum::DeterminerTempleAleatoire();
            ExecHistoire::GetEffetActuel()->m_Texte = "Vous êtes maintenant un fonctionnaire dévoué du très secret"
                     " Officio Assassinorum. Votre temple est le temple " + temple + ".";

            Humain::GetHumainJoue()->SetValeurACaracId(Assassinorum::C_TEMPLE, temple);
        };
        m_ConditionSelecteurProba = new Condition(0.001 - tmpFavoriseur, p_Relative);
        m_Conditions.push_back(Crime::AjouterConditionSiJamaisCriminel());
        m_Conditions.push_back( Planete::AjouterConditionSiPasMondeFeral() );
    }break;
    case 8 : {
        m_Nom = Metier::ADEPTUS_MINISTORUM;
        m_Description = "Vous êtes maintenant un fonctionnaire dévoué du très saint Adeptus Ministorum.";
        m_Image = ":/images/organisations/Adeptus_Ministorum_Icon.jpg";
        m_ConditionSelecteurProba = new Condition(0.1 - tmpFavoriseur, p_Relative);
    }break;
    case 9 : {
        m_Nom = Metier::MARIN_IMPERIAL;
        m_Description = "Vous vous engagez dans la marine impériale.";
        m_Image = ":/images/organisations/FlotteImperialeDeGuerre.jpg";
        m_ConditionSelecteurProba = new Condition(0.01 - tmpFavoriseur, p_Relative);
        m_Conditions.push_back( Planete::AjouterConditionSiPasMondeFeral() );
    }break;
    case 10 : {
        m_Nom = Metier::OUVRIER;
        m_ConditionSelecteurProba = new Condition(0.1 - tmpFavoriseur, p_Relative);
        // plus de chances d'êtres ouvrier sur les mondes ruches et forges
        Planete::AjouterModifProbaSiMondeForge(m_ConditionSelecteurProba, 0.8);
        Planete::AjouterModifProbaSiMondeRuche(m_ConditionSelecteurProba, 0.5);
        m_Conditions.push_back( Planete::AjouterConditionSiPasMondeFeral() );
    }break;
    case 11 : {
        m_Nom = Metier::CHASSEUR_CUEILLEUR_NOMADE;
        m_ConditionSelecteurProba = new Condition(0.5 - tmpFavoriseur, p_Relative);
        // uniquement sur les mondes férals
        m_Conditions.push_back( Planete::AjouterConditionSiMondeFeral() );
    }break;
    case 12 : {
        m_Nom = Metier::MINEUR;
        m_ConditionSelecteurProba = new Condition(0.005 - tmpFavoriseur, p_Relative);
        Planete::AjouterModifProbaSiMondeMinier(m_ConditionSelecteurProba, 3.0);
    }break;
    case 13 : {
        m_Nom = Metier::TECHNOPRETRE;
        m_Image = ":/images/metier/Technopretre.jpg";
        m_ConditionSelecteurProba = new Condition(0.0001 + tmpFavoriseur, p_Relative);
        m_ConditionSelecteurProba = Planete::AjouterModifProbaSiMondeForge(m_ConditionSelecteurProba, 0.01);
        m_CallbackDisplay = [] {
            QString division = AdeptusMechanicus::DeterminerDivisionAleatoire();
            ExecHistoire::GetEffetActuel()->m_Texte = "Vous êtes maintenant un technoprêtre au service de l'Omnimessie."
                     "\\n vous êtes affecté à votre division et êtes maintenant " + division + ".";

            Humain::GetHumainJoue()->SetValeurACaracId(AdeptusMechanicus::C_DIVISION, division);
        };
    }break;
    }

    if ( m_Description == "" ) {
        m_Description = "Vous êtes maintenant " +
                        m_Nom;
        m_Description += ".";
    }
    m_ModificateursCaracs[C_METIER] = m_Nom;

    m_Conditions.push_back(Metier::AjouterConditionSiAPasMetier());

    if ( m_ConditionSelecteurProba!= nullptr) {
        // si on a moins de 15 ans la proba de s'en voir affecter un est très faible :
        // mais affectation de métier plus rapide sur monde féodal :
        m_ConditionSelecteurProba->AjouterModifProba(-2.3, {new Condition(GenVieHumain::AGE, "120", Comparateur::c_Inferieur)});
        m_ConditionSelecteurProba->AjouterModifProba(-2.3,
            {new Condition(GenVieHumain::AGE, "180", Comparateur::c_Inferieur),
             new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FEODAL, Comparateur::c_Different)
                                       });
    }

    METIERS[m_Nom] = this;
}


QList<QString> Metier::METIERS_INTEGRES = {Metier::ARBITES, Metier::INQUISITEUR}; //  métiers où la criminalité est extrêmement faible

Condition* Metier::AjouterConditionSiAMetier()
{
    Condition* cond = new Condition(Metier::C_METIER, "", Comparateur::c_Different);
    return cond;
}

Condition* Metier::AjouterConditionSiAPasMetier()
{
    Condition* cond = new Condition(Metier::C_METIER, "", Comparateur::c_Egal);
    return cond;
}

Condition* Metier::AjouterModifProbaSiAMetierIntegre(Condition* cond, double poidsProba)
{
    for ( int i = 0 ; i < Metier::METIERS_INTEGRES.length(); ++i) {
        cond->AjouterModifProba(poidsProba,
            { new Condition(Metier::C_METIER, Metier::METIERS_INTEGRES[i], Comparateur::c_Egal) });
    }
    return cond;
}
