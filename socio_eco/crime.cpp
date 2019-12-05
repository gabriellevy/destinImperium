#include "crime.h"
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
#include "classesociale.h"

int Crime::COMPTEUR = 0;

// caracs :
QString Crime::C_CRIMINEL = "Est criminel";
//valeurs de criminel : ("" signifie innocent). Note : êre jugé innocent même si n est coupable remet en ""
QString Crime::DELINQUANT = "Délinquant";
QString Crime::CRIMINEL = "Criminel";

Crime::Crime()
{
    switch (Crime::COMPTEUR) {
    case 0 : {
        m_Nom = Crime::DELINQUANT;
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Vous vous mettez à voler à droite à gauche pour survivre";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  "",
                                  Comparateur::c_Egal));
        m_Conditions.push_back(
                    new Condition(ClasseSociale::C_CLASSE_SOCIALE,
                                  ClasseSociale::MISERABLES,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::DELINQUANT;

    }break;
    case 1 : {
        m_Nom = Crime::CRIMINEL;
        m_ConditionSelecteurProba = new Condition(0.0001, p_Relative);
        m_Description = "Vos perversions vous poussent à devenir un violeur de plus en plus dépravé.";
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;

    }break;
    case 2 : {
        m_Nom = Crime::CRIMINEL;
        m_ConditionSelecteurProba = new Condition(0.0001, p_Relative);
        m_Description = "Votre soif de richesse fait de vous un criminel de plus en plus violent.";
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;

    }break;
    }

    Crime::COMPTEUR++;
}


Effet* Crime::GenererEffet(GenEvt* genEvt)
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

    return effet;
}


void Crime::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Crime* evt = new Crime();
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new Crime();
    }
}
