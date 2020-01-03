#include "astronomica.h"
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
#include "../destinLib/execeffet.h"
#include "socio_eco/economieevt.h"
#include "humain.h"
#include "texte/jourapresjour.h"
#include "humanite/pbsante.h"
#include "warp/psyker.h"

// caracs
QString Astronomica::C_POSTE = "Poste";
// VALEURS DE C_POSTE
QString Astronomica::INSTRUCTEUR = "Instructeur";
QString Astronomica::ACOLYTE = "Acolyte";
QString Astronomica::ELU = "Élu";

Astronomica::Astronomica(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{

    switch (indexEvt) {
    case 0 : {
        m_Nom = "Sacrifice Astronomica";
        m_ConditionSelecteurProba = new Condition(0.05, p_Relative);
        m_Description = "Vous avez donné tout votre potentiel et fait de grands efforts pour aider l'empereur mais la tâche est insurmontable. "
                "Vous sentez votre âme se dissoudre dans le trône d'or et dans la lumière aveuglante de l'astronomicon";
        m_Image = ":/images/warp/god-emperor.jpg";
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_Conditions.push_back(new Condition(Astronomica::C_POSTE, Astronomica::ELU, Comparateur::c_Egal));
        m_Conditions.push_back(Metier::AjouterConditionSiACeMetier(Metier::ASTRONOMICA));
    }break;
    case 1 : {
        m_Nom = "FormationAcolyte Astronomica";
        m_ConditionSelecteurProba = new Condition(0.4, p_Relative);
        m_Description = "Vous êtes initié par les instructeurs au fonctionnement et aux mystères de l'Astronomican."
                "Vous êtes maintenant un acolyte";
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_Conditions.push_back(Metier::AjouterConditionSiACeMetier(Metier::ASTRONOMICA));
        // sans poste
        m_Conditions.push_back(new Condition(Astronomica::C_POSTE, "", Comparateur::c_Egal));

        m_ModificateursCaracs[Astronomica::C_POSTE] = Astronomica::ACOLYTE;
    }break;
    case 2 : {
        m_Nom = "Choisi pour le sacrifice Astronomica";
        m_ConditionSelecteurProba = new Condition(0.02, p_Relative);
        m_Description = "Vos études touchent à leur fin. Vous vous êtes montré digne de rejoindre la chambre sacrée de l'Astronomican dans l'Himalaya."
                " Vous êtes un élu.";
        m_Conditions.push_back(Psyker::AjouterConditionSiPsyker());
        m_Conditions.push_back(Metier::AjouterConditionSiACeMetier(Metier::ASTRONOMICA));
        m_Conditions.push_back(new Condition(Astronomica::C_POSTE, Astronomica::ACOLYTE, Comparateur::c_Egal));

        m_ModificateursCaracs[Astronomica::C_POSTE] = Astronomica::ELU;
    }break;
    }
}

void Astronomica::RafraichirPhrasesAstronomica(QString typePlanete, QString classeSociale)
{
    Humain* hum = Humain::GetHumainJoue();
    if ( hum->GetValeurCarac(Astronomica::C_POSTE) == Astronomica::ACOLYTE)
    {
        JourApresJour::PHRASES.push_back(Phrase(
            "Vous êtes initié au mystères du warp."));
        JourApresJour::PHRASES.push_back(Phrase(
            "Vos connaissances en philosophie progressent."));
    } else if ( hum->GetValeurCarac(Astronomica::C_POSTE) == Astronomica::ELU)
    {
        JourApresJour::PHRASES.push_back(Phrase(
            "Votre âme se consume lentement, au service de l'Astronomican."));
    }
    JourApresJour::PHRASES.push_back(Phrase(
        "Un nouveau contingent de psykers est arrivé. Bénis soient-ils par la lumière sacrée de l'empereur."));
}
