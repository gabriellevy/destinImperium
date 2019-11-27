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
#include "../socio_eco/classesociale.h"


int MondeRuche::COMPTEUR = 0;

MondeRuche::MondeRuche()
{
    switch (MondeRuche::COMPTEUR) {
    case 0 : {
        m_Nom = "repas_bouillie";
        // seulement pour les pauvres :
        m_Conditions = { new Condition(ClasseSociale::ID_CLASSE_SOCIALE, ClasseSociale::MAITRES, Comparateur::c_Different),
                         new Condition(ClasseSociale::ID_CLASSE_SOCIALE, ClasseSociale::INFLUENTS, Comparateur::c_Different)
                       };
        m_ConditionSelecteurProba = new Condition(1, p_Relative);
        m_Description = "Encore une bonne bouillie de déchets organiques recyclés comme repas";
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

    effet->m_Conditions = m_Conditions;

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

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new MondeRuche();
    }
}

