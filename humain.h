#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestionnairecarac.h"
#include "planet.h"

class Humain : public DPerso
{
public:
    Humain();

    Planete* GetPlanete();
};

#endif // HUMAIN_H
