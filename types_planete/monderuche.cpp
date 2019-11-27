#include "monderuche.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "voyage.h"
#include "metier.h"
#include "../destinLib/effet.h"


int MondeRuche::COMPTEUR = 0;

MondeRuche::MondeRuche()
{
    switch (MondeRuche::COMPTEUR) {
    case 0 : {
        m_Nom = "test temp";
        m_Condition = new Condition(0, p_Pure);
        m_Description = "blablabla";
        //Inquisition::AjouterModifProbaSiInquisiteur(m_Condition, 0.1);
        //m_ModificateursCaracs[Inquisition::RANG] = Administratum::GRADE_SCRIBE;

    }break;
    }

    MondeRuche::COMPTEUR++;

}


Effet* MondeRuche::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = nullptr;
    /*if ( m_Nom == Inquisition::ID_AFFECTATION_ORDO) {
        // sélectionneur d'effets
        QVector<NoeudProbable*> noeudsAffectation;
        Ordo::GenererNoeudsAffectation(genEvt, noeudsAffectation);
        effet = genEvt->AjouterEffetSelecteurDEvt(
                    noeudsAffectation,
                    Inquisition::ID_AFFECTATION_ORDO,
                    "",
                    GenVieHumain::EVT_SELECTEUR);
    } else*/ {
        // système de création d'effets de base :
        effet = genEvt->AjouterEffetNarration(
            m_Description,
            m_Image,
            "evt_monde_ruche_" + m_Nom, GenVieHumain::EVT_SELECTEUR);
        effet->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
    }

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }

    return effet;
}


void MondeRuche::GenererNoeudsMondeRuche(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    MondeRuche* evt = new MondeRuche();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new MondeRuche();
    }
}

