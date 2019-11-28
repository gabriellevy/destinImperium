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
#include "../destinLib/aleatoire.h"
#include "../socio_eco/classesociale.h"
#include "../actions/combat.h"
#include "pbsante.h"
#include "../destinLib/gestionnairecarac.h"

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
    case 1 : {
        m_Nom = "voyage_train_des_cendres";
        // pas pour les très pauvres :
        m_Conditions = { new Condition(ClasseSociale::ID_CLASSE_SOCIALE, ClasseSociale::MISERABLES, Comparateur::c_Different)                       };
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative); // 0.01
        m_Description = "Vous prenez ne train des cendres pour rendre une visite dans une ruche voisine.";
        m_CallbackDisplay = [] {
            // selon les proba il peut se passer plus de choses durant ce voyage :
            if ( Aleatoire::GetAl()->EntierInferieurA(10) == 0) {
                // attaque du train :
                Effet* effetActuel = ExecHistoire::GetEffetActuel();
                effetActuel->m_Texte += "\nLe train est attaqué par des rebelles nomades mutants !";
                int resCombat = Combat::JouerCombat(3);
                if ( resCombat < -2) {
                    effetActuel->m_Texte += "\nVous êtes tué dans l'attaque";
                    GestionnaireCarac::SetValeurACaracId(PbSante::SANTE, PbSante::MORT);
                } else if ( resCombat == -1) {
                    effetActuel->m_Texte += "\nVous êtes capturé par les infâmes mutants !";
                    // TODO MATHIEU : oula c'est dur là ! que faire ?
                } else if ( resCombat < 2) {
                    effetActuel->m_Texte += "\nLes pillards volent une bonne partie de la cargaison puis s'enfuient. Vous êtes sauf.";
                } else {
                    effetActuel->m_Texte += "\nVous vous défendez violemment et parvenez à tuer plusieurs pillards avant qu'ils ne prennent le fuite. Tout le train vous acclame en héros.";
                }
            }

        };

    }break;
    }

    // tous ces événements ne peuvent se produire que sur un monde ruche :
    m_Conditions.push_back(
                new Condition(Planete::C_TYPE_PLANETE,
                              Planete::GetTypeMondeAsStr(TypePlanete::MondeRuche),
                              Comparateur::c_Egal));

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
        effet->m_CallbackDisplay = m_CallbackDisplay;
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

