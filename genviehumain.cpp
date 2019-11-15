#include "genviehumain.h"
#include "imperium.h"
#include "../destinLib/gestionnairecarac.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/perso.h"
#include "../destinLib/execeffet.h"
#include "../destinLib/lancerde.h"
#include "../destinLib/setcarac.h"
#include "../destinLib/choix.h"
#include "planet.h"

GenVieHumain::GenVieHumain():GenHistoire ("Vive l'Imperium") {}

GenVieHumain* GenVieHumain::GetGenVieHumain()
{
    return static_cast<GenVieHumain*>(ME);
}

Hist* GenVieHumain::GenererHistoire()
{
    GenererDataUnivers();

    GenererPersos();

    //GenererFonctionsCallback();

    GenererEvtsAccueil();

    GenererCaracs();

    return m_HistoireGeneree;
}

void GenVieHumain::GenererDataUnivers()
{
}

void GenVieHumain::GenererPersos()
{
    DPerso* perso = new DPerso("?", "?", "?", "");
    perso->InitialiserPerso();
    IPerso::AjouterPersoJouable(perso);
}

void GenVieHumain::GenererCaracs()
{
    /*int chance = 6 + Aleatoire::GetAl()->D6();
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(LDOELH::CHANCE, chance, 0, chance);
*/}

void GenVieHumain::GenererEvtsAccueil()
{
    this->AjouterEvt("Debut", "Génération du perso par les choix");
    Effet* effet1 = AjouterEffetNarration("", "");
    effet1->m_GoToEffetId = "effetSelectionPlanete";

    QVector<NoeudProbable*> noeudsDestination = Planete::ConstruireToutePlanetes(m_GenerateurEvt); // doit se faire ici car contient la génération d'effets associés
    Effet* effetSelectionPlanete = m_GenerateurEvt->AjouterEffetSelecteurDEvt(noeudsDestination, "effetSelectionPlanete");
    effetSelectionPlanete->m_MsChrono = 1;
}
