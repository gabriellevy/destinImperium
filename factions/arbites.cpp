#include "arbites.h"
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
#include "humain.h"
#include "texte/jourapresjour.h"

// grades
QString Arbites::JUGE_ARBITES = "Juge"; //  => inateignable pour l'instant
QString Arbites::PREVOT_MARECHAL = "Prévôt maréchal"; // chef de tout l'adeptus => innateignable pour l'instant

Arbites::Arbites(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "??? Arbites";
        m_ConditionSelecteurProba = new Condition(0.0, p_Relative);
        m_Description = "??? Arbites";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        /*m_CallbackDisplay = [] {

        };*/

    }break;
    }
}

void Arbites::RafraichirPhrases()
{
    JourApresJour::PHRASES.push_back(
        Phrase(
            "Encore une patrouille tranquille autour de la fortresse de circonscription.",
            ":/images/metier/Arbite_aboard_vessel.jpg"
            ));
    JourApresJour::PHRASES.push_back(
        Phrase(
            "Rien de particulier. Juste quelques coups de matraque énergétique pour calmer les délinquants des environs.",
            ":/images/metier/Female_Arbiter_2.jpg"
            ));
    JourApresJour::PHRASES.push_back(
        Phrase("Vous passez un temps infini à étudier le livre des jugements pour rendre votre verdict." ));
    JourApresJour::PHRASES.push_back(
        Phrase("Vous ajoutez des articles au grand livre des jugements au nom de l'empereur." ));
}
