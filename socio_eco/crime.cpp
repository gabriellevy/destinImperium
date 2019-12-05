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
#include "pbsante.h"

int Crime::COMPTEUR = 0;

// caracs :
QString Crime::C_CRIMINEL = "Est criminel";
//valeurs de criminel : ("" signifie innocent). Note : êre jugé innocent même si n est coupable remet en ""
QString Crime::DELINQUANT = "Délinquant";
QString Crime::CRIMINEL = "Criminel";
// valeurs de GenVieHumain::C_LIBERTE :
QString Crime::CAPTURE_POLICE = "Capturé par la police";
QString Crime::CAPTURE_ARBITES = "Capturé par l'a police'Adeptus Arbites";

Crime::Crime()
{
    double tmp_Modificateur = 0.0; //pour les tests (doit être à 0 en prod)
    switch (Crime::COMPTEUR) {
    case 0 : {
        m_Nom = Crime::DELINQUANT;
        m_ConditionSelecteurProba = new Condition(0.01 + tmp_Modificateur, p_Relative);
        m_Description = "Vous vous mettez à voler à droite à gauche pour survivre";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  "",
                                  Comparateur::c_Egal));
        m_Conditions.push_back(
                    new Condition(ClasseSociale::C_CLASSE_SOCIALE,
                                  ClasseSociale::MISERABLES,
                                  Comparateur::c_Egal));
        m_Conditions = Crime::AjouterConditionSiLibre(m_Conditions);
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::DELINQUANT;

    }break;
    case 1 : {
        m_Nom = Crime::CRIMINEL;
        m_ConditionSelecteurProba = new Condition(0.0001 + tmp_Modificateur, p_Relative);
        m_Conditions = Crime::AjouterConditionSiLibre(m_Conditions);
        m_Description = "Vos perversions vous poussent à devenir un violeur de plus en plus dépravé.";
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;

    }break;
    case 2 : {
        m_Nom = Crime::CRIMINEL;
        m_ConditionSelecteurProba = new Condition(0.0001 + tmp_Modificateur, p_Relative);
        m_Description = "Votre soif de richesse fait de vous un criminel de plus en plus violent.";
        m_Conditions = Crime::AjouterConditionSiLibre(m_Conditions);
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;

    }break;
    case 3 : {
        m_Nom = Crime::CAPTURE_POLICE;
        m_ConditionSelecteurProba = new Condition(0.005 + tmp_Modificateur, p_Relative);
        m_Description = "Vous avez été capturé par la police pour vos méfaits.";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  "",
                                  Comparateur::c_Different));
        m_Conditions = Crime::AjouterConditionSiLibre(m_Conditions);
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_POLICE;

    }break;
    case 4 : {
        m_Nom = Crime::CAPTURE_ARBITES;
        m_ConditionSelecteurProba = new Condition(0.001 + tmp_Modificateur, p_Relative);
        m_Description = "Vous avez été capturé par l'Adeptus Arbites pour vos méfaits.";
        m_Conditions.push_back(
                    new Condition(Crime::C_CRIMINEL,
                                  Crime::CRIMINEL,
                                  Comparateur::c_Egal));
        m_Conditions = Crime::AjouterConditionSiLibre(m_Conditions);
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_ARBITES;

    }break;
    case 5 : {
        m_Nom = "Exécuté par un arbitrator";
        m_ConditionSelecteurProba = new Condition(0.05 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes jugé et condamné à mort pour vos crimes. La sentence est exécutée immédiatement par le juge Arbitrator.";
        m_Image = ":/images/metier/juge.jpg";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_ARBITES,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[PbSante::SANTE] = PbSante::MORT;

    }break;
    case 6 : {
        m_Nom = "Exécuté par la justice";
        m_ConditionSelecteurProba = new Condition(0.01 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes jugé et condamné à mort pour vos crimes. La sentence est exécutée le mois suivant.";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_POLICE,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[PbSante::SANTE] = PbSante::MORT;

    }break;
    case 7 : {
        m_Nom = "Transformé en serviteur";
        m_ConditionSelecteurProba = new Condition(0.01 + tmp_Modificateur, p_Relative);
        m_Description = "Vous êtes jugé et condamné à être transformé en serviteur décérébré jusqu'à la fin de vos jours. Vous êtes lobotomisé le mois suivant...";
        m_Image = ":/images/metier/serviteur.jpg";
        m_Conditions.push_back(
                    new Condition(GenVieHumain::C_LIBERTE,
                                  Crime::CAPTURE_POLICE,
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[PbSante::SANTE] = PbSante::MORT;

    }break;
    }

    Crime::COMPTEUR++;
}

QList<Condition*> Crime::AjouterConditionSiLibre(QList<Condition*> conditions)
{
    conditions.push_back(new Condition(GenVieHumain::C_LIBERTE,
                        "", Comparateur::c_Egal));
    return conditions;
}

QList<Condition*> Crime::AjouterConditionSiNonLibre(QList<Condition*> conditions)
{
    conditions.push_back(new Condition(GenVieHumain::C_LIBERTE,
                        "", Comparateur::c_Different));
    return conditions;
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
