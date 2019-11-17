#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "planet.h"

int Metier::COMPTEUR = 0;

Metier::Metier()
{
    switch (Metier::COMPTEUR) {
    case 0 : {
        m_Nom = "Paysan";
        m_Metier = Paysan;
        m_Condition = new Condition(0.1);
        // plus de chances d'êtres paysans sur les mondes agricoles et médiévaux
        Planete::AjouterModifProbaSiMondeAgricole(m_Condition, 0.8);
        Planete::AjouterModifProbaSiMondeFeodal(m_Condition, 0.6);
    }break;
    case 1 : {
        m_Nom = "Fonctionnaire de l'Administratum";
        m_Metier = FonctionnaireAdministratum;
        m_Condition = new Condition(0.2);
    }break;
    case 2 : {
        m_Nom = "Noble Chevalier";
        m_Metier = NobleChevalier;
        m_Condition = new Condition(0);
        Planete::AjouterModifProbaSiMondeChevalier(m_Condition, 0.01);
    }break;
    case 3 : {
        m_Nom = "Garde Imperial";
        m_Metier = GardeImperial;
        m_Image = ":/images/metier/garde-imperial.jpg";
        m_Condition = new Condition(0.02);
        // plus de chances de devenir garde sur les mondes férals et médiévaux
        Planete::AjouterModifProbaSiMondeFeodal(m_Condition, 0.2);
        Planete::AjouterModifProbaSiMondeFeral(m_Condition, 0.2);
    }break;
    }

    if ( m_Condition!= nullptr) {
        // si on a un métier les chances qu'on s'en voit affecter un sont très faibles :
        m_Condition->AjouterModifProba(-1.0, {new Condition(GenVieHumain::METIER, "", Comparateur::c_Different)});
        // et si on a moins de 15 ans la proba de s'en voir affecter un est très faible :
        // mais affectation de métier plus rapide sur monde féodal :
        m_Condition->AjouterModifProba(-2.3, {new Condition(GenVieHumain::AGE, "120", Comparateur::c_Inferieur)});
        m_Condition->AjouterModifProba(-2.3,
            {new Condition(GenVieHumain::AGE, "180", Comparateur::c_Inferieur),
             new Condition(GenVieHumain::TYPE_PLANETE, Planete::GetTypeMondeAsStr(MondeFeodal), Comparateur::c_Different)
                                       });
    }

    Metier::COMPTEUR++;
}




void Metier::GenererNoeudsSelectionMetier(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Metier* metier = new Metier();
    while ( metier->m_Nom != "") {
        QString texteAffectation = "Vous êtes maintenant " +
                metier->m_Nom;
        texteAffectation += ".";

        Effet* effetAffectation = genEvt->AjouterEffetNarration(
                    texteAffectation,
                    metier->m_Image,
                    "affectation_metier_" + metier->m_Nom, GenVieHumain::EVT_SELECTEUR);
        effetAffectation->AjouterChangeurDeCarac(GenVieHumain::METIER, metier->m_Nom);
        effetAffectation->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effetAffectation = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effetAffectation);

        Condition* cond = metier->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effetAffectation,
                    cond);

        noeuds.push_back(noeud);

        metier = new Metier();
    }
}

