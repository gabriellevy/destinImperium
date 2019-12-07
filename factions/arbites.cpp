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

int Arbites::COMPTEUR = 0;

// grades
QString Arbites::JUGE_ARBITES = "Juge"; //  => inateignable pour l'instant
QString Arbites::PREVOT_MARECHAL = "Prévôt maréchal"; // chef de tout l'adeptus => innateignable pour l'instant

Arbites::Arbites()
{
    switch (Arbites::COMPTEUR) {
    case 0 : {
        m_Nom = "??? Arbites";
        m_ConditionSelecteurProba = new Condition(0.0, p_Relative);
        m_Description = "??? Arbites";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        /*m_CallbackDisplay = [] {

        };*/

    }break;
    }

    Arbites::COMPTEUR++;

}


Effet* Arbites::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = genEvt->AjouterEffetNarration(
            m_Description,
            m_Image,
            "evt_monde_ruche_" + m_Nom, GenVieHumain::EVT_SELECTEUR);
        effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
        effet->m_CallbackDisplay = m_CallbackDisplay;
        effet->m_Conditions = m_Conditions;

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }

    return effet;
}


void Arbites::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Arbites* evt = new Arbites();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new Arbites();
    }
}
