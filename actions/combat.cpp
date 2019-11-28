#include "combat.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"

Combat::Combat()
{

}

QString Combat::C_FORCE_COMBAT = "Force de combat";

int Combat::JouerCombat(int forceEnnemi, int forceJoueur)
{
    int deJ = Aleatoire::GetAl()->D6();
    int deE = Aleatoire::GetAl()->D6();

    if ( forceJoueur ==  -1) {
        forceJoueur = Humain::GetHumainJoue()->GetValeurCaracAsInt(Combat::C_FORCE_COMBAT);
    }

    return (forceJoueur + deJ - deE - forceEnnemi);
}
