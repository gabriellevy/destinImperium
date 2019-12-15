#include "ministorum.h"
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

// caracs

Ministorum::Ministorum(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "";
        m_ConditionSelecteurProba = new Condition(0.0, p_Relative);
        m_Description = "??? Ministorum";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        /*m_CallbackDisplay = [] {

        };*/

    }break;
    }
}

