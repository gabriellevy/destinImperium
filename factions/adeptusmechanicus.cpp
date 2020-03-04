#include "adeptusmechanicus.h"
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
#include "humain.h"

// caracs
QString AdeptusMechanicus::C_DIVISION = "Division";
// valeurs de C_DIVISION
QString AdeptusMechanicus::ALCHEMYS = "Magos Alchemys";
QString AdeptusMechanicus::BIOLOGIS = "Magos Biologis";
QString AdeptusMechanicus::TECHNICUS = "Magos Technicus";
QString AdeptusMechanicus::LOGIS = "Magos Logis";
QString AdeptusMechanicus::XENOLOGIS = "Magos Xenologis";
QString AdeptusMechanicus::LEXMECHANICUS = " Magos Lexmechanicus";
QString AdeptusMechanicus::ORBOLOGIS = "Magos Orbologis";
QString AdeptusMechanicus::CYBERNETIKA = "Magos Cybernetica";
QString AdeptusMechanicus::XENOBIOLOGIS = "Magos Xenobiologis";
QString AdeptusMechanicus::ASTROLOGICUS = "Magos Astrologicus";
QString AdeptusMechanicus::DIGITALIS = "Magos Digitalis";
QString AdeptusMechanicus::FABRICATOR = "Magos Fabricator";
QString AdeptusMechanicus::GENETUS = "Magos Genetus";
QString AdeptusMechanicus::PHYSIC = "Magos Physic";

QList<QString> AdeptusMechanicus::DIVISIONS = {
    AdeptusMechanicus::ALCHEMYS,
    AdeptusMechanicus::BIOLOGIS,
    AdeptusMechanicus::TECHNICUS,
    AdeptusMechanicus::LOGIS,
    AdeptusMechanicus::XENOLOGIS,
    AdeptusMechanicus::LEXMECHANICUS,
    AdeptusMechanicus::ORBOLOGIS,
    AdeptusMechanicus::CYBERNETIKA,
    AdeptusMechanicus::XENOBIOLOGIS,
    AdeptusMechanicus::ASTROLOGICUS,
    AdeptusMechanicus::DIGITALIS,
    AdeptusMechanicus::FABRICATOR,
    AdeptusMechanicus::GENETUS,
    AdeptusMechanicus::PHYSIC
};

AdeptusMechanicus::AdeptusMechanicus(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "youpi AdeptusMechanicus";
        m_ConditionSelecteurProba = make_shared<Condition>(0.0, p_Relative);
        m_Description = "??? Assassinorum";
        //m_ModificateursCaracs[SecteChaos::C_SECTE_CHAOS] = "1";
        /*m_CallbackDisplay = [] {

        };*/

    }break;
    }
}

QString AdeptusMechanicus::DeterminerDivisionAleatoire()
{
    return AdeptusMechanicus::DIVISIONS[Aleatoire::GetAl()->EntierInferieurA(AdeptusMechanicus::DIVISIONS.length())];
}
