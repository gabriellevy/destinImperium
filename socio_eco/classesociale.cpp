#include "classesociale.h"
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
#include "economieevt.h"

ClasseSociale::ClasseSociale(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "promotion classe sociale des pauvres vers moyenne";
        m_ConditionSelecteurProba = new Condition(0.02, p_Relative);
        m_Description = "Vous avez amassé une telle fortune que vous parvenez à vous hisser dans la classe moyenne.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::CLASSE_MOYENNE;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        m_Conditions.push_back(new Condition(EconomieEvt::C_NIVEAU_ECONOMIQUE, "10", Comparateur::c_SuperieurEgal));
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::PAUVRES));

    }break;
    case 1 : {
        m_Nom = "promotion classe sociale des moyens vers influents";
        m_ConditionSelecteurProba = new Condition(0.02, p_Relative);
        m_Description = "Vous avez amassé une telle fortune et noué tellement de contacts avec les classes dirigeants "
                "que vous parvenez à vous hisser parmi les maisons nobles de la ruche.";
        m_Image = ":/images/socio_eco/FemmeNobleApparat.jpg";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::INFLUENTS;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        m_Conditions.push_back(new Condition(EconomieEvt::C_NIVEAU_ECONOMIQUE, "10", Comparateur::c_SuperieurEgal));
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::CLASSE_MOYENNE));

    }break;
    case 2 : {
        m_Nom = "descente classe sociale des pauvres vers misérables";
        m_ConditionSelecteurProba = new Condition(0.02, p_Relative);
        m_Description = "Vous avez accumulé tant d'échecs que vous vous retrouvez dans la misèr la plus totale.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[Metier::C_METIER] = "";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::MISERABLES;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        m_Conditions.push_back(new Condition(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-10", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::PAUVRES));

    }break;
    case 3 : {
        m_Nom = "descente classe sociale des moyens vers pauvres";
        m_ConditionSelecteurProba = new Condition(0.02, p_Relative);
        m_Description = "Vous avez accumulé tant d'échecs que vous vous retrouvez licencié et projeté parmi les classes pauvres.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[Metier::C_METIER] = "";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::PAUVRES;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        m_Conditions.push_back(new Condition(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-10", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::CLASSE_MOYENNE));

    }break;
    case 4 : {
        m_Nom = "descente classe sociale des influents vers moyens";
        m_ConditionSelecteurProba = new Condition(0.02, p_Relative);
        m_Description = "Vous avez accumulé tant d'échecs que vous vous retrouvez expulsé de votre maison noble et déshonoré. "
                "Vous allez devoir maintenant survivre parmi les classes inférieures.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[Metier::C_METIER] = "";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::CLASSE_MOYENNE;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        m_Conditions.push_back(new Condition(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-10", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::INFLUENTS));

    }break;
    }
}

Condition* ClasseSociale::AjouterConditionSiCetteClasseSociale(QString classeSociale)
{
    Condition* cond = new Condition(ClasseSociale::C_CLASSE_SOCIALE, classeSociale, Comparateur::c_Egal);
    return cond;
}

QString ClasseSociale::C_CLASSE_SOCIALE = "Classe sociale";


QString ClasseSociale::GetClasseSocialeAleatoire(QString typeMonde)
{
    double proba = Aleatoire::GetAl()->Entre0Et1();
    if (typeMonde == Planete::PLANETE_RUCHE) {
        if ( proba < 0.01)
            return ClasseSociale::MISERABLES;
        else if (proba < 0.7)
            return ClasseSociale::PAUVRES;
        else if ( proba < 0.98)
            return ClasseSociale::CLASSE_MOYENNE;
        else if ( proba < 0.999)
            return ClasseSociale::INFLUENTS;
        else {
            return ClasseSociale::MAITRES;
        }
    } else if ( typeMonde == Planete::PLANETE_MINIERE) {
        // essentiellement des escalves et des travaiolleurs pénaux
        if ( proba < 0.9)
            return ClasseSociale::MISERABLES;
        else if (proba < 0.98)
            return ClasseSociale::PAUVRES;
        else if ( proba < 0.99)
            return ClasseSociale::CLASSE_MOYENNE;
        else if ( proba < 0.9999)
            return ClasseSociale::INFLUENTS;
        else {
            return ClasseSociale::MAITRES;
        }
    } else {
        if ( proba < 0.01)
            return ClasseSociale::MISERABLES;
        else if (proba < 0.7)
            return ClasseSociale::PAUVRES;
        else if ( proba < 0.98)
            return ClasseSociale::CLASSE_MOYENNE;
        else if ( proba < 0.999)
            return ClasseSociale::INFLUENTS;
        else {
            return ClasseSociale::MAITRES;
        }
    }
}


QString ClasseSociale::MISERABLES = "Misérable";
QString ClasseSociale::PAUVRES = "Pauvre";
QString ClasseSociale::CLASSE_MOYENNE = "Classe moyenne";
QString ClasseSociale::INFLUENTS = "Classe dominante";
QString ClasseSociale::MAITRES = "Classe dirigeante";
