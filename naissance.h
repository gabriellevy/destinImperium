#ifndef NAISSANCE_H
#define NAISSANCE_H

#include "../destinLib/effet.h"

/**
 * @brief classe gérant uniquement ce qui se détermine immédiatement à la naissance du personnage
 */
class Naissance
{
public:

    static Effet* GenererEffetNaissance(Effet* effetNarrationVide);
};

#endif // NAISSANCE_H
