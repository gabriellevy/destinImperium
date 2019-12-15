#include "voyage.h"
#include "genviehumain.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "types_planete/planet.h"
#include "../destinLib/gestionnairecarac.h"

Voyage::Voyage(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Réaffectation vers une planète";
        m_ConditionSelecteurProba = new Condition(0.0, p_Relative);
        m_ConditionSelecteurProba->AjouterModifProba(2.0,
        {new Condition(Voyage::REAFFECTATION_PLANETE, "", Comparateur::c_Different)});
        m_Description = "Vos avez été réaffecté vers une nouvelle planète.";
        m_ModificateursCaracs[Voyage::VOYAGE_WARP] = "1";
        m_ModificateursCaracs[Planete::C_PLANETE] = "";
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = "";
        m_CallbackDisplay = [](){
            // détermination dynamique de la planète de destination :
            Planete* nouvellePlanete = Planete::GetPlaneteAleatoire(true, true);
            Effet* effetActuel = Univers::ME->GetExecHistoire()->EffetActuel();
            effetActuel->m_ImgPath = nouvellePlanete->m_Image;
            effetActuel->m_Texte = "Vos avez été réaffecté vers la planète " + nouvellePlanete->m_Nom + ".";
            IPerso::GetPersoCourant()->SetValeurACaracId(Voyage::DESTINATION_PLANETE, nouvellePlanete->m_Nom);
        };
    }break;

    }
}

QString Voyage::GetDescription()
{
    return m_Description;
}

QString Voyage::DESTINATION_PLANETE = "Destination planète";
QString Voyage::REAFFECTATION_PLANETE = "Réaffectation planète";
QString Voyage::ALEATOIRE = "Aléatoire";
QString Voyage::VOYAGE_WARP = "Voyage warp";
