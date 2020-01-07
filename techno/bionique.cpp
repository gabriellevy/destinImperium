#include "bionique.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "imperium.h"
#include "genviehumain.h"
#include "../types_planete/planet.h"
#include "warp/voyage.h"
#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/aleatoire.h"
#include "socio_eco/classesociale.h"
#include "humanite/pbsante.h"

QString Bionique::C_BIONIQUE_LONGEVITE = "Bionique longévité";

Bionique::Bionique(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "ajout de " + Bionique::C_BIONIQUE_LONGEVITE;
        m_ConditionSelecteurProba = new Condition(0.01, p_Relative);
        m_Description = "Vous remplacez un de vos organes défaillants pour allonger votre durée de vie.";
        m_IncrementeursCaracs[Bionique::C_BIONIQUE_LONGEVITE] = 1;
        m_Image = ":/images/techno/Biotic_Arm.jpg";
        // pour les vieux riches
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiClasseSocialeSuperieureA(ClasseSociale::CLASSE_MOYENNE));
        m_Conditions.push_back(PbSante::AjouterConditionSiAgeSuperieurA(30));
        m_Conditions.push_back(Bionique::AjouterConditionSiBioniqueLongeviteInferieurA(10));

    }break;
    }
}

Condition* Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(int nbBionique)
{
    Condition* cond = new Condition(Bionique::C_BIONIQUE_LONGEVITE, QString::number(nbBionique), Comparateur::c_Superieur);
    return cond;
}
Condition* Bionique::AjouterConditionSiBioniqueLongeviteInferieurA(int nbBionique)
{
    Condition* cond = new Condition(Bionique::C_BIONIQUE_LONGEVITE, QString::number(nbBionique), Comparateur::c_Inferieur);
    return cond;
}
