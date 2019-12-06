#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "types_planete/planet.h"
#include "warp/voyage.h"

int Metier::COMPTEUR = 0;

QString Metier::C_METIER = "Métier";

QString Metier::PAYSAN = "Paysan";
QString Metier::GARDE_IMPERIAL = "Garde Imperial";
QString Metier::ADEPTE_ADMINISTRATUM = "Adepte Administratum";
QString Metier::ARBITES = "Arbitrator"; // Adeptus Arbites
// mondes chevaliers :
QString Metier::NOBLE_CHEVALIER = "Noble Chevalier";
QString Metier::INQUISITEUR = "Inquisiteur";
QString Metier::SERVANT_ADEPTUS_ASTRONOMICA = "Servant Adeptus Astronomica";

QMap<QString, Metier*> Metier::METIERS;

Metier::Metier()
{
    double tmpFavoriseur = 0.0; // valeur servant à tester => à mettre à 0 pour un test final
    switch (Metier::COMPTEUR) {
    case 0 : {
        m_Nom = Metier::PAYSAN;
        m_ConditionSelecteurProba = new Condition(0.1 - tmpFavoriseur, p_Relative);
        // plus de chances d'êtres paysans sur les mondes agricoles et médiévaux
        Planete::AjouterModifProbaSiMondeAgricole(m_ConditionSelecteurProba, 0.8);
        Planete::AjouterModifProbaSiMondeFeodal(m_ConditionSelecteurProba, 0.6);
    }break;
    case 1 : {
        m_Nom = Metier::ADEPTE_ADMINISTRATUM;
        m_Image = ":/images/metier/Administratum Adept.png";
        m_ConditionSelecteurProba = new Condition(0.15 - tmpFavoriseur, p_Relative);
    }break;
    case 2 : {
        m_Nom = Metier::NOBLE_CHEVALIER;
        m_ConditionSelecteurProba = new Condition(0 - tmpFavoriseur, p_Relative);
        Planete::AjouterModifProbaSiMondeChevalier(m_ConditionSelecteurProba, 0.01);
    }break;
    case 3 : {
        m_Nom = Metier::GARDE_IMPERIAL;
        m_Image = ":/images/metier/garde-imperial.jpg";
        m_ConditionSelecteurProba = new Condition(0.02 - tmpFavoriseur, p_Relative);
        // plus de chances de devenir garde sur les mondes férals et médiévaux
        Planete::AjouterModifProbaSiMondeFeodal(m_ConditionSelecteurProba, 0.2);
        Planete::AjouterModifProbaSiMondeFeral(m_ConditionSelecteurProba, 0.2);
    }break;
    case 4 : {
        m_Nom = Metier::ARBITES;
        m_Description = "Agent de l'Adeptus Arbites, l'agence chargée de faire respecter la loi impériale. Vous allez bientôt être affecté à votre planète de garnison.";
        m_Image = ":/images/metier/Arbitrator.jpg";
        m_ConditionSelecteurProba = new Condition(0.01 + tmpFavoriseur, p_Relative);
        // à peine nommé, un arbitrator est affecté à une nouvelle planète
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = Voyage::ALEATOIRE;
    }break;
    case 5 : {
        m_Nom = Metier::INQUISITEUR;
        m_Description = "Agent de l'Inquisition, une organisation secrète chargée de traquer les ennemis de l'imperium.";
        m_Image = ":/images/metier/inquisiteur.jpg";
        m_ConditionSelecteurProba = new Condition(0.001 - tmpFavoriseur, p_Relative); // 0.001
        // à peine nommé, un Inquisiteur est affecté à une nouvelle planète
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = Voyage::ALEATOIRE;
    }break;
    case 6 : {
        m_Nom = Metier::SERVANT_ADEPTUS_ASTRONOMICA;
        m_Description = "Vous êtes un servant dévoué héréditaire de l'Adeptus Astronomica. Comme vos parents avant vous et les parents de vos parents.";
        m_Image = ":/images/organisations/Adeptus_Astronomica_Icon_update.jpg";
        m_ConditionSelecteurProba = new Condition(0.001 - tmpFavoriseur, p_Relative); // 0.001
        m_Conditions.push_back(new Condition(Planete::C_PLANETE, Planete::TERRE, Comparateur::c_Egal));
    }break;
    }

    if ( m_ConditionSelecteurProba!= nullptr) {
        // si on a un métier les chances qu'on s'en voit affecter un sont très faibles :
        m_ConditionSelecteurProba->AjouterModifProba(-1.0, {new Condition(Metier::C_METIER, "", Comparateur::c_Different)});
        // et si on a moins de 15 ans la proba de s'en voir affecter un est très faible :
        // mais affectation de métier plus rapide sur monde féodal :
        m_ConditionSelecteurProba->AjouterModifProba(-2.3, {new Condition(GenVieHumain::AGE, "120", Comparateur::c_Inferieur)});
        m_ConditionSelecteurProba->AjouterModifProba(-2.3,
            {new Condition(GenVieHumain::AGE, "180", Comparateur::c_Inferieur),
             new Condition(Planete::C_TYPE_PLANETE, Planete::PLANETE_FEODAL, Comparateur::c_Different)
                                       });
    }

    METIERS[m_Nom] = this;

    Metier::COMPTEUR++;
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
        effetAffectation->AjouterChangeurDeCarac(Metier::C_METIER, metier->m_Nom);
        QMapIterator<QString, QString> it(metier->m_ModificateursCaracs);
        while ( it.hasNext()) {
            it.next();
            effetAffectation->AjouterChangeurDeCarac(it.key(), it.value());
        }

        Condition* cond = metier->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effetAffectation,
                    cond);

        noeuds.push_back(noeud);

        metier = new Metier();
    }
}
