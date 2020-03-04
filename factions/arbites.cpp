#include "arbites.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "warp/voyage.h"
#include "metier.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"
#include "texte/jourapresjour.h"
#include "socio_eco/economieevt.h"
#include "factions/ministorum.h"

QString Arbites::C_GRADE = "Grade";
QString Arbites::C_AFFECTATION = "Affectation";
// grades
QString Arbites::SENIOR = "Senior";
QString Arbites::JUGE_ARBITES = "Juge"; //  => inateignable pour l'instant
QString Arbites::PREVOT_MARECHAL = "Prévôt maréchal"; // chef de tout l'adeptus => innateignable pour l'instant

QString Arbites::ACOLYTE_INQUISITEUR = "Acolyte";
QString Arbites::VERISPEX = "Vérispex";
QString Arbites::CHATISSEUR = "Chatisseur";
QString Arbites::DETECTIVE = "Détective";
QString Arbites::CHAPELAIN = "Chapelain";

Arbites::Arbites(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "grade de juge";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Grâce à votre carrière exemplaire vous avez été promu juge de l'Arbites. "
                "C'est une promotion glorieuse entre toutes, vous êtes maintenant une des personnes les plus puissantes de la planète.";
        m_ModificateursCaracs[Arbites::C_GRADE] = Arbites::JUGE_ARBITES;
        m_Conditions.push_back(EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(10));
        m_Conditions.push_back(make_shared<Condition>(Arbites::C_GRADE, Arbites::SENIOR, Comparateur::c_Egal));

    }break;
    case 1 : {
        m_Nom = "affecté au service d'un inquisiteur";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Vos compétences ont attiré l'attention d'un inquisiteur qui vous réquisitionne à son service comme acolyte.";
        m_ModificateursCaracs[Arbites::C_AFFECTATION] = Arbites::ACOLYTE_INQUISITEUR;
        m_Conditions.push_back(EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(2));

    }break;
    case 2 : {
        m_Nom = "carrière avance au service de inquisiteur";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Travailer pour l'inquisition vous ouvre de nombreuses portes. Votre carrière progresse.";
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = 1;
        m_Conditions.push_back(make_shared<Condition>(Arbites::C_AFFECTATION,Arbites::ACOLYTE_INQUISITEUR, Comparateur::c_Egal ));

    }break;
    case 3 : {
        m_Nom = "Verispex technicians";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Votre intelligence et votre sens de la méthode sont remarqués au point de vous voir promu parmi les techniciens Verispex."
                "Vous serez chargé d'analyser les preuves trouvées sur les lieux de crime de manière scientifique.";
        m_ModificateursCaracs[Arbites::C_AFFECTATION] = Arbites::VERISPEX;
        m_Conditions.push_back(EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(3));
        m_Conditions.push_back(Arbites::AjouterConditionSiPasAffectation());

    }break;
    case 4 : {
        m_Nom = "Châtisseur";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Votre capacité de persuasion, votre absence de pitié et surtout votre implacabilité ont été remarquées."
                " Vous avez été choisi pour devenir châtisseur, chargé des brutaux interrogatoires de suspects dans la forteresse.";
        m_ModificateursCaracs[Arbites::C_AFFECTATION] = Arbites::CHATISSEUR;
        m_Image = ":/images/crime/Chastener.jpg";
        m_Conditions.push_back(EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(3));
        m_Conditions.push_back(Arbites::AjouterConditionSiPasAffectation());

    }break;
    case 5 : {
        m_Nom = "grade " + Arbites::SENIOR;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Votre compétence et votre ancienneté vous font monter au grade d'arbitrator senior.";
        m_ModificateursCaracs[Arbites::C_GRADE] = Arbites::SENIOR;
        m_Conditions.push_back(EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(3));
        m_Conditions.push_back(make_shared<Condition>(Arbites::C_GRADE, "", Comparateur::c_Egal));

    }break;
    case 6 : {
        m_Nom = Arbites::DETECTIVE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Votre capacité de persuasion et d'analyse ont été remarquées."
                " Vous avez été choisi pour devenir détective, chargé des investigations dans la ruche.";
        m_ModificateursCaracs[Arbites::C_AFFECTATION] = Arbites::DETECTIVE;
        m_Conditions.push_back(EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(3));
        m_Conditions.push_back(Arbites::AjouterConditionSiPasAffectation());

    }break;
    case 7 : {
        m_Nom = Arbites::CHAPELAIN;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Votre foi en l'empereur alliée à votre charisme vous ont qualifié pour devenir chapelain de la division."
                " Vous devrez entretenir la foi et l'incorruptibilité des arbitrators de votre division.";
        m_ModificateursCaracs[Arbites::C_AFFECTATION] = Arbites::CHAPELAIN;
        m_Conditions.push_back(EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(1));
        m_Conditions.push_back(MinistorumEvts::AjouterConditionSiNiveauFoiSuperieurA(4));
        m_Conditions.push_back(Arbites::AjouterConditionSiPasAffectation());

    }break;
    }
}

std::shared_ptr<Condition> Arbites::AjouterConditionSiPasAffectation()
{
    return make_shared<Condition>(Arbites::C_AFFECTATION, "", Comparateur::c_Egal);
}

void Arbites::RafraichirPhrases()
{
    Humain* humain = Humain::GetHumainJoue();
    QString affectation = humain->GetValeurCarac(Arbites::C_AFFECTATION);
    QString grade = humain->GetValeurCarac(Arbites::C_GRADE);
    if ( affectation == "") {
        JourApresJour::PHRASES.push_back(
            Phrase(
                "Encore une patrouille tranquille autour de la fortresse de circonscription.",
                ":/images/metier/Arbite_aboard_vessel.jpg"
                ));
    }
    if ( grade == Arbites::SENIOR) {
        JourApresJour::PHRASES.push_back(
            Phrase(
                "Un travail difficile requérant des troupes que vous n'avez pas vous oblige à avoir recours à des chasseurs de primes locaux.",
                ":/images/crime/gang.PNG"
                ));
    }
    JourApresJour::PHRASES.push_back(
        Phrase(
            "Rien de particulier. Juste quelques coups de matraque énergétique pour calmer les délinquants des environs.",
            ":/images/metier/Female_Arbiter_2.jpg"
            ));
    JourApresJour::PHRASES.push_back(
        Phrase(
            "Il y a une manifestation violente à réprimer. Vous enfilez votre tenue anti émeute.",
            ":/images/crime/Arbitrator_bouclier.jpg"
            ));
    JourApresJour::PHRASES.push_back(
        Phrase("Vous passez un temps infini à étudier le livre des jugements pour rendre votre verdict." ));
    JourApresJour::PHRASES.push_back(
        Phrase("Vous ajoutez des articles au grand livre des jugements au nom de l'empereur." ));
}
