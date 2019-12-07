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

int Ministorum::COMPTEUR = 0;

// caracs

Ministorum::Ministorum()
{
    switch (Ministorum::COMPTEUR) {
    case 0 : {
        m_Nom = "";
        m_ConditionSelecteurProba = new Condition(0.0, p_Relative);
        m_Description = "??? Ministorum";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        /*m_CallbackDisplay = [] {

        };*/

    }break;
    }

    Ministorum::COMPTEUR++;
}

Effet* Ministorum::GenererEffet(GenEvt* genEvt)
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

void Ministorum::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Ministorum* evt = new Ministorum();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new Ministorum();
    }
}
