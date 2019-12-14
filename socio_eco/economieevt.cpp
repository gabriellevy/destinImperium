#include "economieevt.h"
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

int EconomieEvt::COMPTEUR = 0;


QString EconomieEvt::C_NIVEAU_ECONOMIQUE = "Niveau économique";

EconomieEvt::EconomieEvt()
{
    switch (EconomieEvt::COMPTEUR) {
    case 0 : {
        m_Nom = "bon travail";
        m_ConditionSelecteurProba = new Condition(0.03, p_Relative);
        m_Description = "Votre excellent travail est apprécié de tous.";
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = 1;
        m_Conditions.push_back(AjouterConditionSiAMetier());

    }break;
    case 1 : {
        m_Nom = "mauvais travail";
        m_ConditionSelecteurProba = new Condition(0.02, p_Relative);
        m_Description = "Vos nombreuses gaffes au travail mettent votre carrière en danger.";
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = -1;
        m_Conditions.push_back(AjouterConditionSiAMetier());

    }break;
    }

    EconomieEvt::COMPTEUR++;

}


Condition* EconomieEvt::AjouterConditionSiAMetier()
{
    Condition* cond = new Condition(Metier::C_METIER, "", Comparateur::c_Different);
    return cond;
}


Effet* EconomieEvt::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = nullptr;

    // système de création d'effets de base :
    effet = genEvt->AjouterEffetNarration(
        m_Description,
        m_Image,
        "evt_monde_ruche_" + m_Nom, GenVieHumain::EVT_SELECTEUR);
    effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
    effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
    effet->m_Conditions = m_Conditions;

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }
    QMapIterator<QString, int> itInc(m_IncrementeursCaracs);
    while ( itInc.hasNext()) {
        itInc.next();
        effet->AjouterAjouteurACarac(itInc.key(), itInc.value());
    }

    return effet;
}


void EconomieEvt::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    EconomieEvt* evt = new EconomieEvt();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new EconomieEvt();
    }
}


