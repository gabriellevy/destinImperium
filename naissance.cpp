#include "naissance.h"
#include "../destinLib/aleatoire.h"
#include "types_planete/planet.h"
#include "socio_eco/classesociale.h"

Effet* Naissance::GenererEffetNaissance(Effet* effetNarrationVide)
{
    // 1 : déterminer planète de naissance :
    Planete* planete = Planete::GetPlaneteAleatoire(true);

    effetNarrationVide->m_Texte = "Vous êtes nés sur " +
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

    //2. détermination classe sociale :
    e_ClasseSociale classeSociale = ClasseSociale::GetClasseSocialeAleatoire(planete->m_TypePlanete);
    QString classeSocialeStr = ClasseSociale::GetClasseSocialeAsStr(classeSociale, planete->m_TypePlanete);
    effetNarrationVide->AjouterChangeurDeCarac(ClasseSociale::ID_CLASSE_SOCIALE, classeSocialeStr);
}