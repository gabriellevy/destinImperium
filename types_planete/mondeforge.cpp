#include "mondeforge.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "warp/voyage.h"
#include "metier.h"
#include "../destinLib/aleatoire.h"
#include "../socio_eco/classesociale.h"
#include "../actions/combat.h"
#include "humanite/pbsante.h"
#include "../destinLib/gestionnairecarac.h"
#include "humain.h"
#include "texte/jourapresjour.h"

MondeForge::MondeForge(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "bouche trou en attendant MondeForge";
        // pas pour les très pauvres :
        m_Conditions = { make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::MISERABLES, Comparateur::c_Different)                       };
        m_ConditionSelecteurProba = make_shared<Condition>(0.0, p_Relative); // 0.01
        /*m_Description = "Vous prenez le train des cendres pour rendre une visite dans la ruche " +
                MondeRuche::GetNomRucheAleatoire() +
                ".";
        m_Image = ":/images/ruche/Ruche.png";
        m_CallbackDisplay = [] {
        }*/
        }break;
    }

}

void MondeForge::RafraichirPhrases()
{
    JourApresJour::PHRASES.push_back(Phrase("Une petite pause pour admirer les merveilles de l'industrie humaine.",
                                            ":/images/monde_forge/Exterieur.jpg"));
    JourApresJour::PHRASES.push_back(Phrase("Les forges tournent à plein régime. La production sera bonne.",
                                            ":/images/monde_forge/ForgeWorldInterior.png"));
    JourApresJour::PHRASES.push_back(Phrase("Les serviteurs vous assistent efficacement.",
                                            ":/images/monde_forge/Serviteur.png"));
}
