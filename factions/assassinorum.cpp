#include "assassinorum.h"
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

int Assassinorum::COMPTEUR = 0;

// caracs
QString Assassinorum::C_TEMPLE = "Temple";
// valeurs de C_TEMPLE
QString Assassinorum::EVERSOR = "Eversor";
QString Assassinorum::CALLIDUS = "Callidus";
QString Assassinorum::VINDICARE = "Vindicare";
QString Assassinorum::CULEXUS = "Culexus";

Assassinorum::Assassinorum()
{
    switch (Assassinorum::COMPTEUR) {
    case 0 : {
        m_Nom = "youpi Assassinorum";
        m_ConditionSelecteurProba = new Condition(0.0, p_Relative);
        m_Description = "Tenté par les dieux noirs, vous rejoignez une secte du chaos.";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        /*m_CallbackDisplay = [] {

        };*/

    }break;
    }

    Assassinorum::COMPTEUR++;

}


Effet* Assassinorum::GenererEffet(GenEvt* genEvt)
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


void Assassinorum::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Assassinorum* evt = new Assassinorum();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new Assassinorum();
    }
}
