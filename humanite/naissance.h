#ifndef NAISSANCE_H
#define NAISSANCE_H

#include "../destinLib/abs/effet.h"

/**
 * @brief classe gérant uniquement ce qui se détermine immédiatement à la naissance du personnage
 */
class Naissance
{
public:

    static std::shared_ptr<Effet> GenererEffetNaissance(std::shared_ptr<Effet> effetNarrationVide);
};

#endif // NAISSANCE_H
