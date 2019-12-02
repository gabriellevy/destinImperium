#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "types_planete/planet.h"
#include "voyage.h"

int Metier::COMPTEUR = 0;
QMap<e_Metier, Metier*> Metier::METIERS;

Metier::Metier()
{
    double tmpFavoriseur = 0.0; // valeur servant à tester => à mettre à 0 pour un test final
    switch (Metier::COMPTEUR) {
    case 0 : {
        m_Nom = "Paysan";
        m_Metier = Paysan;
        m_Condition = new Condition(0.1 - tmpFavoriseur, p_Relative);
        // plus de chances d'êtres paysans sur les mondes agricoles et médiévaux
        Planete::AjouterModifProbaSiMondeAgricole(m_Condition, 0.8);
        Planete::AjouterModifProbaSiMondeFeodal(m_Condition, 0.6);
    }break;
    case 1 : {
        m_Nom = "Adepte Administratum";
        m_Metier = AdepteAdministratum;
        m_Image = ":/images/metier/Administratum Adept.png";
        m_Condition = new Condition(0.15 - tmpFavoriseur, p_Relative);
    }break;
    case 2 : {
        m_Nom = "Noble Chevalier";
        m_Metier = NobleChevalier;
        m_Condition = new Condition(0 - tmpFavoriseur, p_Relative);
        Planete::AjouterModifProbaSiMondeChevalier(m_Condition, 0.01);
    }break;
    case 3 : {
        m_Nom = "Garde Imperial";
        m_Metier = GardeImperial;
        m_Image = ":/images/metier/garde-imperial.jpg";
        m_Condition = new Condition(0.02 - tmpFavoriseur, p_Relative);
        // plus de chances de devenir garde sur les mondes férals et médiévaux
        Planete::AjouterModifProbaSiMondeFeodal(m_Condition, 0.2);
        Planete::AjouterModifProbaSiMondeFeral(m_Condition, 0.2);
    }break;
    case 4 : {
        m_Nom = "Arbitrator";
        m_Description = "Agent de l'Adeptus Arbites, l'agence chargée de faire respecter la loi impériale. Vous allez bientôt être affecté à votre planète de garnison.";
        m_Metier = Arbitrator;
        m_Image = ":/images/metier/Arbitrator.jpg";
        m_Condition = new Condition(0.01 - tmpFavoriseur, p_Relative);
        // à peine nommé, un arbitrator est affecté à une nouvelle planète
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = Voyage::ALEATOIRE;
    }break;
    case 5 : {
        m_Nom = "Inquisiteur";
        m_Description = "Agent de l'Inquisition, une organisation secrète chargée de traquer les ennemis de l'imperium.";
        m_Metier = Inquisiteur;
        m_Image = ":/images/metier/inquisiteur.jpg";
        m_Condition = new Condition(0.001 + tmpFavoriseur, p_Relative); // 0.001
        // à peine nommé, un Inquisiteur est affecté à une nouvelle planète
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = Voyage::ALEATOIRE;
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
             new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FEODAL, Comparateur::c_Different)
                                       });
    }

    METIERS[m_Metier] = this;

    Metier::COMPTEUR++;
}


QString Metier::GetMetierAsStr(e_Metier metier)
{
    return Metier::METIERS[metier]->m_Nom;
}


void Metier::GenererNoeudsSelectionMetier(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Metier* metier = new Metier();
    while ( metier->m_Nom != "") {
        QString texteAffectation = "Vous êtes maintenant " +
                metier->m_Nom;
        texteAffectation += ".";
        if ( metier->m_Description != "" )
            texteAffectation += " " + metier->m_Description;

        Effet* effetAffectation = genEvt->AjouterEffetNarration(
                    texteAffectation,
                    metier->m_Image,
                    "affectation_metier_" + metier->m_Nom, GenVieHumain::EVT_SELECTEUR);
        effetAffectation->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effetAffectation = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effetAffectation);

        // modificateurs de carac :
        effetAffectation->AjouterChangeurDeCarac(GenVieHumain::METIER, metier->m_Nom);
        QMapIterator<QString, QString> it(metier->m_ModificateursCaracs);
        while ( it.hasNext()) {
            it.next();
            effetAffectation->AjouterChangeurDeCarac(it.key(), it.value());
        }

        Condition* cond = metier->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effetAffectation,
                    cond);

        noeuds.push_back(noeud);

        metier = new Metier();
    }
}

