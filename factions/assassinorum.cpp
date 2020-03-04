#include "assassinorum.h"
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

// caracs
QString Assassinorum::C_TEMPLE = "Temple";
// valeurs de C_TEMPLE
QString Assassinorum::EVERSOR = "Eversor";
QString Assassinorum::CALLIDUS = "Callidus";
QString Assassinorum::VINDICARE = "Vindicare";
QString Assassinorum::CULEXUS = "Culexus";

Assassinorum::Assassinorum(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "youpi Assassinorum";
        m_ConditionSelecteurProba = make_shared<Condition>(0.0, p_Relative);
        m_Description = "??? Assassinorum";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        /*m_CallbackDisplay = [] {

        };*/

    }break;
    }
}

QString Assassinorum::DeterminerTempleAleatoire()
{
    double proba = Aleatoire::GetAl()->Entre0Et1();

    if ( proba < 0.25) {
        return Assassinorum::EVERSOR;
    }
    else if ( proba < 0.5) {
        return Assassinorum::CULEXUS;
    }
    if ( proba < 0.75) {
        return Assassinorum::CALLIDUS;
    }
    return Assassinorum::VINDICARE;
}
