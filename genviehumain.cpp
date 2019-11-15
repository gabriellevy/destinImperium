#include "genviehumain.h"
#include "imperium.h"
#include "../destinLib/gestionnairecarac.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/perso.h"
#include "../destinLib/execeffet.h"
#include "../destinLib/lancerde.h"
#include "../destinLib/setcarac.h"
#include "../destinLib/choix.h"

GenVieHumain::GenVieHumain():GenHistoire ("Vive l'Imperium") {}

GenVieHumain* GenVieHumain::GetGenVieHumain()
{
    return static_cast<GenVieHumain*>(ME);
}

Hist* GenVieHumain::GenererHistoire()
{
    GenererPersos();

    //GenererFonctionsCallback();

    GenererEvtsAccueil();

    GenererCaracs();

    return m_HistoireGeneree;
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
    AjouterEffetNarration("vous êtes né", ":/images/Imperium.jpg");

    //GenererCombatBidon();
}
