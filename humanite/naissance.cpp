#include "naissance.h"
#include "../destinLib/aleatoire.h"
#include "types_planete/planet.h"
#include "socio_eco/classesociale.h"
#include "socio_eco/maison.h"
#include "warp/psyker.h"
#include "genviehumain.h"
#include "metier.h"
#include "types_planete/monderuche.h"

Effet* Naissance::GenererEffetNaissance(Effet* effetNarrationVide)
{
    // 1 : déterminer planète de naissance :
    Planete* planete = Planete::GetPlaneteAleatoire(true);

    effetNarrationVide->m_Texte = "Vous êtes né sur " +
            planete->m_Nom +
            (planete->m_TypePlanete == "" ? "" : ", " + planete->m_TypePlanete);

    if ( planete->m_TitheGrade != nullptr) {
        effetNarrationVide->m_Texte += " (" + planete->m_TitheGrade->GetIntitule() + ")";
    }
    effetNarrationVide->m_Texte += ".";

    if ( planete->m_Faction != nullptr) {
        effetNarrationVide->m_Texte += "\nCette planète est contrôlée par " + planete->m_Faction->m_Nom + ".";
    }

    effetNarrationVide->AjouterChangeurDeCarac(Planete::C_PLANETE, planete->m_Nom);
    effetNarrationVide->AjouterChangeurDeCarac(Planete::C_TYPE_PLANETE, planete->m_TypePlanete);
    effetNarrationVide->m_ImgPath = planete->m_Image;
    effetNarrationVide->m_GoToEffetId = "finNaissance";

    // 2. détermination classe sociale :
    QString classeSocialeStr = ClasseSociale::GetClasseSocialeAleatoire(planete->m_TypePlanete);
    effetNarrationVide->AjouterChangeurDeCarac(ClasseSociale::C_CLASSE_SOCIALE, classeSocialeStr);

    // 2b. détermination de la zone d'habitation (sur sa planète)
    if ( planete->m_TypePlanete == Planete::PLANETE_RUCHE) {
        MondeRuche::AssignerCaracsDeNaissance(classeSocialeStr, effetNarrationVide);
    }

    // 3. détermination de maison éventuelle
    QString maisonStr = Maison::AssignerMaison(classeSocialeStr, planete->m_TypePlanete);
    effetNarrationVide->AjouterChangeurDeCarac(Maison::C_MAISON, maisonStr);
    if ( maisonStr != "") {
        effetNarrationVide->m_Texte += "\nVous êtes de la maison " + maisonStr + ".";
    }

    // 4. détermination si psyker
    QString nivPsyker = Psyker::GetNiveauPsykerNaissance();
    effetNarrationVide->AjouterChangeurDeCarac(Psyker::C_PSYKER, nivPsyker);
}
