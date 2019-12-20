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
#include "humain.h"
#include "../destinLib/execeffet.h"

Voyage::Voyage(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Réaffectation vers une planète";
        m_ConditionSelecteurProba = new Condition(0.5, p_Relative);
        m_Conditions.push_back(new Condition(Voyage::REAFFECTATION_PLANETE, "", Comparateur::c_Different));
        m_Description = "Vous avez été réaffecté vers une nouvelle planète.";
        m_ModificateursCaracs[Voyage::VOYAGE_WARP] = "1";
        m_ModificateursCaracs[Planete::C_PLANETE] = "";
        m_ModificateursCaracs[Voyage::REAFFECTATION_PLANETE] = "";
        m_CallbackDisplay = [](){
            Humain* humain = Humain::GetHumainJoue();
            QString planeteDestinationStr = humain->GetValeurCarac(Voyage::REAFFECTATION_PLANETE);
            Planete* nouvellePlanete = nullptr;
            if ( planeteDestinationStr == Voyage::ALEATOIRE) {
                // détermination dynamique de la planète de destination :
                nouvellePlanete = Planete::GetPlaneteAleatoire(true, true);
                planeteDestinationStr = nouvellePlanete->m_Nom;
            }
            if ( nouvellePlanete == nullptr ) {
                nouvellePlanete = Planete::PLANETES[planeteDestinationStr];
            }
            ExecEffet* effetActuel = Univers::ME->GetExecHistoire()->GetExecEffetActuel();
            effetActuel->ChargerImage( nouvellePlanete->m_Image);
            effetActuel->GetEffet()->m_Texte = "Vos avez été envoyé vers la planète " + planeteDestinationStr + ". --> la suite n'est pas faite !";
            IPerso::GetPersoCourant()->SetValeurACaracId(Voyage::C_DESTINATION_PLANETE, planeteDestinationStr);
        };
    }break;
    case 1 : {
        // TODO MATHIEU : pour simplifier je rends les voyages warps fiables et instantanés => à faire un de ces jours
        m_Nom = "Voyage instantané";
        m_ConditionSelecteurProba = new Condition(0.5, p_Relative);
        m_Conditions.push_back(new Condition(Voyage::C_DESTINATION_PLANETE, "", Comparateur::c_Different));
        m_Description = "Vous arrivez à votre planète de destination.";
        m_ModificateursCaracs[Voyage::VOYAGE_WARP] = "";
        m_CallbackDisplay = [](){
            Humain* humain = Humain::GetHumainJoue();
            QString planeteDestinationStr = humain->GetValeurCarac(Voyage::C_DESTINATION_PLANETE);
            Planete* nouvellePlanete = Planete::PLANETES[planeteDestinationStr];

            ExecEffet* effetActuel = Univers::ME->GetExecHistoire()->GetExecEffetActuel();
            effetActuel->ChargerImage( nouvellePlanete->m_Image);
            effetActuel->GetEffet()->m_Texte = "Vos arrivez enfin à la planète " + planeteDestinationStr + ".";
            IPerso::GetPersoCourant()->SetValeurACaracId(Planete::C_PLANETE, planeteDestinationStr);
            IPerso::GetPersoCourant()->SetValeurACaracId(Voyage::C_DESTINATION_PLANETE, "");
        };
    }break;

    }
}

QString Voyage::GetDescription()
{
    return m_Description;
}

QString Voyage::C_DESTINATION_PLANETE = "Destination planète";
QString Voyage::REAFFECTATION_PLANETE = "Réaffectation planète";
QString Voyage::ALEATOIRE = "Aléatoire";
QString Voyage::VOYAGE_WARP = "Voyage warp";
