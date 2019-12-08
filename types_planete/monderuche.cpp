#include "monderuche.h"
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
#include "../socio_eco/classesociale.h"
#include "../actions/combat.h"
#include "humanite/pbsante.h"
#include "../destinLib/gestionnairecarac.h"
#include "humain.h"

int MondeRuche::COMPTEUR = 0;

MondeRuche::MondeRuche()
{
    switch (MondeRuche::COMPTEUR) {
    case 0 : {
        m_Nom = "voyage_train_des_cendres";
        // pas pour les très pauvres :
        m_Conditions = { new Condition(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::MISERABLES, Comparateur::c_Different)                       };
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative); // 0.01
        m_Description = "Vous prenez ne train des cendres pour rendre une visite dans la ruche " +
                MondeRuche::GetNomRucheAleatoire() +
                ".";
        m_Image = ":/images/ruche/Ruche.png";
        m_CallbackDisplay = [] {
            // selon les proba il peut se passer plus de choses durant ce voyage :
            if ( Aleatoire::GetAl()->EntierInferieurA(10) == 0) {
                // attaque du train :
                Effet* effetActuel = ExecHistoire::GetEffetActuel();
                effetActuel->m_Texte += "\nLe train est attaqué par des rebelles nomades mutants !";
                int resCombat = Combat::JouerCombat(3);
                if ( resCombat < -2) {
                    effetActuel->m_Texte += "\nVous êtes tué dans l'attaque";
                    Humain::GetHumainJoue()->SetValeurACaracId(PbSante::C_SANTE, PbSante::MORT);
                } else if ( resCombat == -1) {
                    effetActuel->m_Texte += "\nVous êtes capturé par les infâmes mutants !";
                    Humain::GetHumainJoue()->SetValeurACaracId(GenVieHumain::C_LIBERTE, "Capturé par les mutants rebelles des sables.");
                } else if ( resCombat < 2) {
                    effetActuel->m_Texte += "\nLes pillards volent une bonne partie de la cargaison puis s'enfuient. Vous êtes sauf.";
                } else {
                    effetActuel->m_Texte += "\nVous vous défendez violemment et parvenez à tuer plusieurs pillards avant qu'ils ne prennent le fuite. Tout le train vous acclame en héros.";
                }
            }

        };

    }break;
    case 1 : {
        m_Nom = "réaffectation planète";
        // pas pour les très riches :
        m_Conditions = { new Condition(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::MAITRES, Comparateur::c_Different)};
        m_ConditionSelecteurProba = new Condition(0.0001, p_Relative);
        m_Description = "Vous avez été choisis pour aller peupler une distante planète récemment découverte. Vous avez un mois pour préparer vos affaires.";
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = Voyage::ALEATOIRE;

    }break;
    }

    // tous ces événements ne peuvent se produire que sur un monde ruche :
    m_Conditions.push_back(
                new Condition(Planete::C_TYPE_PLANETE,
                              Planete::PLANETE_RUCHE,
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


void MondeRuche::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
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


QList<QString> MondeRuche::RUCHES = {
    "Tempestora", "Death Mire", "Volcanus", "Infernus", "Hades", "Acheron", "Helsreach", "Tartarus" // ruches armageddon
};
QString MondeRuche::GetNomRucheAleatoire()
{
    return MondeRuche::RUCHES[Aleatoire::GetAl()->EntierInferieurA(MondeRuche::RUCHES.length())];
}

