#include "voyage.h"
#include "genviehumain.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "planet.h"
#include "../destinLib/gestionnairecarac.h"

int Voyage::COMPTEUR = 0;

Voyage::Voyage()
{
    switch (Voyage::COMPTEUR) {
    case 0 : {
        m_Nom = "Réaffectation vers une planète";
        m_Condition = new Condition(0.0);
        m_Condition->AjouterModifProba(2.0,
        {new Condition(Voyage::REAFFECTATION_PLANETE, "", Comparateur::c_Different)});
        m_Description = "Vos avez été réaffecté vers une nouvelle planète.";
        m_ModificateursCaracs[Voyage::VOYAGE_WARP] = "1";
        m_ModificateursCaracs[GenVieHumain::PLANETE] = "";
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = "";
        m_CallbackDisplay = [](){
            // détermination dynamique de la planète de destination :
            Planete* nouvellePlanete = Planete::GetPlaneteAleatoire(true, true);
            Effet* effetActuel = Univers::ME->GetExecHistoire()->EffetActuel();
            effetActuel->m_ImgPath = nouvellePlanete->m_Image;
            effetActuel->m_Texte = "Vos avez été réaffecté vers la planète " + nouvellePlanete->m_Nom + ".";
            GestionnaireCarac::SetValeurACaracId(Voyage::DESTINATION_PLANETE, nouvellePlanete->m_Nom);
        };
    }break;

    }

    Voyage::COMPTEUR++;
}

QString Voyage::GetDescription()
{
    return m_Description;
}

void Voyage::GenererNoeudsVoyage(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    Voyage* voyage = new Voyage();
    while ( voyage->m_Nom != "") {
        Effet* effetAffectation = genEvt->AjouterEffetNarration(
                    voyage->GetDescription(),
                    voyage->m_Image,
                    "voyage_" + voyage->m_Nom, GenVieHumain::EVT_SELECTEUR);

        effetAffectation->m_GoToEffetId = GenVieHumain::EFFET_SELECTEUR_ID;
        effetAffectation->m_CallbackDisplay = voyage->m_CallbackDisplay;

        // modificateurs de carac :
        effetAffectation = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effetAffectation);
        QMapIterator<QString, QString> it(voyage->m_ModificateursCaracs);
        while ( it.hasNext()) {
            it.next();
            effetAffectation->AjouterChangeurDeCarac(it.key(), it.value());
        }

        Condition* cond = voyage->m_Condition;

        NoeudProbable* noeud = new NoeudProbable(
                    effetAffectation,
                    cond);

        noeuds.push_back(noeud);

        voyage = new Voyage();
    }
}

QString Voyage::DESTINATION_PLANETE = "Destination planète";
QString Voyage::REAFFECTATION_PLANETE = "Réaffectation planète";
QString Voyage::ALEATOIRE = "Aléatoire";
QString Voyage::VOYAGE_WARP = "Voyage warp";
