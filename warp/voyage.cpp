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
#include "../destinLib/aleatoire.h"
#include "psyker.h"
#include "humanite/pbsante.h"
#include "texte/jourapresjour.h"
#include "socio_eco/economieevt.h"

QString Voyage::C_DESTINATION_PLANETE = "Destination planète";
QString Voyage::C_REAFFECTATION_PLANETE = "Réaffectation planète";
QString Voyage::ALEATOIRE = "Aléatoire";
QString Voyage::C_DUREE_VOYAGE_WARP = "Voyage warp";

Voyage::Voyage(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Réaffectation vers une planète";
        m_ConditionSelecteurProba = new Condition(0.5, p_Relative);
        m_Conditions.push_back(new Condition(Voyage::C_REAFFECTATION_PLANETE, "", Comparateur::c_Different));
        m_Description = "Vous avez été réaffecté vers une nouvelle planète.";
        m_ModificateursCaracs[Planete::C_PLANETE] = "";
        m_ModificateursCaracs[Voyage::C_REAFFECTATION_PLANETE] = "";
        m_CallbackDisplay = [](){
            Humain* humain = Humain::GetHumainJoue();
            QString planeteDestinationStr = humain->GetValeurCarac(Voyage::C_REAFFECTATION_PLANETE);
            Planete* nouvellePlanete = nullptr;
            if ( planeteDestinationStr == Voyage::ALEATOIRE) {
                // détermination dynamique de la planète de destination :
                nouvellePlanete = Planete::GetPlaneteAleatoire(true, true);
                planeteDestinationStr = nouvellePlanete->m_Nom;
            }
            if ( nouvellePlanete == nullptr ) {
                nouvellePlanete = Planete::PLANETES[planeteDestinationStr];
            }

            Voyage::DeclencherVoyageWarpVersPlanete(nouvellePlanete);
        };
    }break;
    case 1 : {
        m_Nom = "Voyage warp terminé";
        m_ConditionSelecteurProba = new Condition(0.5, p_Relative);
        m_Description = "Vous arrivez à votre planète de destination.";
        m_Image = ":/images/warp/flotte_hors_warp.png";
        m_Conditions.push_back(new Condition(Voyage::C_DUREE_VOYAGE_WARP, "0", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(new Condition(Voyage::C_DESTINATION_PLANETE, "", Comparateur::c_Different));
        m_ModificateursCaracs[Voyage::C_DUREE_VOYAGE_WARP] = "";
        m_CallbackDisplay = [](){
            Humain* humain = Humain::GetHumainJoue();
            QString planeteDestinationStr = humain->GetValeurCarac(Voyage::C_DESTINATION_PLANETE);
            Planete* nouvellePlanete = Planete::PLANETES[planeteDestinationStr];

            ExecEffet* effetActuel = Univers::ME->GetExecHistoire()->GetExecEffetActuel();
            effetActuel->ChargerImage( nouvellePlanete->m_Image);
            effetActuel->GetEffet()->m_Texte = "Vos arrivez enfin à la planète " + planeteDestinationStr + ".";
            IPerso::GetPersoCourant()->SetValeurACaracId(Planete::C_PLANETE, planeteDestinationStr);
            IPerso::GetPersoCourant()->SetValeurACaracId(Planete::C_TYPE_PLANETE, nouvellePlanete->m_TypePlanete);
            IPerso::GetPersoCourant()->SetValeurACaracId(Voyage::C_DESTINATION_PLANETE, "");
        };
    }break;
    case 2 : {
        m_Nom = "Voyage warp allongé";
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Les courants warp vous font dériver. Le voyage s'allonge.";
        m_Image = ":/images/warp/warp.jpg";
        m_Conditions.push_back(new Condition(Voyage::C_DUREE_VOYAGE_WARP, "0", Comparateur::c_Superieur));
        m_Conditions.push_back(new Condition(Voyage::C_DESTINATION_PLANETE, "", Comparateur::c_Different));
        m_IncrementeursCaracs[Voyage::C_DUREE_VOYAGE_WARP] = 1;
    }break;
    case 3 : {
        m_Nom = "Tempête Voyage warp allongé";
        m_ConditionSelecteurProba = new Condition(0.002, p_Relative);
        m_Description = "Une terrible tempête warp vous isole de l'Astronomicon. Impossible de naviguer dans ces conditions pour l'instant.";
        m_Image = ":/images/warp/Warpstorm_.jpg";
        m_Conditions.push_back(new Condition(Voyage::C_DUREE_VOYAGE_WARP, "0", Comparateur::c_Superieur));
        m_Conditions.push_back(new Condition(Voyage::C_DESTINATION_PLANETE, "", Comparateur::c_Different));
        m_IncrementeursCaracs[Voyage::C_DUREE_VOYAGE_WARP] = 5;
    }break;

    }
}

void Voyage::RafraichirPhrases()
{
    Humain* humain = Humain::GetHumainJoue();
    int nbMois = humain->GetValeurCaracAsInt(Voyage::C_DUREE_VOYAGE_WARP);

    JourApresJour::PHRASES.push_back(Phrase("Le voyage vous semble interminable mais il semble bien se passer.",
                                            ":/images/warp/warp.jpg"));
    JourApresJour::PHRASES.push_back(Phrase("Le warp vous provoque des cauchemars horribles de paysages infernaux.",
                                            ":/images/warp/enfers_warp.jpg"));
}

void Voyage::DeclencherVoyageWarpVersPlanete(Planete* planete)
{
    Humain* humain = Humain::GetHumainJoue();
    int nbMoisVoyage = Aleatoire::GetAl()->EntierEntreAEtB(2, 12);

    ExecEffet* effetActuel = Univers::ME->GetExecHistoire()->GetExecEffetActuel();
    effetActuel->ChargerImage( planete->m_Image);
    effetActuel->GetEffet()->m_Texte = "Vos avez été envoyé vers la planète " + planete->m_Nom +
            ". Il est estimé que le trajet prendra " + QString::number(nbMoisVoyage) + " mois.";
    humain->SetValeurACaracId(Voyage::C_DESTINATION_PLANETE, planete->m_Nom);
    humain->SetValeurACaracId(Voyage::C_DUREE_VOYAGE_WARP, nbMoisVoyage);
}

QString Voyage::GetDescription()
{
    return m_Description;
}
