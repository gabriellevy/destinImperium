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
